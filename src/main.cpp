#include <Arduino.h>
#include <interrupt.h>
#include <home.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <STM32LowPower.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <HardwareSerial.h>
#include <esp_defs.h>

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

//TODO: Pair bedroom1Light and bedroom2Light to be controlled by one pin and add fan
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


volatile bool gateOpened = false, doorOpened = false, isGas = false;

float temperature { }, humidity { };

//volatile uint32_t gateOpened = 0x00, gateClosed = 0x00;

//Interrupt service routines:
void readGateInside(), gateOpen(), readGateOutside(), gateClose(), readMotion(), openDoor(), closeDoor(), flagLight();
//     wakeUpAction();

volatile uint32_t currentTime = 0x00, lastTime = 0x00;

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

HardwareSerial Serial1 (USART1);

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

    //Additional features, not added in v1.0.
//    attachInterrupt(motionSensorDetect, readMotion, CHANGE);
//    attachInterrupt(lightSensorPin, checkLight, CHANGE);



//    LowPower.begin();
//    LowPower.attachInterruptWakeup(sleepBtn, wakeUpAction, RISING, IDLE_MODE);

    buzzer.begin();
    home.begin();
    tempSensor.begin();

    //Communication with WiFi module
    Serial1.begin(115200);

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
//    wakeUpAction();
}


void loop()
{
//    Not implemented in version 1.0
//    while(currentSensor.getValue() >= currentThreshold)
//    {
//        home.clear();
//        home.setCursor(0, 0);
//        home.display("Current exceeds threshold.");
//        home.setCursor(0, 1);
//        home.display("Disconnect");
//        delay(5000);
//        currentSensor.measure();
//        if(currentSensor.getValue() >= currentThreshold)
//        {
//            LowPower.idle();
//        }
//
//    }

    currentTime = millis();
    currentSensor.measure();
    temperature = tempSensor.readTemperature();
    humidity = tempSensor.readHumidity();
    lightSensor.measure(5);
    gasSensor.measure();

    Serial1.print(TEMPERATURE);
    Serial1.println(temperature);
    delay(espDelay);
    Serial1.print(HUMIDITY);
    Serial1.println(humidity);
    delay(espDelay);
    Serial1.print(POWER_CONSUMED);
    Serial1.println(currentSensor.getValue() * 11.9);


    for (int i = 0; i < 6; ++i)
    {
        if(lights[i])
        {
            home.light(i, 3000);
        }

        else
        {
            home.light(i, 0);sensor
        }
    }

    currentSensor.measure();
    Serial1.print(POWER_CONSUMED);
    Serial1.println(currentSensor.getValue() * 11.9);

    if(gasSensor.gasDetect())
    {
        buzzer.setBrightness(4096);
        buzzer.on();
        home.clear();
        home.setCursor(0, 0);
        home.display("Gas detected!!!");
        isGas = true;
        Serial1.print(GAS_DETECTED);
        Serial1.println("Yes");
        delay(espDelay);
    }


    else
    {
        buzzer.setBrightness(0);
        buzzer.off();
        Serial.print(GAS_DETECTED);
        Serial1.println("No");
        delay(espDelay);
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
        Serial1.print(OUTSIDE_LIGHT);
        Serial1.println("ON");
        delay(espDelay);
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
        Serial1.print(OUTSIDE_LIGHT);
        Serial1.println("OFF");
        delay(espDelay);
        delay(1000);
    }

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
        home.display("Waiting...");
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
    if(!gateOpened)
    {
        home.clear();
        home.setCursor(0, 0);
        home.display("Opening Gate");
        home.openGate();
        gateOpened = true;
        Serial.println(GATE_OPEN);
        Serial.println("OPEN");
        gateClose();
    }

    else
    {
        home.clear();
        home.setCursor(0, 0);
        home.display("Closing Gate");
        home.closeGate();
        gateOpened = false;
        Serial.println(GATE_OPEN);
        Serial.println("CLOSED");
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
        Serial.println(GATE_OPEN);
        Serial.println("CLOSED");
    }

    else if (!gateOutsideDetect && gateOpened)
    {
        home.clear();
        home.setCursor(0, 0);
        home.display("Waiting to ");
        home.setCursor(0, 1);
        home.display("Close gate...");
        delay(1000);
    }

    else
    {
        gateOpen();
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

///Not implemented in version 1.0:

//void readMotion()
//{
//    motionSensorDetect = (digitalRead(motionSensor) == HIGH) ? true : false;
//}


//void wakeUpAction()
//{
//    if(!powerOn)
//    {
//        powerOn = true;
//        digitalWrite(power, HIGH);      //TODO: Check and verify operation of transistor.
//        LowPower.shutdown();
//    }
//
//    else
//    {
//        powerOn=false;
//        digitalWrite(power, LOW);
//    }
//}
