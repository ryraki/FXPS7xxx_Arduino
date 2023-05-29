# FXPS7xxx_Arduino
This library enables the developer to evaluate NXP FXPS7xxx with Arduino

## Usage of this library
Put your FXPS7xxx on your Arduino. Arduino Uno can adopt FXPS7xxx shield board without any changes.

## Functions
Please read example file first (example_FXPS7250_pressure_i2c or example_FXPS7250_pressure_spi).  
This library sets I2C address 0x60 at default.
First call init() function.  
Self test function can be called by fxps7xxx_startup_self_test. The arguments defined in fxps7xxx_regdef.h able to be used are below. Please read the datasheet for each meaning or behavior.  
FXPS7XXX_DSP_CFG_U5_STL_CTRL_P_CELL_MODE_VERIFICATION  
FXPS7XXX_DSP_CFG_U5_STL_CTRL_INHIBIT_SNS_DATA_X_WRITE0  
FXPS7XXX_DSP_CFG_U5_STL_CTRL_INHIBIT_SNS_DATA_X_WRITE1  
FXPS7XXX_DSP_CFG_U5_STL_CTRL_INHIBIT_SNS_DATA_X_WRITE2  
FXPS7XXX_DSP_CFG_U5_STL_CTRL_INHIBIT_SNS_DATA_X_WRITE3  
FXPS7XXX_DSP_CFG_U5_STL_CTRL_DIGITAL_SELF_TEST0  
FXPS7XXX_DSP_CFG_U5_STL_CTRL_DIGITAL_SELF_TEST1  
FXPS7XXX_DSP_CFG_U5_STL_CTRL_DIGITAL_SELF_TEST2  
FXPS7XXX_DSP_CFG_U5_STL_CTRL_DIGITAL_SELF_TEST3  

## Known Issues
This library is not used for 165, 400, 550kPa and Analog. Will be supported.

## Board information
FXPS7250D board: https://www.nxp.jp/design/software/development-software/sensor-toolbox-sensor-development-ecosystem/evaluation-boards/brktstbapx7250-evaluation-breakout-board-series:BRKTSTBAPx7250
