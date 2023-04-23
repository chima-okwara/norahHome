#include <Arduino.h>
#include "home.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>



DCMotor gate (PB8, PB9);
PIRSensor motion (PA4);
IRSensor gateInside (PB4);
IRSensor gateOutside (PB3);
SoilMoisture soilMoisture (PA1);
LightSensor lightSensor (PA3);
CurrentSensor currentSensor (PA2);
GasSensor gasSensor (PA0, 7);
DCMotor door (PA8, PA9);
LiquidCrystal_I2C lcd(0x27, 16, 2);
ShiftReg shr(PA6, PA7, PA5, 0X00);

norahHome home (&gate, &door, &lcd, &lightSensor, &currentSensor, &gasSensor, &motion, &soilMoisture, &gateInside, &gateOutside, &shr);


void setup()
{
    home.begin();
    home.clear();
    home.setCursor(0, 0);
    home.display("    norahHome   ");
    delay(1000);
    home.clear();
    home.setCursor(0, 0);
    home.display("IoT - Based");
    delay(1000);
    home.setCursor(0, 1);
    home.display("  Smart Home  ");
    delay(1000);
    home.clear();
    home.setCursor(0, 0);
    home.display("Management");
    home.setCursor(0, 1);
    home.display("         System");
    delay(1000);
    home.clear();
    home.setCursor(0, 0);
    home.display(" NorahLinks  ");
    home.setCursor(0, 1);
    home.display("Technologies (R)");
    delay(1000);
    home.clear();
    home.setCursor(0, 0);
    home.display("    (c) 2023   ");
    delay(1000);
    home.clear();
}


void loop()
{
    delay(1000);
    home.setCursor(0, 0);
    home.display("Waiting...                                        ");
    if(gateOutside.detect())
    {
        home.clear();
        home.setCursor(0,0);
        home.display("Opening Gate");
        home.openGate();
        delay(1000);
    }

    if(gateInside.detect())
    {
        home.clear();
        home.setCursor(0,0);
        home.display("closing gate");
       home.closeGate();
       delay(1000);
    }
}
