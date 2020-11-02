#ifndef Defines_h
#define Defines_h

DNSServer dnsServer;
AsyncWebServer server(80);

const char* ssid     = "KomaMoodLamp";
const char* password = "komalamp";


/** LED STRIP ANIMATIONS **/
#define PIN 15
#define NUM 25
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM,PIN, NEO_GRB + NEO_KHZ800);

#endif