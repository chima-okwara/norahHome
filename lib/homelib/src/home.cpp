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


norahHome(DCMotor *Gate, LiquidCrystal_I2C *Screen, DCMotor *Window, LightSensor* LDR, CurrentSensor* is, GasSensor* gas, PIRSensor *motions, IRSensor* Gates, DCMotor* Fan, LEDDriver *sit, LEDDriver* bed)

:lcd(Screen), gateSensor(Gates), motion(motions), fan(Fan), gate(Gate), windows(Window), gasSensor(gas), sittingRoomLights(sit), bedRoomLights(bed), lightSensor(LDR), currentSensor(is)
{

}


void norahHome::begin()
{
    lcd->begin();
    gate->begin();
    motion->begin();
    gateSensor->begin();
    fan->begin();
    windows->begin();
    gasSensor->begin();
    sittingRoomLights->begin();
    bedRoomLights()->begin();
    lightSensor->begin();
    currentSensor()->begin();

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


