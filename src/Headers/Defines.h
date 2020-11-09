#ifndef Defines_h
#define Defines_h

    /** TASKS **/
    xTaskHandle File_System_Task_Handle;
    /** TASKS **/
    #define ever (;;)
    #define FS_NO_GLOBALS
    #define U_LITTLEFS 100
    #define CONFIG_LITTLEFS_CACHE_SIZE 512
    
    DNSServer dnsServer;
    AsyncWebServer server(80);
    AsyncWebServerRequest *request;
    AsyncWebSocket ws("/MoodLamp");


    const char* ssid     = "KomaMoodLamp";
    const char* password = "komalamp";


    /** LED STRIP ANIMATIONS **/
    #define PIN 15
    #define NUM 25
    Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM,PIN, NEO_GRB + NEO_KHZ800);

    const char *ErrorLog = "/Errorlog.txt";
    const char *Config = "/Config.txt";

    /** SOCKET DEFINES */
        static const inline void Send_Async(String msg,String SpecChar);
        void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len);
    /** SOCKET DEFINES */

#endif