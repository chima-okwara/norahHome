////////////////////////////////////////////////////////////////////////////////////////////////////
//*FILE NAME:       home.h
//*FILE DESC:       Implementation file for GasSensor.
//*FILE VERSION:    0.1.1
//*FILE AUTHOR:     Chimaroke Okwara
//*LAST MODIFIED:   Saturday, 16 April, 2023 12:54 (chima_okwara)
//*LICENSE:         Academic Free License
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include "home.h"

IRSensor::IRSensor(pin_t signalPin):_signalPin(signalPin), _detected(false)
{

}

void IRSensor::begin()
{
    pinMode(_signalPin, INPUT);
//    attachInterrupt(digitalPinToInterrupt(_signalPin), [this] { readIR<IRSensor>(this); }, CHANGE);
}

void IRSensor::read()
{
    _detected = ( (digitalRead(_signalPin) == LOW) ? true : false );
}

const bool& IRSensor::detect()
{
    return (_detected ? true : false);
}
