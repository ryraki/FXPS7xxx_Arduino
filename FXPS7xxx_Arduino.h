#ifndef _FXPS7xxx_Arduino_h
#define _FXPS7xxx_Arduino_h

#include "fxps7xxx_regdef.h"

#ifndef FXPS7xxx_I2C_ADDR
#define FXPS7xxx_I2C_ADDR (uint8_t)0x60
#endif

/*
 * Definition
 */

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

//fxps7xxx fixed self test register setting vs expected value table
const uint16_t fixed_st[] = {0x0, 0xAAAA, 0x5555, 0xFFFF};

//fxps7xxx digital self test  register setting vs expected value table
const uint16_t digital_st[] = {0x8171, 0x6C95, 0x807A, 0x78AC};

/*
 * Functions
 */
uint8_t fxps7xxx_init();
uint8_t fxps7xxx_get_pressure(float *pPressure);
uint8_t fxps7xxx_get_temperature(float *pTemperature);
uint8_t fxps7xxx_read_reg(uint16_t address, uint8_t num, uint8_t *pReadBuffer);
uint8_t fxps7xxx_write_reg(uint16_t address, uint8_t writeBuffer);
uint8_t fxps7xxx_startup_self_test(uint8_t mode);

#endif