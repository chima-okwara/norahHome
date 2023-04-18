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

template <typename T>
    void readPIR(T *sensor);

template <typename T>
    void readIR(T *sensor);

class GasSensor
{
public:
    //Constructors:
    GasSensor() = default;
    GasSensor(pin_t signalPin, pin_t threshold);
    // ~GasSensor();

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

protected:
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
    DCMotor(pin_t mot1, pin_t mot2);
    bool begin();
    const direction_t& move(const direction_t& dir, pin_t speed);
    void stop();
    const direction_t& getDir() const;

private:
    uint32_t _mot1, _mot2;
    direction_t _dir;

};

class IRSensor
{
public:
    IRSensor() = default;
    IRSensor(pin_t signalPin);

    void begin();
    const bool& detect();
    template <typename T>
        void readIR(T *sensor);

private:
    volatile uint32_t _signalPin;
    volatile bool _detected;
};

class PIRSensor
{
public:
    PIRSensor() = default;
    PIRSensor(pin_t signalPin);

    void begin();
    const bool& isMotion();
    template <typename T>
        void readPIR(T *sensor);

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
 norahHome(DCMotor *Gate, LiquidCrystal_I2C *Screen, DCMotor *Window, LightSensor* LDR, CurrentSensor* is, GasSensor* gas, PIRSensor *motion, IRSensor* Gate, DCMotor* fan, LEDDriver *sit, LEDDriver* bed);


 // methods
void begin();
void openGate();
void closeGate();
template <typename T>
    void display(const T& val)
    {
        lcd->print(val);
    }


 private:
 //Devices:
 SoilMoisture *soilMoisture;

 LiquidCrystal_I2C *lcd;

 IRSensor *gateSensor;
 PIRSensor *motion;

 DCMotor *fan;
 DCMotor *gate;
 DCMotor *windows;
 DCMotor *door;

 GasSensor *gasSensor;

 LEDDriver *sittingRoomLights;
 LEDDriver *bedRoomLights;

 LightSensor *lightSensor;
 CurrentSensor *currentSensor();
};

#endif
