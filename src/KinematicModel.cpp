
#include "config.h"
#include "KinematicModel.h"
#include "Transformation.h"

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
KinematicModel::begin(IMU *upperImu, IMU *lowerImu)
{
    this->_upperImu = upperImu;
    this->_lowerImu = lowerImu;
}

void
KinematicModel::reinitialize()
{
    /* Get quaternion from IMU */
    _initUpperArmQuaternion = _upperImu->getQuaternion();
    _initLowerArmQuaternion = _lowerImu->getQuaternion();

    /* Invert both */
    _initUpperArmQuaternion.inverse();
    _initLowerArmQuaternion.inverse();


}

void
KinematicModel::update()
{
    Quaternion      upperQ = _upperImu->getQuaternion();
    Quaternion      lowerQ = _lowerImu->getQuaternion();
    Position        p1;
    Position        p2(0.0f, 0.0f, -_upperArmLength);
    Position        p3(0.0f, 0.0f, -_lowerArmLength);
    RotationMatrix  rot1 = upperQ.getRotationMatrix();
    RotationMatrix  rot2 = lowerQ.getRotationMatrix();
    Transformation  t01(p1, rot1);
    Transformation  t02(p1, rot2);
    Transformation  t03(p1, rot2);


}

void
KinematicModel::setArmLength(float upperArmLength, float lowerArmLength)
{
    this->_upperArmLength = upperArmLength;
    this->_lowerArmLength = lowerArmLength;
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
