/*
 * Copyright 2023 ryraki
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
#include "SPI.h"
#include "fxps7xxx_regdef.h"
#include "FXPS7xxx_Arduino.h"

uint8_t FXPS7xxx_Arduino::init() {
  uint8_t data = 0;
  uint8_t stat = 0;
  if (comType == FXPS7XXX_ANA) {
    pinMode(A0, INPUT);
    return SENSOR_SUCCESS;
  }
  reset();
  delay(100);
  if (comType == FXPS7XXX_SPI) {
    int i=0;
    for (; i<100; i++) {
      read_reg(FXPS7XXX_WHO_AM_I, 1, &data);
      if (data==FXPS7XXX_H_WHOAMI_VALUE) break;
    }
    if (i==100) {
      Serial.println("Error during initialization");
      return FXPS7XXX_DEVICE_NOT_FOUND;
    }
  }
  stat = read_reg(FXPS7XXX_WHO_AM_I, 1, &data);
  if(data != FXPS7XXX_H_WHOAMI_VALUE){
    Serial.println("Error during initialization");
    return FXPS7XXX_DEVICE_NOT_FOUND;
  }
  read_reg(FXPS7XXX_DEVSTAT, 1, &data);
  read_reg(FXPS7XXX_DEVSTAT, 1, &data);
  return stat;
}

void FXPS7xxx_Arduino::reset() {
  if (comType == FXPS7XXX_ANA)
    return;
  write_reg(FXPS7XXX_DEVLOCK_WR, FXPS7XXX_DEVLOCK_WR_RESET00);
  write_reg(FXPS7XXX_DEVLOCK_WR, FXPS7XXX_DEVLOCK_WR_RESET11);
  write_reg(FXPS7XXX_DEVLOCK_WR, FXPS7XXX_DEVLOCK_WR_RESET01);
}

uint8_t FXPS7xxx_Arduino::read_reg(uint8_t address, uint8_t num, uint8_t *pReadBuffer) {
  switch(comType) {
    case communicationInterface::_I2C:
      read_reg_i2c(address, num, pReadBuffer);
      break;
    case communicationInterface::_SPI:
      read_reg_spi(address, num, pReadBuffer);
      break;
    default:
      break;
  }
  return SENSOR_SUCCESS;
}

uint8_t FXPS7xxx_Arduino::write_reg(uint8_t address, uint8_t writeBuffer) {
  switch(comType) {
    case communicationInterface::_I2C:
      write_reg_i2c(address, writeBuffer);
      break;
    case communicationInterface::_SPI:
      write_reg_spi(address, writeBuffer);
      break;
    default:
      break;
  }
  return SENSOR_SUCCESS;
}

uint8_t FXPS7xxx_Arduino::read_reg_i2c(uint8_t address, uint8_t num, uint8_t *pReadBuffer) {
  // In case that the user accesses the UF region
  if (address >= 0xa0) {
    if (((address+num)&0xf0) != (address&0xf0)) return FXPS7XXX_REGION_ERROR;
    write_reg(address & 0xf0, FXPS7XXX_UF_REGION_W);
    delay(1);
    Wire.beginTransmission(I2C_address);
    Wire.write(FXPS7XXX_UF_REGION_R);
    Wire.endTransmission(false);
    Wire.requestFrom(I2C_address, (uint8_t)1);
    uint8_t data = Wire.read();
    if (data != (address & 0xf0)) return FXPS7XXX_REGION_ERROR;
  }
  // Normal Operation of read function
  Wire.beginTransmission(I2C_address);
  Wire.write(address);
  Wire.endTransmission(false);
  Wire.requestFrom(I2C_address, num);
  for (int i=0; i<num; i++)
    pReadBuffer[i] = Wire.read();
  return SENSOR_SUCCESS;
}

uint8_t FXPS7xxx_Arduino::write_reg_i2c(uint8_t address, uint8_t writeBuffer) {
  Wire.beginTransmission(I2C_address);
  Wire.write(address);
  Wire.write(writeBuffer);
  Wire.endTransmission();
  return SENSOR_SUCCESS;
}

uint8_t FXPS7xxx_Arduino::read_reg_spi(uint8_t address, uint8_t num, uint8_t *pReadBuffer) {
  uint8_t stat=0;
  // In case that the user accesses the UF region
  if (address >= 0xa0) {
    if (((address+num)&0xf0) != (address&0xf0)) return FXPS7XXX_REGION_ERROR;
    stat += write_reg(address & 0xf0, FXPS7XXX_UF_REGION_W);
    delay(1);
    uint8_t _spi_txdata_uf[4] = {FXPS7XXX_SPI_R, address, FXPS7XXX_UF_REGION_R, 0};
    stat += access_reg_spi(_spi_txdata_uf);
    stat += access_reg_spi(_spi_txdata_uf);
    if (spi_rxdata[2] != (address & 0xf0)) stat = FXPS7XXX_REGION_ERROR;
    if (stat != SENSOR_SUCCESS) return stat;
  }
  // Normal Operation of read function
  uint8_t i = 0;
  while (i<num) {
    if (i==0 || (((address+i)%2)==0)) {
      uint8_t _spi_txdata[4] = {FXPS7XXX_SPI_R, address+i, 0, 0};
      stat = access_reg_spi(_spi_txdata);
      stat += access_reg_spi(_spi_txdata);
    }
    pReadBuffer[i] = spi_rxdata[2-(address+i)%2];
    i++;
  }
  return stat;
}

float FXPS7xxx_Arduino::get_pressure_sensor_data_request(uint8_t sensor) {
  if (comType != FXPS7XXX_SPI) return -1;
  if (sensor>=2) return -2;
  uint8_t sourceid=0;
  if (sensor==0) sourceid = sourceid0;
  else sourceid = sourceid1;
  uint8_t _spi_txdata[4] = {(sourceid<<5)|0x10, 0, 0, 0};
  access_reg_spi(_spi_txdata);
  uint8_t stat=access_reg_spi(_spi_txdata);
  if (stat != SENSOR_SUCCESS) return -3;
  uint16_t sensor_data = ((uint16_t)spi_rxdata[0]<<14) | ((uint16_t)spi_rxdata[1]<<6) | ((uint16_t)spi_rxdata[2]>>2);
  float output;
  if (num_sensor_data==0)
  output=((sensor_data>>4) - PABSOFF_12sdr[P_RANGE]) / PABS_sense_12sdr[P_RANGE];
  else
    output=((float)sensor_data - PABSOFF_16sdr[P_RANGE]) / PABS_sense_16sdr[P_RANGE];
  return output;
}

uint8_t FXPS7xxx_Arduino::write_reg_spi(uint8_t address, uint8_t writeBuffer) {
  if (address == FXPS7XXX_SOURCEID_0)
    sourceid0 = writeBuffer & 0x0f;
  if (address == FXPS7XXX_SOURCEID_1)
    sourceid1 = writeBuffer & 0x0f;
  if (address == FXPS7XXX_SPI_CFG)
    num_sensor_data = (writeBuffer & FXPS7XXX_SPI_CFG_DATASIZE_16)>>FXPS7XXX_SPI_CFG_DATASIZE_SHIFT;
  uint8_t _spi_txdata[4] = {FXPS7XXX_SPI_W, address, writeBuffer, 0};
  return access_reg_spi(_spi_txdata);
}

uint8_t FXPS7xxx_Arduino::access_reg_spi(uint8_t *p_spi_txdata) {
  uint8_t buffer[4];
  memcpy(buffer, p_spi_txdata, 4);
  buffer[3] = u8Crc_Calculate(buffer);
  memcpy(spi_txdata, buffer, 4);
  digitalWrite(spi_ss, HIGH);
  delay(1);
  SPI.beginTransaction(spi_settings);
  digitalWrite(spi_ss, LOW);
  SPI.transfer(&buffer, 4);
  digitalWrite(spi_ss, HIGH);
  SPI.endTransaction();
  memcpy(spi_rxdata, buffer, 4);
  if (debug) {
    char str[50];
    sprintf(str, "SPI SENT: %02x %02x %02x %02x\nSPI RCVD: %02x %02x %02x %02x\n", spi_txdata[0], spi_txdata[1], spi_txdata[2], spi_txdata[3], spi_rxdata[0], spi_rxdata[1], spi_rxdata[2], spi_rxdata[3]);
    Serial.print(str);
  }
  if (spi_rxdata[3] != u8Crc_Calculate(spi_rxdata)) return SENSOR_INVALIDPARAM_ERR;
  if (spi_rxdata[0]&0x08) {
    if (spi_rxdata[0]==0x08) return FXPS7xxx_ST_FAILED;
    else return FXPS7XXX_DEVICE_ERROR;
  }
  else return SENSOR_SUCCESS;
}

float FXPS7xxx_Arduino::get_pressure(uint8_t sensor) {
  if (comType == FXPS7XXX_ANA) {
    return analogRead(A0)/1023.0*250.0+10;
  }
  if (sensor >= 2) return -1;
  uint8_t data[2] = {0};
  if (sensor == 0)
    read_reg(FXPS7XXX_SNSDATA0_L, 2, data);
  else 
    read_reg(FXPS7XXX_SNSDATA1_L, 2, data);
  uint16_t raw_pressure = ((int16_t)(data[1]<< 8) | data[0]);
  return ((float)(raw_pressure - PABSOFF_16reg[P_RANGE] ) / PABS_sense_16reg[P_RANGE]);
}

int16_t FXPS7xxx_Arduino::get_temperature() {
  uint8_t data = 0;
  read_reg(FXPS7XXX_TEMPERATURE, 1, &data);
  return data - 68;
}

uint8_t FXPS7xxx_Arduino::self_test(uint8_t mode) {
  FXPS7XXX_DSP_STAT_t dsp_status = {0};
  uint16_t sens_16_expected = 0;
  uint8_t stat = SENSOR_SUCCESS;
  
  // Common Mode Self-Test
  if (mode == FXPS7XXX_DSP_CFG_U5_STL_CTRL_P_CELL_MODE_VERIFICATION) {
    write_reg(FXPS7XXX_DSP_CFG_U5, FXPS7XXX_DSP_CFG_U5_STL_CTRL_P_CELL_MODE_VERIFICATION);
    delay(10);
    write_reg(FXPS7XXX_DSP_CFG_U5, FXPS7XXX_DSP_CFG_U5_STL_CTRL_NORMAL_SIGNAL);
    for (int i=0; i<10; i++) {
      delay(10);
      read_reg(FXPS7XXX_DSP_STAT, 1, &dsp_status.w);
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
  write_reg(FXPS7XXX_DEVLOCK_WR, 0x00);  // Make sure ENDINIT=0
  write_reg(FXPS7XXX_DSP_CFG_U5, mode);  // Enable Self-Test
  delay(10);
  uint8_t sens_data8[2];
  read_reg(FXPS7XXX_SNSDATA0_L, 2, sens_data8);
  uint16_t sens_data16 = ((int16_t)(sens_data8[1]<< 8) | sens_data8[0]);
  if (sens_data16 != sens_16_expected) stat = FXPS7xxx_ST_FAILED;
  write_reg(FXPS7XXX_DSP_CFG_U5, 0x00);
  return stat;
}

uint8_t FXPS7xxx_Arduino::u8Crc_Calculate(uint8_t *p_u8_cmd_msg) {
  uint32_t u32_cmd_msg = ((uint32_t)p_u8_cmd_msg[0]<<24) | ((uint32_t)p_u8_cmd_msg[1]<<16) | ((uint32_t)p_u8_cmd_msg[2]<<8);
  struct {
    uint8_t u8InitialValue;
    uint16_t u16Polynomial;
    uint8_t u8CrcLength;
    uint8_t u8DataBitStart;
    uint8_t u8DataLength; // including the CRC
  } crc_calc_param = {0xFF, 0x012F, 0x08, 0, 32};
  uint16_t u16_index;
  /* Calculate mask value */
  uint64_t u64_mask = ((~(uint64_t)0) >> (32 - crc_calc_param.u8DataLength)) - ((uint64_t)(((uint64_t)1) << crc_calc_param.u8CrcLength) - 1);
  /* Update the command message using CRC params */
  u32_cmd_msg = (u32_cmd_msg >> crc_calc_param.u8DataBitStart) & ((uint32_t)(((uint64_t)1) << crc_calc_param.u8DataLength) - 1);
  /* Calculate remainder and XOR value */
  uint64_t u64_remainder = (uint64_t)(((((uint64_t)u32_cmd_msg)) | (((uint64_t)crc_calc_param.u8InitialValue) << (crc_calc_param.u8DataLength))) & u64_mask);
  uint64_t u64_xor = ((uint64_t)crc_calc_param.u16Polynomial) << (crc_calc_param.u8DataLength - 1) ;
  /* Calculate remainder by shifting xor value over message and CRC length */
  for (u16_index = (uint16_t)
    (((uint16_t)crc_calc_param.u8DataLength) +
    ((uint16_t)crc_calc_param.u8CrcLength)); u16_index > 0;
    u16_index--) {
      if (((u64_remainder >> (u16_index - 1)) & 0x01) != 0)
        u64_remainder ^= u64_xor;
      u64_xor >>= 1;
      if ((u64_remainder & u64_mask) == 0)
      break;
  }
  /* Return 8-bit CRC calculated */
  uint8_t CRC_Answer = (uint8_t)(u64_remainder & (uint8_t)((uint64_t)(((uint64_t)1) << crc_calc_param.u8CrcLength) - 1));
  //p_u8_cmd_msg[3] = CRC_Answer;
  return CRC_Answer;
}