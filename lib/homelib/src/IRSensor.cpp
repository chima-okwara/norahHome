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
template <typename T>
    void readIR(T *sensor)
{
    sensor->_detected = ( (digitalRead(sensor->_signalPin) == LOW) ? true : false );
}

IRSensor::IRSensor(pin_t signalPin):_signalPin(signalPin), _detected(false)
{

}

void IRSensor::begin()
{
    pinMode(_signalPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(_signalPin), [this] { readIR(this); }, FALLING);
}

const bool& IRSensor::detect()
{
    return (_detected ? true : false);
}
