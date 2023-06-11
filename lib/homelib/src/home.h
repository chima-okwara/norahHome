////////////////////////////////////////////////////////////////////////////////////////////////////
//*FILE NAME:       home.h
//*FILE DESC:       Header file for norahHome.
//*FILE VERSION:    0.1.1
//*FILE AUTHOR:     Favour Aina
//*LAST MODIFIED:   Monday, 3 April, 2023 19:35 (chima_okwara)
//*LICENSE:         Academic Free License
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___NORAHHOME___
#define ___NORAHHOME___
#define _MAX_PWM_ 65535
#include <inttypes.h>
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <DHT.h>

#define balconyLight 0
#define frontDoorLight 1
#define outsideLight 2
#define sittingRoomLight 3
#define bedroom1Light 4
#define bedroom2Light 5

#define ON HIGH
#define OFF LOW
//#include <Arduino_ADC.h>

#ifdef ADC_RESOLUTION
    #undef ADC_RESOLUTION
    #define ADC_RESOLUTION 12
    #define  ADC_MAX_VALUE ((1 << ADC_RESOLUTION) -1)
#endif

extern volatile uint32_t currentTime;

using pin_t = const uint32_t&;
enum class direction_t { forward = (bool) true, backward = (bool) false };
//enum class light_t { balcony = 0, frontDoor = 1, outside = 2, sittingRoom = 3, bedroom1 = 4, bedroom2 = 5 };


class GasSensor
{
public:
    //Constructors:
    GasSensor() = default;
    GasSensor(pin_t signalPin);
    // ~GasSensor();

    //Methods:
    void begin();
    void measure();
    bool gasDetect() const;

private:
    uint32_t _signalPin;
    float _threshold, _value, _concentration;
    bool _isGas;
};

class ShiftReg
{

public:
    ShiftReg() = default;
    ShiftReg(pin_t Data, pin_t Latch, pin_t Clock, const uint8_t &initValue);

    void begin();
    void shiftValue(const uint8_t& value);
    void shiftValue();
    void toggleBalc(const uint8_t& value)
    {
        if(value)
            _value |= (1 << balconyLight);
        else
            _value &= ~(1 << balconyLight);
    }
    void toggleFront(const uint8_t& value)
    {
        if(value)
            _value |= (1 << frontDoorLight);
        else
            _value &= ~(1 << frontDoorLight);
    }
    void toggleOut(const uint8_t& value)
    {
        if(value)
            _value |= (1 << outsideLight);
        else
            _value &= ~(1 << outsideLight);
    }
    void toggleSit(const uint8_t& value)
    {
        if(value)
            _value |= (1 << sittingRoomLight);
        else
            _value &= ~(1 << sittingRoomLight);
    }
    void toggleBed1(const uint8_t& value)
    {
        if(value)
            _value |= (1 << bedroom1Light);
        else
            _value &= ~(1 << bedroom1Light);
    }
    void toggleBed2(const uint8_t& value)
    {
        if(value)
            _value |= (1 << bedroom2Light);
        else
            _value &= ~(1 << bedroom2Light);
    }

    const uint32_t& readValue() { return (_value); }


private:
    uint32_t _data, _latch, _clock, _value;

};

class CurrentSensor
{
public:
    //Constructors:
    CurrentSensor() = default;
    CurrentSensor(pin_t signalPin, const float& sensitivity = 0.185);

    //Methods:
    void begin();
    void measure();
    float getValue() const;

protected:
    uint32_t _signalPin;
    float _sensitivity, _value;


};

class SoilMoisture
{

public:
    //Constructors:
    SoilMoisture() = default;
    SoilMoisture(const uint32_t& sig);

    //Method:
    void begin();
    const float& measure();
    const float& getSoilMoisture();

private:
    uint32_t _signalPin;
    float _moistureValue;
};


class LEDDriver
{
public:
    LEDDriver() = default;
    LEDDriver(pin_t signal);
    bool begin();
    const uint32_t& setBrightness(pin_t brightness);
    const uint32_t& on();
    const uint32_t& off();
    const uint32_t& getBrightness() const;

private:
    uint32_t _signalPin;
    uint32_t _brightness;

};


class DCMotor
{
public:
//To use L293D IC
    DCMotor() = default;
    DCMotor(pin_t mot1, pin_t mot2, pin_t en);
    bool begin();
    const direction_t& move(const direction_t& dir, pin_t speed);
    void stop();
    const direction_t& getDir() const;

private:
    uint32_t _mot1, _mot2, _en;
    direction_t _dir;

};

class IRSensor
{
public:
    IRSensor() = default;
    IRSensor(pin_t signalPin);

    void begin();
    const bool& detect();
    void read();

private:
    volatile uint32_t _signalPin;
    volatile int _detected;
};

class PIRSensor
{
public:
    PIRSensor() = default;
    PIRSensor(pin_t signalPin);

    void begin();
    const bool& isMotion();

private:
    volatile uint32_t _signalPin;
    volatile bool _detected;
};

class LightSensor
{
public:
    LightSensor() = default;
    LightSensor(pin_t signalPin);

    void begin();
    const bool& measure(uint32_t level = 5 );
    const bool& isLight();
    const bool& isDark();

private:
    uint32_t _signalPin;
    bool _state;
};

class norahHome
{
 public:
  //constructor speake
 norahHome() = default;
 norahHome(DCMotor *Gate, DCMotor *Door, LiquidCrystal_I2C *Screen, LightSensor* LDR, CurrentSensor* is, GasSensor* gas, PIRSensor *motion, SoilMoisture *soilMoisture, IRSensor* GateInside, IRSensor* GateOutside, LEDDriver* l1, LEDDriver* l2, LEDDriver* l3, LEDDriver* l4, LEDDriver *l5, LEDDriver* l6, pin_t espTx, pin_t espRx);


 // methods
    void begin();
    void openGate();
    void closeGate();
    void openDoor();
    void closeDoor();

    void light(const uint8_t& lite, pin_t value);



template <typename T>
    void display(const T& val)
    {
        lcd->print(val);
    }
    void clear() { lcd->clear(); }
    void setCursor(int c, int r) { lcd->setCursor(c ,r); }


    //Door and Gate:


 private:
 //Devices:
 SoilMoisture *soilMoisture;

 LiquidCrystal_I2C *lcd;

 IRSensor *gateInside;
 IRSensor *gateOutside;
 PIRSensor *motion;

 DCMotor *gate;
 DCMotor *door;

 GasSensor *gasSensor;

 LightSensor *lightSensor;
 CurrentSensor *currentSensor;
 LEDDriver* balc;
 LEDDriver* frDoor;
 LEDDriver* outLight;
 LEDDriver* sitLight;
 LEDDriver* bed1Light;
 LEDDriver* bed2Light;
 uint32_t _espTx, _espRx;
 SoftwareSerial *esp;
};


#endif
