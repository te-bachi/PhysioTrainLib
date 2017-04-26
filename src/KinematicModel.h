/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 25.04.2017
 */

#ifndef __KINEMATIC_MODEL_H__
#define __KINEMATIC_MODEL_H__

#include "Wire.h"
#include "IMU.h"
#include "Quaternion.h"
#include "Position.h"

class KinematicModel {
    public:

    private:
        TwoWire                 *_upperImu;
        IMU                     *_lowerImu;
        float                   _upperArmLength;
        float                   _lowerArmLength;
        Quaternion              _initUpperArmQuaternion;
        Quaternion              _initLowerArmQuaternion;
        Position                _upperArmPosition;
        Position                _lowerArmPosition;

    public:
                                KinematicModel();
                                KinematicModel(const KinematicModel& model);
        virtual                 ~KinematicModel();

        void                    begin(TwoWire *upperImu, IMU *lowerImu);
        void                    reinitialize();
        void                    update();
        void                    setUpperArmLength(float upperArmLength);
        void                    setLowerArmLength(float lowerArmLength);

    private:
        Quaternion              requestQuaternion();
};

#endif

