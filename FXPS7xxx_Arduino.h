/*
 * Copyright 2023 ryrak
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
 
/**
 * @file FXPS7xxx_Arduino.h
 * @brief This file is the header for FXPS7xxx_Arduino
 */
 
#ifndef _FXPS7XXX_ARDUINO_H
#define _FXPS7XXX_ARDUINO_H

#include "fxps7xxx_regdef.h"
#include <SPI.h>
#include <Arduino.h>

#define FXPS7XXX_I2C FXPS7xxx_Arduino::communicationInterface::_I2C
#define FXPS7XXX_SPI FXPS7xxx_Arduino::communicationInterface::_SPI
#define FXPS7XXX_ANA FXPS7xxx_Arduino::communicationInterface::_ANA

#define FXPS7XXX_SPI_R static_cast<uint8_t>(FXPS7xxx_Arduino::command_SPI::_SPI_R)
#define FXPS7XXX_SPI_W static_cast<uint8_t>(FXPS7xxx_Arduino::command_SPI::_SPI_W)

#define P_RANGE static_cast<uint8_t>(P_range)

#define FXPS7115S FXPS7XXX_SPI,FXPS7xxx_Arduino::pressureRange::P115  //!< @brief Used for FXPS7115D4 SPI version at constructor 
#define FXPS7115I FXPS7XXX_I2C,FXPS7xxx_Arduino::pressureRange::P115  //!< @brief Used for FXPS7115D4 I2C version at constructor 
#define FXPS7250S FXPS7XXX_SPI,FXPS7xxx_Arduino::pressureRange::P250  //!< @brief Used for FXPS7250D4 SPI version at constructor 
#define FXPS7250I FXPS7XXX_I2C,FXPS7xxx_Arduino::pressureRange::P250  //!< @brief Used for FXPS7250D4 SPI version at constructor 

#define FXPS7XXX_DEBUG 1

/**
* @brief Class to evaluate FXPS7xxxD4
*/
class FXPS7xxx_Arduino {
  public:
    uint8_t debug=0;                                        //!< @brief Debug mode (1 to indicate sent/received hex data in serial)
    enum class communicationInterface {_SPI, _I2C, _ANA};   //!< @brief Communication interface
    enum class pressureRange {P115=0, P250=1};              //!< @brief Pressure range setting. Other pressure range to be supported later (165, 400, 550).
    enum class command_SPI {_SPI_R = 0xC0, _SPI_W = 0x80};  //!< @brief SPI command

    communicationInterface comType;                         //!< @brief Variable to indicate communication interface
    pressureRange P_range;                                  //!< @brief Variable to indicate pressure range

    uint8_t sourceid0, sourceid1, num_sensor_data=0;        //!< @brief SPI Only: Source ID and which sensor to obtain data from
    SPISettings spi_settings = SPISettings(100000, MSBFIRST, SPI_MODE0); //!< @brief SPI Only: Settings to use in SPI mode
    uint8_t spi_ss = SS;                                    //!< @brief SPI Only: /CS pin to use
    uint8_t spi_txdata[4];                                  //!< @brief SPI Only: TX data
    uint8_t spi_rxdata[4];                                  //!< @brief SPI Only: RX data

    uint8_t I2C_address = 0x60;                             //!< @brief Variable to indicate I2C address, default to be 0x60

    const uint16_t fixed_st[4] = {0x0, 0xAAAA, 0x5555, 0xFFFF};       //!< @brief Self-Test for fixed
    const uint16_t digital_st[4] = {0x8171, 0x6C95, 0x807A, 0x78AC};  //!< @brief Self-Test for digital
    
    const float PABSOFF_12sdr[2]    = {-1567.8, -4.2};      //!< @brief Offset coefficient to be used at 12-bit Sensor data request command
    const float PABS_sense_12sdr[2] = {46.67, 15.21};       //!< @brief Sensitivity coefficient to be used at 12-bit Sensor data request command
    const float PABSOFF_16reg[2]    = {25536, 28661.6};     //!< @brief Offset coefficient to be used at Register read command
    const float PABS_sense_16reg[2] = {93.34, 30.42};       //!< @brief Sensitivity coefficient to be used at Register read command
    const float PABSOFF_16sdr[2]    = {-25084.8, 67.41};    //!< @brief Offset coefficient to be used at 16-bit Sensor data request command
    const float PABS_sense_16sdr[2] = {746.72, 243.36};     //!< @brief Sensitivity coefficient to be used at 16-bit Sensor data request command

    /**
    * @brief Initialization function: Execute once after definition
    */
    uint8_t init();


    /**
    * @brief Reset function: To send 00->11->01 to DEVLOCK_WR[RESET]
    */
    void FXPS7xxx_Arduino::reset();
    
    /**
    * @brief Register read function: Interface is selected automatically
    * @param Register address to access
    * @param Number of register to be read
    * @param Pointer to array to store register contents
    * @return Status (sensor_error_type)
    */
    uint8_t read_reg(uint8_t address, uint8_t num, uint8_t *pReadBuffer);
    
