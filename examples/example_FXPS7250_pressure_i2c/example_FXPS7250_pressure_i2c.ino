/*
 * Copyright 2023 ryraki
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

FXPS7xxx_Arduino fxps7250i(FXPS7250I);

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);
  Serial.println("Demo program start");
  uint8_t stat = fxps7250i.init();
  Serial.println("Initialization finished. Start reading data by kPa");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("CH0:");
  Serial.print(fxps7250i.get_pressure(0));
  Serial.print(",CH1:");
  Serial.println(fxps7250i.get_pressure(1));
  delay(500);
}
