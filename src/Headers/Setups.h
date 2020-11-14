#ifndef Setups_h
#define Setups_h

static const inline void Handle_Captive(){
    WiFi.softAP(ssid, password);
    dnsServer.start(53, "*", WiFi.softAPIP());
    ws.onEvent(onWsEvent);
    server.addHandler(&ws);
    server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);
    server.begin();
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
    Wire.begin(21,22);
    File_System_Init();
    Handle_Captive();
    //pixels.begin();
    Init_Tasks();
}

#endif