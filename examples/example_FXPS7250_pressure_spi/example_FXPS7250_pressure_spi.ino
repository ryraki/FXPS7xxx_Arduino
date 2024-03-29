/*
 * Copyright 2023 ryraki
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**
 * @file example_FXPS7250_pressure_spi.ino
 * @brief Read pressure data from registers and sensor data request command
 */

#include "FXPS7xxx_Arduino.h"
#include <SPI.h>

FXPS7xxx_Arduino fxps7250s(FXPS7250S);

void setup() {
  // put your setup code here, to run once:
  SPI.begin();
  Serial.begin(115200);
  Serial.println("Demo program start");
  uint8_t stat = fxps7250s.init();
  fxps7250s.write_reg(FXPS7XXX_SOURCEID_0, FXPS7XXX_SOURCEID_0_SID0_EN | 0x02);
  fxps7250s.write_reg(FXPS7XXX_SOURCEID_1, 0x01);
  fxps7250s.write_reg(FXPS7XXX_SPI_CFG, FXPS7XXX_SPI_CFG_DATASIZE_16);
  fxps7250s.write_reg(FXPS7XXX_DEVLOCK_WR, FXPS7XXX_DEVLOCK_WR_ENDINIT_FINISHED);
  Serial.println("Initialization finished. Start reading data by kPa");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("===CH0===");
  Serial.print("Read by sensor data request: ");
  Serial.println(fxps7250s.get_pressure_sensor_data_request(0));
  Serial.print("Read by register read      : ");
  Serial.println(fxps7250s.get_pressure(0));
  Serial.println("===CH1===");
  Serial.print("Read by sensor data request: ");
  Serial.print(fxps7250s.get_pressure_sensor_data_request(1));
  Serial.println(" (Error due to non-enabled)");
  Serial.print("Read by register read      : ");
  Serial.println(fxps7250s.get_pressure(1));
  delay(5000);
}
