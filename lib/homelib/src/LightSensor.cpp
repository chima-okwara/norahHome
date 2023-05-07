////////////////////////////////////////////////////////////////////////////////////////////////////
//*FILE NAME:       home.h
//*FILE DESC:       Implementation file for GasSensor.
//*FILE VERSION:    0.1.1
//*FILE AUTHOR:     Chimaroke Okwara
//*LAST MODIFIED:   Monday, 3 April, 2023 19:35 (chima_okwara)
//*LICENSE:         Academic Free License
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include "home.h"
#ifndef LRES
#define LRES 12
#endif

LightSensor::LightSensor(pin_t signalPin):_signalPin(signalPin)
{

}

void LightSensor::begin()
{
    pinMode(_signalPin, INPUT_ANALOG);
    analogReadResolution(LRES);
}

const bool& LightSensor::measure(uint32_t level)
{
    analogReadResolution(LRES);
    static uint32_t raw = analogRead(_signalPin);
    raw = map(raw, 0, 4096, 0, 10);
    _state = ( raw >= level) ? true : false;        //TODO: Verify formula
    return(_state);
}

const bool& LightSensor::isLight()
{
    return (_state) ? true : false;
}

const bool& LightSensor::isDark()
{
    return (!_state) ? true : false;
}
