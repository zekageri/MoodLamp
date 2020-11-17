#ifndef Defines_h
#define Defines_h

    /** TASKS **/
    xTaskHandle File_System_Task_Handle;
    xTaskHandle Time_System_Task_Handle;
    xTaskHandle Animation_Task_Handle;
    xTaskHandle CaptivePortal_Task_Handle;
    /** TASKS **/
    #define ever (;;)
    #define FS_NO_GLOBALS
    #define U_LITTLEFS 100
    #define CONFIG_LITTLEFS_CACHE_SIZE 512
    RTC_DS3231 rtc;
    
    DNSServer dnsServer;
    AsyncWebServer server(80);
    AsyncWebServerRequest *request;
    AsyncWebSocket ws("/MoodLamp");


    const char* ssid     = "KomaMoodLamp";
    const char* password = "komalamp";


    /** LED STRIP ANIMATIONS **/
    typedef struct{
        boolean TEMPERATURE = 0,FIRE = 0,BASIC_FIRE = 0;
        boolean TYPES[4] = {TEMPERATURE,FIRE,BASIC_FIRE};
    }  Animation_types;
    Animation_types ANIMATION[4];

    typedef struct{
        boolean PRIDE = 1;
        boolean TYPES[2] = {PRIDE};
    } Static_types;
    Static_types STATIC[2];

    const char *ErrorLog = "/Errorlog.txt";
    const char *Config = "/Config.txt";

    /** SOCKET DEFINES */
        static const inline void Handle_Captive();
        static const inline void Send_Async(String msg,String SpecChar);
        void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len);
    /** SOCKET DEFINES */

    /** ESP TIME **/
        void Time_System( void * parameter );
    /** ESP TIME **/

    /** TASK DECLARATIONS **/
        void CaptivePortal( void * parameter );
    /** TASK DECLARATIONS **/
#endif