    /**
    * @brief Register read function for I2C: Called by read_reg() function
    * @param Register address to access
    * @param Number of register to be read
    * @param Pointer to array to store register contents
    * @return Status (sensor_error_type)
    */
    uint8_t read_reg_i2c(uint8_t address, uint8_t num, uint8_t *pReadBuffer);
    
    /**
    * @brief Register read function for SPI: Called by read_reg() function
    * @param Register address to access
    * @param Number of register to be read
    * @param Pointer to array to store register contents
    * @return Status (sensor_error_type)
    */
    uint8_t read_reg_spi(uint8_t address, uint8_t num, uint8_t *pReadBuffer);
    
    
    /**
    * @brief Register write function: Interface is selected automatically
    * @param Register address to access
    * @param Content to be written
    * @return Status (sensor_error_type)
    */
    uint8_t write_reg(uint8_t address, uint8_t writeBuffer);
    
    /**
    * @brief Register write function for I2C: Called by write_reg() function, calls access_reg_spi()
    * @param Register address to access
    * @param Content to be written
    * @return Status (sensor_error_type)
    */
    uint8_t write_reg_i2c(uint8_t address, uint8_t writeBuffer);
    
    /**
    * @brief Register write function for SPI: Called by write_reg() function, calls access_reg_spi()
    * @param Register address to access
    * @param Content to be written
    * @return Status (sensor_error_type)
    */
    uint8_t write_reg_spi(uint8_t address, uint8_t writeBuffer);
    
    /**
    * @brief Register access function: SPI command is complex, so this function wraps SPI communication
    * @param Pointer to contents to be sent
    * @return Status (sensor_error_type)
    */
    uint8_t access_reg_spi(uint8_t *p_spi_txdata);


    /**
    * @brief Sensor data request command: SPI Only, takes 16-bit or 12-bit sensor data
    * @param Sensor number: Which sensor to access, 0 or 1
    * @return Pressure data (float)
    */
    float get_pressure_sensor_data_request(uint8_t sourceid);
    
    /**
    * @brief Function to read pressure data by register: Takes 16-bit sensor data by reading SNSDATAx_y
    * @param Sensor number: Which sensor to access, 0 or 1
    * @return Pressure data (float)
    */
    float get_pressure(uint8_t sensor);
    
    /**
    * @brief Function to read pressure data by register: Takes temperature data by reading TEMPERATURE
    * @param Sensor number: Which sensor to access, 0 or 1
    * @return Temperature data in unit of degC (Signed int16)
    */
    int16_t get_temperature();
    
    /**
    * @brief Function to activate self-test
    * @param Self-Test Mode
    * @return Status (sensor_error_type)
    */
    uint8_t self_test(uint8_t mode);
    
    /**
    * @brief Function to calculate CRC8, normally only used in SPI
    * @param Pointer to calculate CRC
    * @return CRC result
    */
    uint8_t u8Crc_Calculate(uint8_t *p_u8_cmd_msg);

    /**
    * @brief Constructor for FXPS7xxx_Arduino: Device type is selected from definition
    * @param Communication interface type: Selected from FXPS7XXX_I2C, FXPS7XXX_SPI, or FXPS7XXX_ANA
    * @param Pressure range: Selected from P_RANGE
    */
    FXPS7xxx_Arduino(communicationInterface _comType, pressureRange _P_range) {
      comType = _comType;
      P_range = _P_range;
    }

    /**
    * @brief Constructor for FXPS7xxx_Arduino with debug mode: Device type is selected from definition
    * @param Communication interface type: Selected from FXPS7XXX_I2C, FXPS7XXX_SPI, or FXPS7XXX_ANA
    * @param Pressure range: Selected from P_RANGE
    * @param debug mode (1 to show raw communication data in serial, Only available at SPI)
    */
    FXPS7xxx_Arduino(communicationInterface _comType, pressureRange _P_range, uint8_t _debug) {
      comType = _comType;
      P_range = _P_range;
      debug   = _debug;
    }
};

typedef enum sensor_error_type
{
    SENSOR_SUCCESS           = 0,  /*!< Success value returned by sensor APIs. */
    SENSOR_INVALIDPARAM_ERR  = 1,  /*!< Invalid Param Error value by SENSOR APIs. */
    SENSOR_INIT_ERR          = 2,  /*!< SENSOR Init Error value returned by Init API. */
    SENSOR_WRITE_ERR         = 3,  /*!< SENSOR Write Error value returned by Write API. */
    SENSOR_READ_ERR          = 4,  /*!< SENSOR Read Error value returned by Read API. */
    SENSOR_BAD_ADDRESS       = 5,  /*!< SENSOR Error value returned for bad address access. */
    FXPS7XXX_DEVICE_NOT_FOUND = 6,  /*!< Device not found, wrong who I am value.*/
    FXPS7XXX_DEVICE_ERROR     = 7,  /*!< Device error, Wrong data.*/
    FXPS7XXX_REGION_ERROR     = 8,  /*!< Device region error.*/
    FXPS7xxx_ST_FAILED        = 9,  /*!< Self Test is failed.*/
} error_type_t;

#endif