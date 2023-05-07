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

GasSensor::GasSensor(pin_t signalPin) :_signalPin(signalPin), _value(0), _concentration(0), _isGas(false)
{

}

void GasSensor::begin()
{
    pinMode(_signalPin, INPUT_ANALOG);
    analogReadResolution(GRES);
}

void GasSensor::measure()
{
    analogReadResolution(GRES);
    _value = analogRead(_signalPin);
    _value = _value * (5.0 / 4096.0);
    _concentration = _value / (5.0 / 1000);
    _isGas = (_concentration > 1000.0) ? true : false;
}

bool GasSensor::gasDetect() const
{
    return (_isGas) ? true : false;
}
