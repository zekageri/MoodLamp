#ifndef Server_Handles_h
#define Server_Handles_h
    static const inline void Get_Animation(int ANIM){
        for(int i = 0; i < 13; i++){ANIMATION->TYPES[i] = 0;}
        ANIMATION->TYPES[ANIM] = 1;
        power = true;
    }
    static inline void HTTP_Requests(){
        server.on("/Index.html", HTTP_GET, [](AsyncWebServerRequest *request) {
            //Serial.println("Admin html");
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/Index.html.gz", "text/html");
            response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });

        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
            //Serial.println("Admin html");
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/LampBundle.html.gz", "text/html");
            response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });

        server.on("/Admin.css", HTTP_GET, [](AsyncWebServerRequest *request) {
            //Serial.println("Admin css");
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
            //Serial.println("bootstrap js");
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/Bootstrap.min.js.gz", "text/javascript");
            response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });

        server.on("/Jquery_3.3.5.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
            //Serial.println("Jquery");
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/Jquery_3.3.5.min.js.gz", "text/javascript");
            response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });

        server.on("/Index.js", HTTP_GET, [](AsyncWebServerRequest *request) {
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/Index.js.gz", "text/javascript");
            response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });

        server.on("/Set_Animation", HTTP_GET, [](AsyncWebServerRequest *request){
            AsyncWebParameter* p = request->getParam(0);
            if(p->value() != "OFF"){
                Get_Animation(p->value().toInt());
            }else{
                power = false;
            }
            AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "AnimSwitched;"+p->value());
            response->addHeader("Access-Control-Allow-Origin","*");
            request->send(response);
        });
        server.on("/AppIcon.png", HTTP_GET, [](AsyncWebServerRequest *request) {
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/AppIcon.png", "image/x-icon");
            request->send(response);
        });

        server.on("/edelsans_regular.otf", HTTP_GET, [](AsyncWebServerRequest *request) {
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/edelsans_regular.otf.gz", "font/opentype");
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