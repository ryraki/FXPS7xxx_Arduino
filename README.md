# FXPS7xxx_Arduino
This library enables the developer to evaluate NXP FXPS7xxx with Arduino

## Usage of this library
Put your FXPS7xxx I2C version (will adopt with SPI version) on your Arduino. Arduino Uno can adopt FXPS7xxx shield board without any changes.

## Functions
Please read example file first (example_temp_pressure).  
This library sets I2C address 0x60 at default. If the address is not suitable for your environment, please set the address by \#define FXPS7xxx_I2C_ADDR (uint8_t) your_address.  
First call fxps7xxx_init function.  
You can get the pressure and temperature by fxps7xxx_get_pressure and fxps7xxx_get_temperature functions, respectively.  
If you would like to read or write registers, call fxps7xxx_read_reg and fxps7xxx_write_reg functions, respectively. Write function only is for a single register. Will update for multiple registers.  
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
This library is not used for SPI version of FXPS7xxx. Will adopt those boards.

## Board information
FXPS7250D board: https://www.nxp.jp/design/software/development-software/sensor-toolbox-sensor-development-ecosystem/evaluation-boards/brktstbapx7250-evaluation-breakout-board-series:BRKTSTBAPx7250
