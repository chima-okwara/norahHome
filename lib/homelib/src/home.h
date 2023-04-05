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

#define ADC_RESOLUTION 12
#define  ADC_MAX_VALUE ((1 << ACD_RESOLUTION) -1)


using pin_t = const uint32_t&;
enum class direction_t { forward = (bool) true, backward = (bool) false };

class GasSensor
{
public:
    //Constructors:
    GasSensor() = default;
    GasSensor(pin_t signalPin, pin_t threshold);
    ~GasSensor();

    //Methods:
    void begin();
    void measure();
    bool gasDetect() const;

private:
    uint32_t _signalPin, _threshold, _value;
    bool isGas;
};

class CurrentSensor
{
public:
    //Constructors:
    CurrentSensor() = default;
    CurrentSensor(pin_t signalPin, const float& sensitivity);
    ~CurrentSensor();

    //Methods:
    void begin();
    void measure();
    float getValue() const;

private:
    uint32_t _signalPin;
    float _sensitivity, _value;


};

class SoilMoisture
{

public:
    //Constructors:
    SoilMoisture() = default;
    SoilMoisture(const uint32_t& sig, const uint32_t& power);
    ~SoilMoisture();

    //Method:
    void begin();
    const float& measure() const;
    const float getSoilMoisture() const;

private:
    uint32_t _signalPin;
    uint32_t _powerPin;
    float* _moistureValue;
};


class LEDDriver
{
public:
    LEDDriver() = default;
    LEDDriver(pin_t signal);
    bool begin();
    uint32_t setBrightness(pin_t brightness);
    uint32_t on();
    uint32_t off();
    uint32_t getBrightness() const;

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
    direction_t move(const direction_t& dir, pin_t speed);
    void stop();
    direction_t getDir() const;

private:
    uint32_t _mot1, _mot2, _en;
    direction_t _dir;

};


class norahHome
{
 public:
  //constructor speake
 norahHome() = default;
 norahHome(const uint8_t &speaker, const uint8_t &startLed);


 void begin();
 // methods
 uint8_t lights();
 uint8_t door();

 //Devices:
 SoilMoisture *soilMoisture;
 LiquidCrystal_I2C *lcd;
 Liquid
 uint8_t _speaker;
 uint8_t _startLed;
};

#endif
