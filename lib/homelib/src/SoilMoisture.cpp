////////////////////////////////////////////////////////////////////////////////////////////////////
//*FILE NAME:       home.h
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

SoilMoisture::SoilMoisture(const uint32_t& pin, const uint32_t& power): _signalPin(new uint32_t (pin)), _powerPin(new uint32_t (power)), __moistureValue(new float (0.0))
{

}

const float& SoilMoisture::measure()
{
    analogReadResolution(SRES);
    digitalWrite(_powerPin, HIGH);
    delayMicroseconds(30);
    auto value = analogRead(_signalPin);
    *_moistureValue = (float(value) / 4096) * 3.3;
    *_moistureValue = map(*_moistureValue, 0, 4095, 0, 100);        //TODO: Verify this line
    return *_moistureValue;
}


void SoilMoisture::begin()
{
    pinMode(_signalPin, INPUT_ANALOG);
    pinMode(_powerPin, INPUT_PULLDOWN);
    measure();
}

const float& SoilMoisture::getSoilMoisture()
{
    return *_moistureValue;
}

SoilMoisture::~SoilMoisture()
{
    delete _moistureValue;
    _moistureValue = nullptr;
}
