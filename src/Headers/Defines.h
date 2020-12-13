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
    RTC_DS3231 rtc;
    
    DNSServer dnsServer;
    AsyncWebServer server(80);
    AsyncWebServerRequest *request;
    AsyncWebSocket ws("/MoodLamp");


    // I2C
    #define SCL 22
    #define SDA 21
    
    boolean is_ADXL = false;
    Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
    
    
    const char* ssid     = "KomaMoodLamp";
    const char* password = "komalamp12345";

    const char *ErrorLog    = "/Errorlog.txt";
    const char *Config      = "/Config.txt";
    const char *CurrentAnimation      = "/CurrentAnimation.txt";

    static const inline void Get_Animation(int ANIM);

    /** ADXL */
        static const inline void adxl_Setup();
    /** ADXL */
    /** FILE SYSTEM */
        static const inline void File_System_Init();
        static const inline void Save_Current_Animation(int animNUM);
        static const inline int Get_Current_Animation();
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