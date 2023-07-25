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

FXPS7xxx_Arduino fxps7250a(FXPS7250A);

void setup() {
  // put your setup code here, to run once:
  uint8_t stat = fxps7250a.init();
  Serial.println("Initialization finished. Start reading data by kPa");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(fxps7250a.get_pressure(1));
  delay(500);
}
