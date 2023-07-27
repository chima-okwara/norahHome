//TODO:
//Push to database:
/*
compound
balcony
front_door
sitting_room
bedroom
temperature
humidity
daytime
nighttime
power_consumed
gasDetected
*/
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <Wire.h>
#include <norahHome_esp.h>
#include <esp_defs.h>

float humidity { }, temperature { }, powerConsumed { };
bool outsideLightOn{ }, sittingRoomLightOn{ }, bedroomLightOn{ }, gasDetected{ }, gateOpen{ }, doorOpen{ };
char daytime[4] { }, nighttime[4] { };

// Replace with your network credentials
const char* ssid     = "Tell My Wi-Fi Love Her";
const char* password = "0p3ns3s4m3!";
const char* ipAddress = "xxx.xxx.xxx.xxx";


// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "https://xxx.yyy.zzz.abc/123.php";

//API Key for syncing with database
String apiKeyValue = "NorahHome_20202_ul";


void setup()
{
  Serial.begin(115200);
  lastActionSuccess = true;



  WiFi.begin(ssid, password);

    //Send C for connecting....
  Serial.println('C');

  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.println(ERROR);
    delay(500);
  }

  flag = ESP_READY;
  Serial.println(flag);
//  strcpy(WiFi.localIP(), ipAddress);
  }


void loop()
{
  if(WiFi.status()== WL_CONNECTED && Serial.available() > 0)
  {
    flag = Serial.read();
    switch (flag)
    {
        case UPLOAD:
//      case REUPLOAD:
        {
            std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

            // Ignore SSL certificate validation
            client->setInsecure();

            HTTPClient https;

            // Your Domain name with URL path or IP address with path
            https.begin(*client, serverName);


            // Specify content-type header
            https.addHeader("Content-Type", "application/x-www-form-urlencoded");


            // Prepare your HTTP POST request data
//            String httpRequestData = "api_key=" + apiKeyValue + " " + "&user_id=" + 'D' + "";
            String httpRequestData = "api_key=" + apiKeyValue + "&temperature=" + String(temperature)
                          +  "&humidity=" + String(humidity) + "&power_consumed=" + String(powerConsumed)
                          +  "&gasDetected=" + String(gasDetected) + "&gateOpen=" + String(gateOpen) + "&doorOpen="
                          + String(doorOpen) + "&bedroomLight" + String(bedroomLightOn)
                          + "&outsideLight" + String(outsideLightOn) + "&sittingRoomLight" + String(sittingRoomLightOn) + "";
            Serial.print("httpRequestData: ");


            Serial.println(httpRequestData);

            // Send HTTP POST request
            int httpResponseCode = https.POST(httpRequestData);

            if (httpResponseCode>0)
            {
                Serial.print("HTTP Response code: ");
                Serial.println(httpResponseCode);
            }

            else
            {
                Serial.print("Error code: ");
                Serial.println(httpResponseCode);
            }
            // Free resources
            https.end();
            break;
        }

        case ESP_READY:
        {
//            std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
//
//             Ignore SSL certificate validation
//            String url = "http://" + String(serverName) + "/servers.php?character";
//            client->setInsecure();
//
//            HTTPClient https;
//
//
//            https.begin(*client, url);
//            https.addHeader("Content-Type", "application/x-www-form-urlencoded");
//
//            int httpResponseCode = https.GET();
//            if(httpResponseCode > 0)
//            {
//                String buffer = https.getString();
//                flag = buffer.charAt(0);
//            }

//            else
//            {
//                flag = Serial.read();
//            }

            break;
        }

        case TEMPERATURE:
        {
            getTemperature();
            break;
        }

        case HUMIDITY:
        {
            getHumidity();
            break;
        }

        case BEDROOM_LIGHT:
        {
            getBedroomLight();
            break;
        }

        case SITTING_ROOM_LIGHT:
        {
            getSittingRoomLight();
            break;
        }

        case OUTSIDE_LIGHT:
        {
            getOutsideLight();
            break;
        }

        case POWER_CONSUMED:
        {
            getPowerConsumed();
            break;
        }

        case GAS_DETECTED:
        {
            getGasDetected();
            break;
        }

        case GATE_OPEN:
        {
            getGateOpen();
            break;
        }

        case DOOR_OPEN:
        {
            getDoorOpen();
            break;
        }

        case DAYTIME:
        {
            getDayTime();
            break;
        }

        default:
        {
           Serial.println(ESP_READY);
            break;
        }
    }
  }

  else
  {
    WiFi.begin(ssid, password);
  }

  delay(2000);
}

