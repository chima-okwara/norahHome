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
#ifndef ARES
#define ARES 12
#endif

CurrentSensor::CurrentSensor(pin_t signalPin, const float& sensitivity) :_signalPin(signalPin), _sensitivity(sensitivity), _value(0)
{

}

void CurrentSensor::begin()
{
    analogRead(ARES);
    pinMode(_signalPin, INPUT_ANALOG);
}

void CurrentSensor::measure()
{
    static uint32_t raw = analogRead(_signalPin);
    float _value = (float(raw)- 512) / 4096.0 * 5000 / _sensitivity;     //TODO: VERIFY formula
}

float CurrentSensor::getValue() const
{
    return(_value);
}


