
#include "config.h"
#include "KinematicModel.h"

KinematicModel::KinematicModel()
: _upperImu(NULL), _lowerImu(NULL)
{

}

KinematicModel::KinematicModel(const KinematicModel& model)
: _upperImu(model._upperImu), _lowerImu(model._lowerImu)
{

}

KinematicModel::~KinematicModel()
{
    //
}

void
KinematicModel::begin(TwoWire *upperImu, IMU *lowerImu)
{
    this->_upperImu = upperImu;
    this->_lowerImu = lowerImu;
}

void
KinematicModel::reinitialize()
{
    float       qw = 0.0f;
    float       qx = 0.0f;
    float       qy = 0.0f;
    float       qz = 0.0f;


    /* Request quaternion from Razor slave*/
    _initUpperArmQuaternion = requestQuaternion();

    /* Read quaternion from own IMU */
    _initLowerArmQuaternion = _lowerImu->getQuaternion();


}

void
KinematicModel::update()
{
    /*
    Quaternion      upperQ = requestQuaternion();
    Quaternion      lowerQ = _lowerImu->getQuaternion();
    Position        p1;
    Position        p2(0.0f, 0.0f, -_upperArmLength);
    Position        p3(0.0f, 0.0f, -_lowerArmLength);
    RotationMatrix  rot1 = _lo;
    RotationMatrix  rot2();
    RotationMatrix  rot3();
    Transformation t01()
    */
}

void
KinematicModel::setUpperArmLength(float upperArmLength)
{
    this->_upperArmLength = upperArmLength;
}

void
KinematicModel::setLowerArmLength(float lowerArmLength)
{
    this->_lowerArmLength = lowerArmLength;
}

Quaternion
KinematicModel::requestQuaternion()
{
    Quaternion  q;
    char        buffer[64];
    int         i;

    /* Multiplexer Select Razor Slave */
    _upperImu->beginTransmission(I2C_ADDRESS_I2C_MULTIPLEXER);
    _upperImu->write(1 << I2C_MULTIPLEXER_RAZOR_SLAVE);
    _upperImu->endTransmission();


    return q;
}
