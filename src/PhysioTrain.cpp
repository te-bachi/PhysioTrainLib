
#include "PhysioTrain.h"
#include "Mode.h"
#include "config.h"

// pinPeripheral() function
#include "wiring_private.h"

CLI             cli;
IMU             imuLower(IMU_SELECT_INTERNAL);
IMU             imuUpper(IMU_SELECT_EXTERNAL);
KinematicModel  model;

TwoWire         muxWire(&sercom1, 11, 13);
SX1509          ioExpander;
RTC_DS3231      rtc;
//Timer           timer; // using millis() rather than the Timer object

StateMachine    stateMachine;
Switch          recordSwitch;
PushButton      startStopButton;
RotarySwitch    modeSwitch;

File            teachFile;
File            exerciseFile;
File            resultFile;

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
        SerialUSB.println(i);
        delay(1000);
    }
}

void PhysioTrain::begin()
{
    SerialUSB.begin(SERIAL_BAUD_RATE);

    countdown();

    Wire3.begin();                  // SERCOM3 => internal IMU
    Wire1.begin();                  // SERCOM1 => external I2C Multiplexer
    pinPeripheral(11, PIO_SERCOM);  // Assign D11 to SERCOM
    pinPeripheral(13, PIO_SERCOM);  // Assign D13 to SERCOM

    I2CMux::selectGpioExpander();
    ioExpander.begin(&Wire1);
    recordSwitch.begin(&ioExpander, IO_IN_SWITCH_RECORD);
    startStopButton.begin(&ioExpander, IO_IN_PUSHBUTTON_START_STOP);
    modeSwitch.begin(&ioExpander, IO_IN_ROTARYSWITCH_TEACH, IO_IN_ROTARYSWITCH_EXERCISE, IO_IN_ROTARYSWITCH_EVALUATE);

    I2CMux::selectRtc();
    rtc.begin();

    cli.begin();
    imuLower.begin();
    imuUpper.begin();

    model.begin(&imuUpper, &imuLower);
    model.setArmLength(KINEMATIK_UPPER_ARM_LENGTH, KINEMATIK_LOWER_ARM_LENGTH);
}
