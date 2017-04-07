

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <Arduino.h>

#if defined(ARDUINO_ARCH_SAMD)
    #define Serial SerialUSB
#endif

/******************************************************************************
 * Serial Port Config
 *****************************************************************************/


// Serial port baud
#define SERIAL_BAUD_RATE                115200


#endif

