/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 07.04.2017
 */

#ifndef __CONFIG_H__
#define __CONFIG_H__

#ifdef ARDUINO
#include <Arduino.h>
#endif

#if defined(ARDUINO_ARCH_SAMD)
    #define Serial SerialUSB
#endif

/******************************************************************************
 * Serial Port Config
 *****************************************************************************/


// Serial port baud
#define SERIAL_BAUD_RATE                115200


#endif

