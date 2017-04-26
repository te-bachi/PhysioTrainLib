
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

    /* Send request to receive quaternion*/
    _upperImu->requestFrom(I2C_ADDRESS_RAZOR_SLAVE, 6);

    /* Slave may send less than requested... */
    for (i = 0; _upperImu->available() && i < 64; i++) {
        /* Receive a byte */
        buffer[i] = _upperImu->read();
    }

    /* Convert */
    q.setW(0.0f);
    q.setX(0.0f);
    q.setY(0.0f);
    q.setZ(0.0f);

    return q;
}
