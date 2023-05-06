#include <Arduino.h>
#include <interrupt.h>
#include <home.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <pinmap.h>


#define irInside PA15
#define irOutside PB5
#define motionSensor PA4


#define gateDelay 2000


volatile bool gateInsideDetect = false,
         gateOutsideDetect = false,
         motionSensorDetect = false;

bool gateOpened = false, doorOpened = false;

//volatile uint32_t gateOpened = 0x00, gateClosed = 0x00;

void readGateInside(), gateOpen(), readGateOutside(), gateClose(), readMotion(), openDoor(), closeDoor();

volatile uint32_t currentTime = 0x00;

uint32_t lcdUpdate = 0x00;


DCMotor gate(PB8, PB9, PA11);
PIRSensor motion (PA4);
IRSensor gateInside (PB4);
IRSensor gateOutside (PB5);
SoilMoisture soilMoisture (PA1);
LightSensor lightSensor (PA3);
CurrentSensor currentSensor (PA2);
GasSensor gasSensor (PA0, 7);
DCMotor door (PA8, PA9, PA10);
LiquidCrystal_I2C lcd(0x27, 16, 2);
ShiftReg shr(PA6, PA7, PA5, 0X00);

norahHome home (&gate, &door, &lcd, &lightSensor, &currentSensor, &gasSensor, &motion, &soilMoisture, &gateInside, &gateOutside, &shr);


void setup()
{
    pinMode(irInside, INPUT_PULLUP);
    pinMode(irOutside, INPUT_PULLUP);
    pinMode(motionSensor, INPUT);
    attachInterrupt(irInside, readGateInside, CHANGE);
    attachInterrupt(irOutside, readGateOutside, CHANGE);
    attachInterrupt(motionSensorDetect, readMotion, CHANGE);


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
    home.display("         System"        );
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
    currentTime = millis();
    gasSensor.measure();

    if(gateInsideDetect)
        gateOpen();
    if(gateOutsideDetect)
        gateClose();
    if(motionSensorDetect)
        openDoor();
    if (!motionSensorDetect)
        closeDoor();


    if(currentTime - lcdUpdate >= 500)
    {
        lcdUpdate = currentTime;
        home.clear();
        home.setCursor(0, 0);
        home.display("Waiting...                        ");
    }

}

void readGateInside()
{
    gateInsideDetect = (digitalRead(irInside) == LOW ? true : false ) ;
}

void readGateOutside()
{
    gateOutsideDetect = (digitalRead(irOutside) == LOW ? true : false ) ;
}



void gateOpen()
{
    if(gateInsideDetect && !gateOpened)
    {
        home.clear();
        home.setCursor(0, 0);
        home.display("Opening Gate");
        home.openGate();
        gateOpened = true;
        gateClose();
    }
}

void gateClose()
{
        if(gateOutsideDetect && gateOpened)
        {
            home.clear();
            home.setCursor(0, 0);
            home.display("Closing Gate");
            home.closeGate();
            gateOpened = false;
        }

        else if (!gateOutsideDetect && gateOpened)
        {
            home.clear();
            home.setCursor(0, 0);
            home.display("Waiting to ");
            home.setCursor(0, 1);
            home.display("Close gate...");
        }

        else
        {
            home.clear();
        }

}


void openDoor()
{
    if(!doorOpened)
    {
        home.clear();
        home.setCursor(0, 0);
        home.display("Opening Door");
        home.openDoor();
        doorOpened = true;
    }
}

void closeDoor()
{
    if(doorOpened)
    {
        home.clear();
        home.setCursor(0, 0);
        home.display("Closing Door");
        home.closeDoor();
        doorOpened = false;
    }
}
void readMotion()
{
    motionSensorDetect = (digitalRead(motionSensor) == HIGH) ? true : false;
}
