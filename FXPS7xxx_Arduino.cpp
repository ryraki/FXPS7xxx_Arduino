/*
 * Copyright 2023 ryrak
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**
 * @file FXPS7xxx_Arduino.cpp
 * @brief This file contains the functions for FXPS7xxx Pressure sensor evaluation by Arduino
 */
 
#include "Arduino.h"
#include "Wire.h"
#include "fxps7xxx_regdef.h"
#include "FXPS7xxx_Arduino.h"

// Run this function first!!
uint8_t fxps7xxx_init() {
  Wire.begin();
  uint8_t data = 0;
  fxps7xxx_read_reg(FXPS7XXX_DEVSTAT, 1, &data);
  fxps7xxx_read_reg(FXPS7XXX_WHO_AM_I, 1, &data);
  if(data != FXPS7XXX_H_WHOAMI_VALUE){
    return FXPS7XXX_DEVICE_NOT_FOUND;
  }
  return SENSOR_SUCCESS;
}

uint8_t fxps7xxx_get_pressure(float *pPressure) {
  uint8_t data[2] = {0};
  fxps7xxx_read_reg(FXPS7XXX_SNSDATA0_L, 2, data);
  uint16_t raw_pressure = ((int16_t)(data[1]<< 8) | data[0]);
  *pPressure = ((raw_pressure - 28661.6 ) / 30.42);
  return 0;
}

uint8_t fxps7xxx_get_temperature(float *pTemperature) {
  uint8_t data = 0;
  fxps7xxx_read_reg(FXPS7XXX_TEMPERATURE, 1, &data);
  *pTemperature = data - 68;
  return 0;
}

uint8_t fxps7xxx_read_reg(uint16_t address, uint8_t num, uint8_t *pReadBuffer) {
  if (address >= 0xa0) {
    if (((address+num)&0xf0) != (address&0xf0)) return FXPS7XXX_REGION_ERROR;
    fxps7xxx_write_reg(address & 0xf0, FXPS7XXX_UF_REGION_W);
    delay(1);
    Wire.beginTransmission(FXPS7xxx_I2C_ADDR);
    Wire.write(FXPS7XXX_UF_REGION_R);
    Wire.endTransmission(false);
    Wire.requestFrom(FXPS7xxx_I2C_ADDR, (uint8_t)1);
    uint8_t data = Wire.read();
    if (data != (address & 0xf0)) return FXPS7XXX_REGION_ERROR;
  }
  Wire.beginTransmission(FXPS7xxx_I2C_ADDR);
  Wire.write(address);
  Wire.endTransmission(false);
  Wire.requestFrom(FXPS7xxx_I2C_ADDR, num);
  for (int i=0; i<num; i++)
    pReadBuffer[i] = Wire.read();
  return 0;
}

uint8_t fxps7xxx_write_reg(uint16_t address, uint8_t writeBuffer) {
  Wire.beginTransmission(FXPS7xxx_I2C_ADDR);
  Wire.write(address);
  Wire.write(writeBuffer);
  Wire.endTransmission();
  return 0;
}

uint8_t fxps7xxx_startup_self_test(uint8_t mode) {
  FXPS7XXX_DSP_STAT_t dsp_status = {0};
  uint16_t sens_16_expected = 0;
  uint8_t stat = SENSOR_SUCCESS;
  
  // Common Mode Self-Test
  if (mode == FXPS7XXX_DSP_CFG_U5_STL_CTRL_P_CELL_MODE_VERIFICATION) {
    fxps7xxx_write_reg(FXPS7XXX_DSP_CFG_U5, FXPS7XXX_DSP_CFG_U5_STL_CTRL_P_CELL_MODE_VERIFICATION);
    delay(10);
    fxps7xxx_write_reg(FXPS7XXX_DSP_CFG_U5, FXPS7XXX_DSP_CFG_U5_STL_CTRL_NORMAL_SIGNAL);
    for (int i=0; i<10; i++) {
      delay(10);
      fxps7xxx_read_reg(FXPS7XXX_DSP_STAT, 1, &dsp_status.w);
      if (!dsp_status.b.st_active) break;
    }
    if (dsp_status.b.st_active || dsp_status.b.st_error) return FXPS7xxx_ST_FAILED;
    return SENSOR_SUCCESS;
  }
  
  // Fixed or Digital Test
  else if (mode == FXPS7XXX_DSP_CFG_U5_STL_CTRL_INHIBIT_SNS_DATA_X_WRITE0 || mode == FXPS7XXX_DSP_CFG_U5_STL_CTRL_INHIBIT_SNS_DATA_X_WRITE1 || mode == FXPS7XXX_DSP_CFG_U5_STL_CTRL_INHIBIT_SNS_DATA_X_WRITE2 || mode == FXPS7XXX_DSP_CFG_U5_STL_CTRL_INHIBIT_SNS_DATA_X_WRITE3)
    sens_16_expected = fixed_st[(mode>>4)&0x03];    // Fixed Test
  else if (mode == FXPS7XXX_DSP_CFG_U5_STL_CTRL_DIGITAL_SELF_TEST0 || mode == FXPS7XXX_DSP_CFG_U5_STL_CTRL_DIGITAL_SELF_TEST1 || mode == FXPS7XXX_DSP_CFG_U5_STL_CTRL_DIGITAL_SELF_TEST2 || mode == FXPS7XXX_DSP_CFG_U5_STL_CTRL_DIGITAL_SELF_TEST3)
    sens_16_expected = digital_st[(mode>>4)&0x03];  // Digital Test
  else return FXPS7xxx_ST_FAILED;
  fxps7xxx_write_reg(FXPS7XXX_DEVLOCK_WR, 0x00);  // Make sure ENDINIT=0
  fxps7xxx_write_reg(FXPS7XXX_DSP_CFG_U5, mode);  // Enable Self-Test
  delay(10);
  uint8_t sens_data8[2];
  fxps7xxx_read_reg(FXPS7XXX_SNSDATA0_L, 2, sens_data8);
  uint16_t sens_data16 = ((int16_t)(sens_data8[1]<< 8) | sens_data8[0]);
  if (sens_data16 != sens_16_expected) stat = FXPS7xxx_ST_FAILED;
  fxps7xxx_write_reg(FXPS7XXX_DSP_CFG_U5, 0x00);
  return stat;
}