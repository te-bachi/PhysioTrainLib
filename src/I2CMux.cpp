
#include "config.h"
#include "I2CMux.h"

#include <Wire.h>

extern TwoWire muxWire;

I2CMux::I2CMux()
{

}

I2CMux::~I2CMux()
{

}

void
I2CMux::select(int channel)
{
//    Serial.print("I2CMux::select(0x");
//    Serial.print(I2C_ADDRESS_I2C_MULTIPLEXER, HEX);
//    Serial.print(" => ");
//    Serial.print(channel, DEC);
//    Serial.print(")\n");
    muxWire.beginTransmission(I2C_ADDRESS_I2C_MULTIPLEXER);
    muxWire.write(1 << channel);
    muxWire.endTransmission();
}

void
I2CMux::selectGpioExpander()
{
    select(I2C_MULTIPLEXER_GPIO_EXPANDER);
}

void
I2CMux::selectRtc()
{
    select(I2C_MULTIPLEXER_RTC);
}

void
I2CMux::selectVibra()
{
    select(I2C_MULTIPLEXER_VIBRA);
}

void
I2CMux::selectRazorSlave()
{
    select(I2C_MULTIPLEXER_RAZOR_SLAVE);
}
