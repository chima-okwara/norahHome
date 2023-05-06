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
#define gatespeed 1200
#define doorspeed 1200


norahHome::norahHome(DCMotor *Gate, DCMotor *Door, LiquidCrystal_I2C *Screen, LightSensor* LDR, CurrentSensor* is, GasSensor* gas, PIRSensor *motion, SoilMoisture *soilMoisture, IRSensor* GateInside, IRSensor* GateOutside, ShiftReg* shr)
:soilMoisture(soilMoisture), lcd(Screen), gateInside(GateInside), gateOutside(GateOutside), motion(motion), gate(Gate), door(Door), gasSensor(gas), lightSensor(LDR), currentSensor(is), shiftReg(shr)

{

}


void norahHome::begin()
{
    lcd->begin();
    gate->begin();
    motion->begin();
    gateInside->begin();
    gateOutside->begin();
    gasSensor->begin();
    lightSensor->begin();
    soilMoisture->begin();
    door->begin();
    currentSensor->begin();
}

void norahHome::openGate()
{
    gate->move(direction_t::backward, gatespeed);
    delay(2000);
    gate->stop();
}

void norahHome::closeGate()
{
    gate->move(direction_t::forward, gatespeed);
    delay(2000);
    gate->stop();
}

void norahHome::openDoor()
{
    door->move(direction_t::backward, doorspeed);
    delay(2000);
    door->stop();
}

void norahHome::closeDoor()
{
    door->move(direction_t::forward, doorspeed);
    delay(2000);
    door->stop();
}


