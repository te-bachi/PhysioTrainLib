
#include "config.h"
#include "CLI.h"

CLI::CLI()
{
    //
}

CLI::~CLI()
{
    //
}

bool
CLI::begin()
{
    Serial.begin(SERIAL_BAUD_RATE);

    uint32_t bkla;

    /*
    main    = MenuMain(this);
    file    = MenuFile(this);
    run     = MenuRun(this);
    */
    main.begin(this);
    file.begin(this);
    run.begin(this);
    current = &main;
    
    
    return true;
}

void
CLI::update()
{
    // Checks for new serial input:
    if (Serial.available()) {
        // If new input is available on serial port
        current->parse(Serial.read());
    }
}


    /*
    String imuLog = ""; // Create a fresh line to log
    
    imuLog += String(imu.time) + ", ";
    
    imu.computeEulerAngles();
    imuLog += String(imu.pitch, 2) + ", ";
    imuLog += String(imu.roll, 2) + ", ";
    imuLog += String(imu.yaw, 2) + ", ";
    imuLog += String(imu.computeCompassHeading(), 2) + ", ";

    // Blink LED once every second (if only logging to serial port)
    if (millis() > lastBlink + UART_BLINK_RATE) {
        blinkLED(); 
        lastBlink = millis();
    }
    */
