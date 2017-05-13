
#include <Arduino.h>
#include "Switch.h"
#include "I2CMux.h"
#include "config.h"

Switch::Switch()
: _ioExpander(NULL), _prev(0), _pos(false), _value(false)
{

}

Switch::~Switch()
{

}

void
Switch::begin(SX1509 *ioExpander, int pin)
{
    _ioExpander = ioExpander;
    _pin        = pin;

    I2CMux::selectGpioExpander();
    _ioExpander->pinMode(_pin, INPUT);
    _value = _ioExpander->digitalRead(_pin);
}


bool
Switch::getValue()
{
    bool    pos;
    int     curr = millis();
    int     prev = _prev;

    if (prev == 0 || (curr - prev) > TIME_DEBOUNCING_DELAY_MS) {
        I2CMux::selectGpioExpander();
        pos = _ioExpander->digitalRead(_pin);

        /* switch is pressed */
        if (pos == HIGH && pos != _pos) {
            /* invert value */
            _value = !_value;
        }
        _pos = pos;
    }

    return _value;
}
