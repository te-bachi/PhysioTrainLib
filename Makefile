
@LOUD = 1
LIBRARIES_STATIC            = 
PROGRAMS                    = physiotrain

GLOBAL_CFLAGS               = -Wall -ggdb
GLOBAL_LDFLAGS              = 

MKDIR_LIST                  = obj/physiotrain/test

### LIBRARIES #################################################################


### PROJECT2 ##################################################################

physiotrain_CFLAGS       = -Isrc -Isrc/test
physiotrain_LDFLAGS      = 
physiotrain_LIBRARIES    = 
physiotrain_SOURCE       = Acceleration.cpp \
                           EulerAngle.cpp \
                           Filter.cpp \
                           I2CMux.cpp \
                           Position.cpp \
                           RotationMatrix.cpp \
                           IMU.cpp \
                           KinematicModel.cpp \
                           Mode.cpp \
                           Quaternion.cpp \
                           QuaternionFixedPoint.cpp \
                           StateMachine.cpp \
                           Transformation.cpp \
                           test/PhysioTrainTest.cpp \
                           test/Wire.cpp \
                           test/WString.cpp \
                           test/SparkFunMPU9250-DMP.cpp \
                           test/itoa.cpp \
                           test/avr/dtostrf.cpp \
                           


include autogen.mk