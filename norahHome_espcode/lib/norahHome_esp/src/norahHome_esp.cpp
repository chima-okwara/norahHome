#include <Arduino.h>
#include "norahHome_esp.h"



bool lastActionSuccessful()
{
    return (lastActionSuccess ? true : false);
}


bool getHumidity()
{
    delay(espDelay);

    String buffer = Serial.readString();
    humidity = buffer.toFloat();
    Serial.println(HUMIDITY);
    Serial.println(humidity);
    return (true);
}

bool getBedroomLight()
{
    delay(espDelay);

    String buffer = Serial.readString();

    if(buffer.equals("ON"))
        bedroomLightOn = true;
    else
        bedroomLightOn = false;
    Serial.println(BEDROOM_LIGHT);
    Serial.println(bedroomLightOn);
    return true;
}

bool getTemperature()
{
    delay(espDelay);

    String buffer = Serial.readString();
    temperature = buffer.toFloat();
    Serial.println(TEMPERATURE);
    Serial.println(temperature);
    return true;
}

bool getDoorOpen()
{
    delay(espDelay);

    String buffer = Serial.readString();
    if(buffer.equals("OPEN"))
        doorOpen = true;
    else
        doorOpen = false;

    Serial.println(DOOR_OPEN);
    Serial.println(doorOpen);
    return true;
}

bool getGateOpen()
{
    delay(espDelay);

    String buffer = Serial.readString();
    if(buffer.equals("OPEN"))
        gateOpen = true;
    else
        gateOpen = false;

    Serial.println(GATE_OPEN);
    Serial.println(gateOpen);
    return true;
}

bool getGasDetected()
{
    delay(espDelay);

    String buffer = Serial.readString();
    if(buffer.equals("YES"))
        gasDetected = true;
    else
        gasDetected = false;

    Serial.println(GAS_DETECTED);
    Serial.println(gasDetected);
    return true;
}

bool getPowerConsumed()
{
    delay(espDelay);

    String buffer = Serial.readString();
    powerConsumed = buffer.toFloat();
    Serial.println(POWER_CONSUMED);
    Serial.println(powerConsumed);
    return true;
}

bool getSittingRoomLight()
{
    delay(espDelay);

    String buffer = Serial.readString();
    if(buffer.equals("ON"))
        sittingRoomLightOn = true;
    else
        sittingRoomLightOn = false;

    Serial.println(SITTING_ROOM_LIGHT);
    Serial.println(sittingRoomLightOn);
    return true;
}

bool getOutsideLight()
{
    delay(espDelay);

    String buffer = Serial.readString();

    if(buffer.equals("ON"))
        outsideLightOn = true;
    else
        outsideLightOn = false;
    Serial.println(OUTSIDE_LIGHT);
    Serial.println(outsideLightOn);
    return true;
}

bool getDayTime()
{
    delay(espDelay);

    String buffer = Serial.readString();

    if(buffer.equals("YES"))
    {
        strcpy(daytime, "YES");
        strcpy(nighttime, "NO");
    }

    else
    {
        strcpy(daytime, "NO");
        strcpy(nighttime, "YES");
    }

    Serial.println(DAYTIME);
    Serial.println(String(daytime));
    Serial.println(String(nighttime));
    return true;
}
