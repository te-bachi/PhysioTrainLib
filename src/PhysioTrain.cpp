
#include "PhysioTrain.h"
#include "config.h"

// pinPeripheral() function
#include "wiring_private.h"

CLI             cli;
IMU             imuLower(IMU_SELECT_INTERNAL);
IMU             imuUpper(IMU_SELECT_EXTERNAL);
KinematicModel  model;

TwoWire         muxWire(&sercom1, 11, 13);


PhysioTrain::PhysioTrain()
{
    //
}

PhysioTrain::~PhysioTrain()
{
    //
}

static void countdown()
{
    for (int i = 5; i > 0; i--) {
        Serial.println(i);
        delay(1000);
    }
}

void PhysioTrain::begin()
{
    Serial.begin(SERIAL_BAUD_RATE);

    countdown();

    Wire3.begin(); // SERCOM3 => internal IMU
    Wire1.begin(); // SERCOM1 => external I2C Multiplexer
    pinPeripheral(11, PIO_SERCOM);
    pinPeripheral(13, PIO_SERCOM);

    cli.begin();
    imuLower.begin();
    imuUpper.begin();
    //model.begin(&Wire3, &imuLower);
}
