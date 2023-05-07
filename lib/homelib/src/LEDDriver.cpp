////////////////////////////////////////////////////////////////////////////////////////////////////
//*FILE NAME:       home.h
//*FILE DESC:       Implementation file for LEDDriver.
//*FILE VERSION:    0.1.1
//*FILE AUTHOR:     Chimaroke Okwara
//*LAST MODIFIED:   Saturday, 1 April, 2023 20:19
//*LICENSE:         Academic Free License
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include "home.h"
#ifndef LRES
#define LRES 12
#endif

LEDDriver::LEDDriver(pin_t signalPin):_signalPin(signalPin), _brightness(0)
{

}

bool LEDDriver::begin()
{
    pinMode(_signalPin, OUTPUT);
    analogWriteResolution(LRES);
    return true;
}


pin_t LEDDriver::setBrightness(pin_t brightness)
{
    _brightness = brightness;
    return (getBrightness());
}

pin_t LEDDriver::getBrightness() const
{
    return (_brightness);
}


pin_t LEDDriver::on()
{
    analogWriteResolution(LRES);
    analogWrite(_signalPin, _brightness);
    return (getBrightness());
}

pin_t LEDDriver::off()
{
    analogWriteResolution(LRES);
    analogWrite(_signalPin, 0);
    return (getBrightness());
}


