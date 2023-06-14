#include <Arduino.h>
#include <interrupt.h>
#include <home.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <STM32LowPower.h>
#include <DHT.h>


#define irInside PA15
#define irOutside PB5
#define motionSensor PA4
#define balconyLightPin PA5
#define frontDoorLightPin PA6
#define outsideLightPin PA7
#define sittingRoomLightPin PB0
#define bedroom1LightPin PB1
#define bedroom2LightPin PA11
#define lightSensorPin PA2
#define buzzerPin PC15
#define currentSensorPin PA3
#define currentThreshold 500.00
#define sleepBtn PB13
#define power PB12


#define tx PB7
#define rx PB6

#define DHTPIN  PB14
#define DHTTYPE DHT11




#define gateDelay 2000

//Flags:
volatile bool gateInsideDetect = false,
         gateOutsideDetect = false,
         motionSensorDetect = false,
         lights[6] { },
         powerOn = false;


bool gateOpened = false, doorOpened = false, isGas = false;

//volatile uint32_t gateOpened = 0x00, gateClosed = 0x00;

void readGateInside(), gateOpen(), readGateOutside(), gateClose(), readMotion(), openDoor(), closeDoor(), flagLight(),
     wakeUpAction();

volatile uint32_t currentTime = 0x00;

uint32_t lcdUpdate = 0x00;



DCMotor gate(PB8, PB9, PA11);
PIRSensor motion (motionSensor);
IRSensor gateInside (irInside);
IRSensor gateOutside (irOutside);
SoilMoisture soilMoisture (PA1);
LightSensor lightSensor (PA2);
CurrentSensor currentSensor (currentSensorPin);
GasSensor gasSensor (PA0);
DCMotor door (PA12, PA9, PA8);
LiquidCrystal_I2C lcd(0x27, 16, 2);
LEDDriver l1(balconyLightPin);
LEDDriver l2(frontDoorLightPin);
LEDDriver l3(outsideLightPin);
LEDDriver l4(sittingRoomLightPin);
LEDDriver l5(bedroom1LightPin);
LEDDriver l6(bedroom2LightPin);
LEDDriver buzzer(buzzerPin);

DHT tempSensor(DHTPIN, DHTTYPE);

norahHome home (&gate, &door, &lcd, &lightSensor, &currentSensor, &gasSensor, &motion, &soilMoisture, &gateInside, &gateOutside, &l1, &l2, &l3, &l4, &l5, &l6, tx, rx);





void setup()
{
    pinMode(power, OUTPUT);
    pinMode(irInside, INPUT_PULLUP);
    pinMode(irOutside, INPUT_PULLUP);
    pinMode(motionSensor, INPUT);
    pinMode(sleepBtn, INPUT_PULLDOWN);
    attachInterrupt(irInside, readGateInside, CHANGE);
    attachInterrupt(irOutside, readGateOutside, CHANGE);
    attachInterrupt(motionSensorDetect, readMotion, CHANGE);
//    attachInterrupt(lightSensorPin, checkLight, CHANGE);


    LowPower.begin();
    LowPower.attachInterruptWakeup(sleepBtn, wakeUpAction, RISING, IDLE_MODE);

    buzzer.begin();
    home.begin();
    tempSensor.begin();

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
    wakeUpAction();
}


void loop()
{
    while(currentSensor.getValue() >= currentThreshold)
    {
        home.clear();
        home.setCursor(0, 0);
        home.display("Current exceeds threshold.");
        home.setCursor(0, 1);
        home.display("Disconnect");
        delay(5000);
        currentSensor.measure();
        if(currentSensor.getValue() >= currentThreshold)
        {
            LowPower.idle();
        }

    }
    
    for (int i = 0; i < 6; ++i)
    {
        if(lights[i])
        {
            home.light(i, 3000);       
        }    
        
        else
        {
            home.light(i, 0);        
        }
    }
    currentSensor.measure();

    if(tempSensor.readTemperature() >= 30.0);
    {

    }
    currentTime = millis();
    lightSensor.measure(5);
    gasSensor.measure();

    if(gasSensor.gasDetect())
    {
        buzzer.setBrightness(4096);
        buzzer.on();
        home.clear();
        home.setCursor(0, 0);
        home.display("Gas detected!!!");
        isGas = true;
    }

    else
    {
        buzzer.setBrightness(0);
        buzzer.off();
        isGas = false;
    }


    if (lightSensor.isDark())
    {
        home.light(balconyLight, 3000);
        home.light(outsideLight, 3000);
        home.clear();
        home.setCursor(0, 0);
        home.display("Nightfall...");
        delay(500);
        home.setCursor(0, 1);
        home.display("Lights on.");
        delay(1000);
    }

    else if(lightSensor.isLight())
    {
        home.light(balconyLight, OFF);
        home.light(outsideLight, OFF);
        home.clear();
        home.setCursor(0, 0);
        home.display("Daybreak...");
        delay(500);
        home.setCursor(0, 1);
        home.display("Lights off.");
        delay(1000);
    }


    gasSensor.measure();

    if(gateInsideDetect)
        gateOpen();
    if(gateOutsideDetect)
        gateClose();
//    if(motionSensorDetect)
//        openDoor();
//    if (!motionSensorDetect)
//        closeDoor();


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
    currentSensor.measure();

}

void readGateOutside()
{
    gateOutsideDetect = (digitalRead(irOutside) == LOW ? true : false ) ;
    currentSensor.measure();
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


void wakeUpAction()
{
    if(!powerOn)
    {
        powerOn = true;
        digitalWrite(power, HIGH);      //TODO: Check and verify operation of transistor.
        LowPower.shutdown();
    }

    else
    {
        powerOn=false;
        digitalWrite(power, LOW);
    }
}
