#ifndef Defines_h
#define Defines_h

    //#define FASTLED_ALLOW_INTERRUPTS 0
    //#define FASTLED_INTERRUPT_RETRY_COUNT 1

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
    const char* password = "komalamp12345";

    /** LED STRIP ANIMATIONS **/
    typedef struct{
        boolean TEMPERATURE = 0,FIRE = 0,BASIC_FIRE = 0,RAINBOWWITHGLITTER = 0,RAINBOW = 0,JUGGLE = 0,WATER = 0,
        FIRE_NEW = 0,PRIDE = 0, SINUS = 0, BPM = 0,CONFETTI = 0;
        boolean TYPES[13] = 
        {TEMPERATURE,FIRE,BASIC_FIRE,RAINBOWWITHGLITTER,RAINBOW,JUGGLE,WATER,FIRE_NEW,PRIDE,SINUS,BPM,CONFETTI};
    }  Animation_types;
    Animation_types ANIMATION[4];

    typedef struct{
        boolean SOLIDBLUE = 0;
        boolean TYPES[2] = {SOLIDBLUE};
    } Static_types;
    Static_types STATIC[2];

    const char *ErrorLog = "/Errorlog.txt";
    const char *Config = "/Config.txt";
    /** FILE SYSTEM */
        static const inline void File_System_Init();
    /** FILE SYSTEM */

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