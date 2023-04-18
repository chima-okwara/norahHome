#include <Arduino.h>
#include "home.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

DCMotor gate (PB1, PB2);
LiquidCrystal_I2C lcd(0x27, 16, 2);
norahHome home (&gate, &lcd);


void setup()
{
    home.begin();
}


void loop()
{
    home.display("Opening Gate");
    home.openGate();
    delay(1000);
    home.display("closing gate");
    home.closeGate();

}
