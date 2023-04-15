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


norahHome::norahHome(DCMotor* Gate, LiquidCrystal_I2C* Screen):lcd(Screen), gate(Gate)
{

}


void norahHome::begin()
{
    lcd->init();
    gate->begin();

}

void norahHome::openGate()
{
    gate->move(direction_t::backward, 2048);
    delay(4000);
    gate->stop();
}

void norahHome::closeGate()
{
    gate->move(direction_t::forward, 2048);
    delay(4000);
    gate->stop();
}


