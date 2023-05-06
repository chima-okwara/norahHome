////////////////////////////////////////////////////////////////////////////////////////////////////
//*FILE NAME:       home.h
//*FILE DESC:       Implementation file for DCMotor.
//*FILE VERSION:    0.1.1
//*FILE AUTHOR:     Chimaroke Okwara
//*LAST MODIFIED:   Monday, 3 April, 2023 19:35 (chima_okwara)
//*LICENSE:         Academic Free License
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include "home.h"
#ifndef MRES
#define MRES 12
#endif
DCMotor::DCMotor(pin_t mot1, pin_t mot2, pin_t en):_mot1(mot1), _mot2(mot2), _en(en), _dir(direction_t::forward)
{

}

bool DCMotor::begin()
{
    pinMode(_mot1, OUTPUT);
    pinMode(_mot2, OUTPUT);
    pinMode(_en, OUTPUT);
    analogWriteResolution(MRES);
    return(true);
}

const direction_t& DCMotor::move(const direction_t& dir, pin_t speed)
{
    analogWriteResolution(MRES);
    switch(dir)
    {
        case direction_t::forward:
        {
            // digitalWrite(_en, HIGH);
            digitalWrite(_mot1, HIGH);
            digitalWrite(_mot2, LOW);
            analogWrite(_en, speed);
            _dir = direction_t::forward;
            break;
        }

        case direction_t::backward:
        {
            // digitalWrite(_en, HIGH);
            digitalWrite(_mot1, LOW);
            digitalWrite(_mot2, HIGH);
            analogWrite(_en, speed);
            _dir = direction_t::backward;
            break;
        }
    }

    return (_dir);
}


void DCMotor::stop()
{
    // digitalWrite(_en, 0);
    analogWriteResolution(MRES);
    digitalWrite(_mot1, LOW);
    digitalWrite(_mot2, LOW);
    analogWrite(_en, LOW);
}


const direction_t& DCMotor::getDir() const
{
    return(_dir);
}
