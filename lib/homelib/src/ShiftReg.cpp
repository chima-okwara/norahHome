////////////////////////////////////////////////////////////////////////////////////////////////////
//*FILE NAME:       ShiftReg.cpp
//*FILE DESC:       Implementation file for GasSensor.
//*FILE VERSION:    0.1.1
//*FILE AUTHOR:     Chimaroke Okwara
//*LAST MODIFIED:   Monday, 3 April, 2023 19:35 (chima_okwara)
//*LICENSE:         Academic Free License
//////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include "home.h"

ShiftReg::ShiftReg(pin_t Data, pin_t Latch, pin_t Clock, const uint8_t &initValue) : _data(Data), _latch(Latch), _clock(Clock), _value(initValue)
{

}


void ShiftReg::begin()
{
    pinMode(_data, INPUT);
    pinMode(_latch, INPUT);
    pinMode(_clock, INPUT);

    shiftValue(_value);
}


void ShiftReg::shiftValue(const uint8_t& value)
{
        digitalWrite(_latch, LOW); //Latch low - start sending
        shiftOut(_data, _clock, MSBFIRST, value); //Shift most sig. bit first
        digitalWrite(_latch, HIGH);
}

void ShiftReg::shiftValue()
{
        digitalWrite(_latch, LOW); //Latch low - start sending
        shiftOut(_data, _clock, MSBFIRST, _value); //Shift most sig. bit first
        digitalWrite(_latch, HIGH);
}
