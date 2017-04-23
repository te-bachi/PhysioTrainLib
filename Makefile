LIBRARIES_STATIC            = 
PROGRAMS                    = physiotrain

GLOBAL_CFLAGS               = -Wall -ggdb
GLOBAL_LDFLAGS              = 

### LIBRARIES #################################################################


### PROJECT2 ##################################################################

physiotrain_CFLAGS       = 
physiotrain_LDFLAGS      = 
physiotrain_LIBRARIES    = 
physiotrain_SOURCE       = PhysioTrain.cpp \
                           Acceleration.cpp \
                           EulerAngle.cpp \
                           Filter.cpp \
                           Quaternion.cpp \
                           Position.cpp \
                           RotationMatrix.cpp \
                           Transformation.cpp
                           


include autogen.mk