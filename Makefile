
#LOUD = 1
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
physiotrain_SOURCE       = test/itoa.cpp \
                           test/avr/dtostrf.cpp \
                           test/PhysioTrain.cpp \
                           test/WString.cpp \
                           Acceleration.cpp \
                           EulerAngle.cpp \
                           Filter.cpp \
                           Quaternion.cpp \
                           Position.cpp \
                           RotationMatrix.cpp \
                           Transformation.cpp
                           


include autogen.mk