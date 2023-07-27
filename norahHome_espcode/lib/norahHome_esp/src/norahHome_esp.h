#ifndef __HMS_ESP_H__
#define __HMS_ESP_H__
#include <Arduino.h>
#include "esp_defs.h"

//Let D be the terminating character in the strings sent over serial:

extern float humidity, temperature, powerConsumed;
extern bool outsideLightOn, sittingRoomLightOn, bedroomLightOn, gasDetected, gateOpen, doorOpen;
extern char daytime[4], nighttime[4];
//static String sBuffer { }; //Buffer for strings (Ensure that userID is always 6 characters long)
//static float fBuffer { }; //Buffer for floats
static char flag { }; //Single characters to be sent to flag an event in either ESP or STM32
static bool lastActionSuccess { };


bool getHumidity();
bool getTemperature();
bool getPowerConsumed();
bool getOutsideLight();
bool getSittingRoomLight();
bool getBedroomLight();
bool getGasDetected();
bool getGateOpen();
bool getDoorOpen();
bool getDayTime();


bool lastActionSuccessful();



#endif
