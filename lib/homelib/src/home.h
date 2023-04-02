////////////////////////////////////////////////////////////////////////////////////////////////////
//*FILE NAME:       home.h
//*FILE DESC:       Header file for norahHome.
//*FILE VERSION:    0.1.1
//*FILE AUTHOR:     Favour Aina
//*LAST MODIFIED:   Saturday, 1 April, 2023 20:19
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
    const float& getSoilMoisture() const;

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
    pin_t setBrightness(pin_t brightness);
    pin_t on();
    pin_t off();
    pin_t getBrightness() const;

private:
    pin_t _signalPin;
    pin_t _brightness;

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
    pin_t _mot1, _mot2, _en;
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
