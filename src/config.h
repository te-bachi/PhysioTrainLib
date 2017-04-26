/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 07.04.2017
 */

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <Arduino.h>

/******************************************************************************
 * Serial Port Config
 *****************************************************************************/

#if defined(ARDUINO_ARCH_SAMD)
    #define Serial SerialUSB
#endif

// Serial port baud
#define SERIAL_BAUD_RATE                115200


/******************************************************************************
 * I2C
 *****************************************************************************/

#define I2C_ADDRESS_I2C_MULTIPLEXER     0x68
#define I2C_ADDRESS_GPIO_EXPANDER       0x68
#define I2C_ADDRESS_RTC                 0x68
#define I2C_ADDRESS_VIBRA               0x68
#define I2C_ADDRESS_RAZOR_SLAVE         0x68

#define I2C_MULTIPLEXER_GPIO_EXPANDER   2
#define I2C_MULTIPLEXER_RTC             3
#define I2C_MULTIPLEXER_VIBRA           4
#define I2C_MULTIPLEXER_RAZOR_SLAVE     5

#endif

