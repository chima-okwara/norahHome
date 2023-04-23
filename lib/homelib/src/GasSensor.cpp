////////////////////////////////////////////////////////////////////////////////////////////////////
//*FILE NAME:       GasSensor.cpp
//*FILE DESC:       Implementation file for GasSensor.
//*FILE VERSION:    0.1.1
//*FILE AUTHOR:     Chimaroke Okwara
//*LAST MODIFIED:   Monday, 3 April, 2023 19:35 (chima_okwara)
//*LICENSE:         Academic Free License
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include "home.h"
#ifndef GRES
#define GRES 12
#endif

GasSensor::GasSensor(pin_t signalPin, pin_t threshold) :_signalPin(signalPin), _threshold(threshold), _value(0)
{

}

void GasSensor::begin()
{
    pinMode(_signalPin, INPUT_ANALOG);
    analogReadResolution(GRES);
}

void GasSensor::measure()
{
    _threshold = _value;
    analogReadResolution(GRES);
    _value = analogRead(_signalPin);
}

bool GasSensor::gasDetect() const
{
    return ( (_value > _threshold) ? true : false);
}
