#ifndef Setups_h
#define Setups_h

static const inline void Handle_Captive(){
    WiFi.softAP(ssid, password);
    dnsServer.start(53, "*", WiFi.softAPIP());
    server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);
    server.begin();
    ws.onEvent(onWsEvent);
    server.addHandler(&ws);
    IPAddress IP = WiFi.softAPIP();
    Serial.print("Mood Lamp Started with ip: ");
    Serial.println(IP);
}

static const inline void Get_Config(){

}

static const inline void File_System_Init(){
    LITTLEFS.begin();
}

static const inline void Main_Setup(){
    File_System_Init();
    Handle_Captive();
    HTTP_Requests();
    pixels.begin();
    Init_Tasks();
}

#endif