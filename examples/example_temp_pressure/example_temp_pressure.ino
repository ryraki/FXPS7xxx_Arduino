#include <FXPS7xxx_Arduino.h>
#include "Wire.h"

// If I2C address is not defined, it will be 0x60 by default
#define FXPS7xxx_I2C_ADDR (uint8_t)0x60

void setup() {
  // put your setup code here, to run once:
  fxps7xxx_init();
  Serial.begin(9600);
  uint8_t a = 0;
  a += fxps7xxx_startup_self_test(FXPS7XXX_DSP_CFG_U5_STL_CTRL_P_CELL_MODE_VERIFICATION);
  a += fxps7xxx_startup_self_test(FXPS7XXX_DSP_CFG_U5_STL_CTRL_INHIBIT_SNS_DATA_X_WRITE3);
  a += fxps7xxx_startup_self_test(FXPS7XXX_DSP_CFG_U5_STL_CTRL_DIGITAL_SELF_TEST1);
  if (!a) Serial.println("All Self-Test SUCCESS!");
  else  Serial.println("Self-Test Failed!");
  Serial.println("---Data from here---");
  delay(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  float a=0;
  fxps7xxx_get_pressure(&a);
  Serial.print("Pressue: ");
  Serial.println(a);
  fxps7xxx_get_temperature(&a);
  Serial.print("Temperature: ");
  Serial.println(a);
  delay(1000);
}
