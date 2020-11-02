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
#include <Adafruit_NeoPixel.h>

/** VENDOR HEADERS */

/***********************************/

/** OWN HEADERS **/
#include <Headers/Defines.h>

#include <Headers/Task_Init.h>
#include <Headers/Server_Handles.h>
#include <Headers/CaptivePortal.h>
#include <Headers/Led_Animations.h>
#include <Headers/Setups.h>
/** OWN HEADERS **/

#endif