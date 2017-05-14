/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 02.05.2017
 */

#ifndef __PHYSIO_TRAIN_H__
#define __PHYSIO_TRAIN_H__

#include <Arduino.h>
#include <Wire.h>
#include <SD.h>

#include "SparkFunSX1509.h"
#include "RTClib.h"
#include "PhysioTrainLib.h"

#define Wire1           muxWire
#define Wire3           Wire

extern CLI              cli;
extern IMU              imuLower;
extern IMU              imuUpper;
extern KinematicModel   model;

extern TwoWire          muxWire;
extern SX1509           ioExpander;
extern RTC_DS3231       rtc;

//extern Timer            timer; // using millis() rather than the Timer object

extern StateMachine     stateMachine;
extern Switch           recordSwitch;
extern PushButton       startStopButton;
extern RotarySwitch     modeSwitch;

extern File             teachFile;
extern File             exerciseFile;
extern File             resultFile;

class PhysioTrain {

    private:

    public:
                    PhysioTrain();
        virtual     ~PhysioTrain();

    public:
        static void begin();

    private:
};

#endif

