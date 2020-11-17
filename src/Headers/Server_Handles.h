#ifndef Server_Handles_h
#define Server_Handles_h
    static const inline void Get_Animation(int ANIM){
        for(int i = 0; i < 13; i++){ANIMATION->TYPES[i] = 0;}
        ANIMATION->TYPES[ANIM] = 1;
        power = 1;
    }
    static inline void HTTP_Requests(){
        server.on("/Set_Animation", HTTP_GET, [](AsyncWebServerRequest *request){
            AsyncWebParameter* p = request->getParam(0);
            if(p->value() != "OFF"){
                Get_Animation(p->value().toInt());
            }else{
                power = 0;
            }
            AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "AnimSwitched;"+p->value());
            response->addHeader("Access-Control-Allow-Origin","*");
            request->send(response);
        });
        server.on("/Icon.png", HTTP_GET, [](AsyncWebServerRequest *request) {
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/Appicon.png.gz", "image/x-icon");
            response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });

        server.on("/Admin.html", HTTP_GET, [](AsyncWebServerRequest *request) {
            Serial.println("Admin html");
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/Admin.html.gz", "text/html");
            response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });

        server.on("/Admin.css", HTTP_GET, [](AsyncWebServerRequest *request) {
            Serial.println("Admin css");
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/Admin.min.css.gz", "text/css");
            response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });

        server.on("/Index.css", HTTP_GET, [](AsyncWebServerRequest *request) {
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/Index.css.gz", "text/css");
            response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });

        server.on("/Bootstrap.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
            Serial.println("bootstrap js");
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/Bootstrap.min.js.gz", "text/javascript");
            response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });

        server.on("/Jquery_3.3.5.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
            Serial.println("Jquery");
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/Jquery_3.3.5.min.js.gz", "text/javascript");
            response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });

        server.on("/Index.js", HTTP_GET, [](AsyncWebServerRequest *request) {
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/Index.js.gz", "text/javascript");
            response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });

        server.onNotFound([](AsyncWebServerRequest *request){
            Serial.println("NOTFOUND!");
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/NotFound.html.gz", "text/html");
            response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });

    }

#endif