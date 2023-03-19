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


