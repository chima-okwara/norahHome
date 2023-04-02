////////////////////////////////////////////////////////////////////////////////////////////////////
//*FILE NAME:       home.cpp
//*FILE DESC:       Implementation file for norahHome.
//*FILE VERSION:    0.1.1
//*FILE AUTHOR:     Favour Aina
//*LAST MODIFIED:   Saturday, 1 April, 2023 20:19
//*LICENSE:         Academic Free License
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include "home.h"


norahHome::norahHome(const uint8_t &speaker, const uint8_t &startLed)
: _speaker {speaker}, _startLed {startLed}
{
    pinMode(_startLed, OUTPUT);
    pinMode(_speaker, OUTPUT);

    for(size_t i {}; i < 5; i++)
    {
        digitalWrite(_speaker, HIGH);
        digitalWrite(_startLed, LOW);
        delay(800);
        digitalWrite(_speaker, LOW);
        digitalWrite(_startLed, LOW);
        delay(800);
    }


}

void norahHome::begin()
{
    adc_init();
}



