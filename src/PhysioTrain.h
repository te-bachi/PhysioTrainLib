/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 02.05.2017
 */

#ifndef __PHYSIO_TRAIN_H__
#define __PHYSIO_TRAIN_H__

#include <Arduino.h>
#include <Wire.h>
#include "PhysioTrainLib.h"

extern CLI              cli;
extern IMU              imuLower;
extern IMU              imuUpper;
extern KinematicModel   model;

extern TwoWire          muxWire;

#define Wire1           muxWire
#define Wire3           Wire

class PhysioTrain {

    private:

    public:
        enum Mode {
            TEACH,
            EXERCISE,
            EVALUATE
        };

        static Mode MODE;

                    PhysioTrain();
        virtual     ~PhysioTrain();

    public:
        static void begin();

    private:
};

#endif
