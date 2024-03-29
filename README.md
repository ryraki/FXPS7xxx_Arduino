# FXPS7xxx_Arduino
This library enables the developer to evaluate NXP FXPS7xxx with Arduino

> **Note**
Known Issue: This library doesn't fully support 165, 400, 550kPa devices though the library still be functionable for these devices. Will be fully supported.

## Usage of this library
Put your FXPS7xxx on your Arduino. Arduino Uno can adopt FXPS7xxx shield board without any changes.

## Datasheet and Board Information
Output|Supported?|Device Information|Datasheet|Board Information
---|---|---|---|---
Digital|YES|[FXPS7115D4(S)](https://www.nxp.com/products/sensors/pressure-sensors/barometric-pressure-15-to-150-kpa/automotive-engine-management-and-fuel-efficiency-control-absolute-pressure-sensor-40-to-115-kpa:FXPS7115D4)|[FXLS7115D4S.pdf](https://www.nxp.com/docs/en/data-sheet/FXPS7115D4S.pdf)  [FXLS7115D4.pdf](https://www.nxp.com/docs/en/data-sheet/FXPS7115D4.pdf)|Device Sample + [BRKFXPS7XXX-PCB + FRDM7X-INTERFACE](https://www.nxp.com/design/software/sensor-toolbox/evaluation-boards/brktstbapx7250-evaluation-breakout-board-series:BRKTSTBAPx7250)
Digital|Partially|[FXPS7165D4(S)](https://www.nxp.com/products/sensors/pressure-sensors/lpg-and-cng-gas-20-to-550-kpa/digital-absolute-pressure-sensor-20-to-550-kpa:FXPS7xx0D4)|[FXLS7165D4S.pdf](https://www.nxp.com/docs/en/data-sheet/FXPS7165D4S.pdf)  [FXLS7165D4.pdf](https://www.nxp.com/docs/en/data-sheet/FXPS7165D4.pdf)|Device Sample + [BRKFXPS7XXX-PCB + FRDM7X-INTERFACE](https://www.nxp.jp/design/software/sensor-toolbox/evaluation-boards/brktstbapx7250-evaluation-breakout-board-series:BRKTSTBAPx7250)
Digital|YES|[FXPS7250D4(S)](https://www.nxp.com/products/sensors/pressure-sensors/lpg-and-cng-gas-20-to-550-kpa/digital-absolute-pressure-sensor-20-to-550-kpa:FXPS7xx0D4)|[FXLS7250D4S.pdf](https://www.nxp.com/docs/en/data-sheet/FXPS7250D4S.pdf)  [FXLS7250D4.pdf](https://www.nxp.com/docs/en/data-sheet/FXPS7250D4.pdf)|[BRKTSTBAPDI7250/BRKTSTBAPDS7250 + FRDM7X-INTERFACE](https://www.nxp.jp/design/software/sensor-toolbox/evaluation-boards/brktstbapx7250-evaluation-breakout-board-series:BRKTSTBAPx7250)
Digital|Partially|[FXPS7400D4(S)](https://www.nxp.com/products/sensors/pressure-sensors/lpg-and-cng-gas-20-to-550-kpa/digital-absolute-pressure-sensor-20-to-550-kpa:FXPS7xx0D4)|[FXLS7400D4S.pdf](https://www.nxp.com/docs/en/data-sheet/FXPS7400D4S.pdf)  [FXLS7400D4.pdf](https://www.nxp.com/docs/en/data-sheet/FXPS7400D4.pdf)|Device Sample + [BRKFXPS7XXX-PCB + FRDM7X-INTERFACE](https://www.nxp.jp/design/software/sensor-toolbox/evaluation-boards/brktstbapx7250-evaluation-breakout-board-series:BRKTSTBAPx7250)
Digital|Partially|[FXPS7550D4(S)](https://www.nxp.com/products/sensors/pressure-sensors/lpg-and-cng-gas-20-to-550-kpa/digital-absolute-pressure-sensor-20-to-550-kpa:FXPS7xx0D4)|[FXLS7550D4S.pdf](https://www.nxp.com/docs/en/data-sheet/FXPS7550D4S.pdf)  [FXLS7550D4.pdf](https://www.nxp.com/docs/en/data-sheet/FXPS7550D4.pdf)|Device Sample + [BRKFXPS7XXX-PCB + FRDM7X-INTERFACE](https://www.nxp.jp/design/software/sensor-toolbox/evaluation-boards/brktstbapx7250-evaluation-breakout-board-series:BRKTSTBAPx7250)
Analog|YES|[FXPS7250A4(S)](https://www.nxp.com/products/sensors/pressure-sensors/lpg-and-cng-gas-20-to-550-kpa/analog-absolute-pressure-sensor-20-to-550-kpa:FXPS7xx0A4)|[FXLS7250A4S.pdf](https://www.nxp.com/docs/en/data-sheet/FXPS7250A4S.pdf)  [FXLS7250A4.pdf](https://www.nxp.com/docs/en/data-sheet/FXPS7250A4.pdf)|[BRKTSTBAPA7250S + FRDM7X-INTERFACE](https://www.nxp.jp/design/software/sensor-toolbox/evaluation-boards/brktstbapx7250-evaluation-breakout-board-series:BRKTSTBAPx7250)
Analog|Partially|[FXPS7400A4(S)](https://www.nxp.com/products/sensors/pressure-sensors/lpg-and-cng-gas-20-to-550-kpa/analog-absolute-pressure-sensor-20-to-550-kpa:FXPS7xx0A4)|[FXLS7400A4S.pdf](https://www.nxp.com/docs/en/data-sheet/FXPS7400A4S.pdf)  [FXLS7400A4.pdf](https://www.nxp.com/docs/en/data-sheet/FXPS7400A4.pdf)|Device Sample + [BRKFXPS7XXX-PCB + FRDM7X-INTERFACE](https://www.nxp.jp/design/software/sensor-toolbox/evaluation-boards/brktstbapx7250-evaluation-breakout-board-series:BRKTSTBAPx7250)
Analog|Partially|[FXPS7550A4(S)](https://www.nxp.com/products/sensors/pressure-sensors/lpg-and-cng-gas-20-to-550-kpa/analog-absolute-pressure-sensor-20-to-550-kpa:FXPS7xx0A4)|[FXLS7550A4S.pdf](https://www.nxp.com/docs/en/data-sheet/FXPS7550A4S.pdf)  [FXLS7550A4.pdf](https://www.nxp.com/docs/en/data-sheet/FXPS7550A4.pdf)|Device Sample + [BRKFXPS7XXX-PCB + FRDM7X-INTERFACE](https://www.nxp.jp/design/software/sensor-toolbox/evaluation-boards/brktstbapx7250-evaluation-breakout-board-series:BRKTSTBAPx7250)

## How to use
Use Library manager pane in Arduino IDE (the books mark), put this library name (FXPS7xxx_Arduino) and click INSTALL button. This library is copied to your Arduino library folder (default: &lt;Your Documents folder&gt;\Arduino\libraries).  
You can find example codes inside this library by selecting from [File]-&gt;[Examples]-&gt;[FXLS89xx_Arduino].  
Please see the documents of [docs/class_f_x_p_s7xxx___arduino.html](https://ryraki.github.io/FXPS7xxx_Arduino/class_f_x_p_s7xxx___arduino.html) in order to get the information of all the functions.

## What are inside in this library?
### List of contents
Category|Folder|Features
---|---|---
Example|[examples/example_FXPS7250_pressure_analog/example_FXPS7250_pressure_analog.ino](examples/example_FXPS7250_pressure_analog/example_FXPS7250_pressure_analog.ino)|Example codes to read the pressure data from FXPS7250A4(S).
Example|[examples/example_FXPS7250_pressure_i2c/example_FXPS7250_pressure_i2c.ino](examples/example_FXPS7250_pressure_i2c/example_FXPS7250_pressure_i2c.ino)|Example codes to read the pressure data from FXPS7250DI4(S) (I2C version of FXPS7250D4(S)).
Example|[examples/example_FXPS7250_pressure_spi/example_FXPS7250_pressure_spi.ino](examples/example_FXPS7250_pressure_spi/example_FXPS7250_pressure_spi.ino)|Example codes to read the pressure data from FXPS7250DS4(S) (SPI version of FXPS7250D4(S)).
Documents|docs/&lt;All data inside the folder&gt;|The documents generated by Doxygen. Please see the link: [docs/class_f_x_p_s7xxx___arduino.html](https://ryraki.github.io/FXPS7xxx_Arduino/class_f_x_p_s7xxx___arduino.html)
Source|[src/FXPS7xxx_Arduino.cpp](src/FXPS7xxx_Arduino.cpp)|The C++ file for this library.
Source|[src/FXPS7xxx_Arduino.h](src/FXPS7xxx_Arduino.h)|The header file for FXPS7xxx_Arduino.cpp.
Source|[src/fxps7xxx.h](src/fxps7xxx.h)|The header for register definition made by NXP.
Arduino|keywords.txt|Keywords data only used for Arduino IDE 1.x.
Arduino|library.properties|Library properties used by Arduino and its Library manager.
Other|Doxyfile|For Doxygen
Other|LICENSE|License data. This is BSD 3-Clause.
Other|README.md|This file.

### Known Issues
This library doesn't contain the pressure calculation data for the devices that indicates "Partially" in the list above. Will update soon.

### Functions
Please read example file first (example_FXPS7250_pressure_i2c or example_FXPS7250_pressure_spi).  
This library sets I2C address 0x60 at default.  
First initialize the class and call begin() function.  
For SPI version, the user must set SOURCEID_0 or 1 to use get_pressure_sensor_data_request(SOURCEID) function.

#### About Self test function
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
