#ifndef _PERIPHERY_H_
#define _PERIPHERY_H_

#include <Arduino.h>

class Periphery
{
    public :
        Periphery (uint8_t pin, uint16_t delay, uint16_t time_shift = 0) {
            _pin = pin;
            _delay = delay;
            _time_shift = time_shift;
            pinMode(pin, OUTPUT);
        }

        bool _status = false;
        bool _initiated = true;
        uint16_t _time_shift = 0;
        uint8_t _pin;
        uint16_t _delay;
        uint32_t _start = millis();
};
#endif