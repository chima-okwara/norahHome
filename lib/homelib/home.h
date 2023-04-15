#ifndef __norahHome__
#define __norahHome__
#include <inttypes.h>
#include <Arduino.h>

#define light1 1

class norahHome
{
 public: 
  //constructor speake
 norahHome() = default; 
 norahHome(const uint8_t &speaker, const uint8_t &startLed);
 

 // methods
 uint8_t lights();
 uint8_t door();

 uint8_t _speaker;
 uint8_t _startLed;

 /* 
 SENSORS TO BE USED FOR THIS HME AUTOMATION INCLUDES:
 Ultrasonic sensor
 motion sensor
 I.R sensor
 temperature and humitdity Sensor
 gas sensor 
  
 
 
 
 
 */
};








#endif