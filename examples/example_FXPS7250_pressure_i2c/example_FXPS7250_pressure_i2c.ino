/*
 * Copyright 2023 ryrak
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**
 * @file example_FXPS7250_pressure_i2c.ino
 * @brief Read pressure data from registers
 */

#include "FXPS7xxx_Arduino.h"
#include <Wire.h>

FXPS7xxx_Arduino dbap(FXPS7250I);

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);
  Serial.println("Demo program start");
  uint8_t stat = dbap.init();
  Serial.println("Initialization finished. Start reading data by kPa");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("===CH0===");
  Serial.print("Read by register read      : ");
  Serial.println(dbap.get_pressure(0));
  Serial.println("===CH1===");
  Serial.print("Read by register read      : ");
  Serial.println(dbap.get_pressure(1));
  delay(5000);
}
