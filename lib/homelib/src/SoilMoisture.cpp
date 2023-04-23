////////////////////////////////////////////////////////////////////////////////////////////////////
//*FILE NAME:       SoilMoisture.cpp
//*FILE DESC:       Implementation file for Soil Moisture Sensor.
//*FILE VERSION:    0.1.1
//*FILE AUTHOR:     Chimaroke Okwara
//*LAST MODIFIED:   Saturday, 1 April, 2023 20:19
//*LICENSE:         Academic Free License
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include "home.h"
#ifndef SRES
#define SRES 12
#endif

SoilMoisture::SoilMoisture(const uint32_t& pin): _signalPin(pin), _moistureValue(0.0)
{

}

const float& SoilMoisture::measure()
{
    analogReadResolution(SRES);
    delayMicroseconds(30);
    auto value = analogRead(_signalPin);
    _moistureValue = (float(value) / 4096) * 3.3;
    _moistureValue = map(_moistureValue, 0, 4095, 0, 100);        //TODO: Verify this line
    return _moistureValue;
}


void SoilMoisture::begin()
{
    pinMode(_signalPin, INPUT_ANALOG);
    measure();
}

const float& SoilMoisture::getSoilMoisture()
{
    return _moistureValue;
}

