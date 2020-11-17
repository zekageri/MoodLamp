#ifndef Includes_h
#define Includes_h
#include <Arduino.h>

/** VENDOR HEADERS */
#include <WiFi.h>
#include <FS.h>
#include <LITTLEFS.h> 
#include <DNSServer.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
//#include <Adafruit_NeoPixel.h>
#include <FastLED.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include "RTClib.h"

/** VENDOR HEADERS */

/***********************************/

/** OWN HEADERS **/
#include <Headers/Defines.h>

#include <Headers/Led_Animations.h>
#include <Headers/ESP_Time.h>
#include <Headers/File_System.h>
#include <Headers/Task_Init.h>
#include <Headers/Server_Handles.h>
#include <Headers/CaptivePortal.h>
#include <Headers/Setups.h>
#include <Headers/Socket.h>
/** OWN HEADERS **/

#endif