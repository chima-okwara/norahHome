////////////////////////////////////////////////////////////////////////////////////////////////////
//*FILE NAME:       home.cpp
//*FILE DESC:       Implementation file for norahHome.
//*FILE VERSION:    0.1.1
//*FILE AUTHOR:     Favour Aina
//*LAST MODIFIED:   Saturday, 1 April, 2023 20:19
//*LICENSE:         Academic Free License
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "home.h"
#define gatespeed 1200
#define doorspeed 1200
#define espBaud 115200


norahHome::norahHome(DCMotor *Gate, DCMotor *Door, LiquidCrystal_I2C *Screen, LightSensor* LDR, CurrentSensor* is, GasSensor* gas, PIRSensor *motion, SoilMoisture *soilMoisture, IRSensor* GateInside, IRSensor* GateOutside, LEDDriver* l1, LEDDriver* l2, LEDDriver* l3, LEDDriver* l4, LEDDriver *l5, LEDDriver* l6, pin_t espTx, pin_t espRx)
:soilMoisture(soilMoisture), lcd(Screen), gateInside(GateInside), gateOutside(GateOutside), motion(motion), gate(Gate), door(Door), gasSensor(gas), lightSensor(LDR), currentSensor(is), balc(l1), frDoor(l2), outLight(l3), sitLight(l4), bed1Light(l5), bed2Light(l6), _espTx(espTx), _espRx(espRx)

{

}


void norahHome::begin()
{
    esp = new SoftwareSerial(_espRx, _espTx);
    esp->begin(espBaud);


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
    balc->begin();
    frDoor->begin();
    outLight->begin();
    sitLight->begin();
    bed1Light->begin();
    bed2Light->begin();

    esp->println("AT+RST");
    lcd->setCursor(0, 0);
    lcd->print("Setting up ");
    lcd->setCursor(0, 1);
    lcd->print("Network...");

    esp->println("AT+CWMODE=2");
    delay(1000);
    esp->println("AT+CSWAP=norahHome0.1,norahhome");
    delay(1000);
    esp->println("AT+CIPMUX=1");
    delay(1000);
    esp->println("AT+CIPSERVER=1,80");
    delay(1000);
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Done setting up");
    lcd->setCursor(0, 1);
    lcd->print("Network!");
    delay(1500);

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

void norahHome::light(const uint8_t& lite, pin_t value)
{
    switch(lite)
    {
        case balconyLight:
        {
            balc->setBrightness(value);
            if(value >= 1)
                balc->on();
            else
                balc->off();
            break;
        }

        case frontDoorLight:
        {
            frDoor->setBrightness(value);
            if(value >= 1)
                frDoor->on();
            else
                frDoor->off();
            break;
        }

        case outsideLight:
        {
            outLight->setBrightness(value);
            if(value >= 1)
                outLight->on();
            else
                outLight->off();
            break;
        }

        case sittingRoomLight:
        {
            sitLight->setBrightness(value);
            if(value >= 1)
                sitLight->on();
            else
                sitLight->off();
            break;
        }

        case bedroom1Light:
        {
            bed1Light->setBrightness(value);
            if(value >= 1)
                bed1Light->on();
            else
                bed1Light->off();
            break;
        }

        case bedroom2Light:
        {
            bed2Light->setBrightness(value);
            if(value >= 1)
                bed2Light->on();
            else
                bed2Light->off();
            break;
        }

        default:
        {
            break;
        }

    }
}



