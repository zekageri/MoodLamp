#ifndef Server_Handles_h
#define Server_Handles_h
    static inline void HTTP_Requests(){
        server.on("/Admin.css", HTTP_GET, [](AsyncWebServerRequest *request) {
            //Serial.println("Admin css");
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/Admin.min.css.gz", "text/css");
            response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });

        server.on("/nouislider.min.css", HTTP_GET, [](AsyncWebServerRequest *request) {
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/nouislider.min.css.gz", "text/css");
            response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });
        server.on("/nouislider.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/nouislider.min.js.gz", "text/javascript");
            response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });

        server.on("/Set_Static", HTTP_GET, [](AsyncWebServerRequest *request){
            AsyncWebParameter* p = request->getParam(0);
            Web_R = p->value().toInt();
            p = request->getParam(1);
            Web_G = p->value().toInt();
            p = request->getParam(2);
            Web_B = p->value().toInt();
            Can_Set_Static = true;
            power = true;
            //Set_Static_From_Web(R,G,B);
            AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "Static Color Set");
            response->addHeader("Access-Control-Allow-Origin","*");
            request->send(response);
        });

        server.on("/Set_Brightness", HTTP_GET, [](AsyncWebServerRequest *request){
            AsyncWebParameter* p = request->getParam(0);
            currentBrightness = p->value().toInt();
            AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "Brightness_OK");
            response->addHeader("Access-Control-Allow-Origin","*");
            request->send(response);
        });

        server.on("/Set_Time", HTTP_GET, [](AsyncWebServerRequest *request){
            AsyncWebParameter* p = request->getParam(0);
            int nowYear = p->value().toInt();
            p = request->getParam(1);
            int nowMonth = p->value().toInt();
            p = request->getParam(2);
            int nowDay = p->value().toInt();
            p = request->getParam(3);
            int nowHour = p->value().toInt();
            p = request->getParam(4);
            int nowMin = p->value().toInt();
            p = request->getParam(5);
            int nowSec = p->value().toInt();
            
            Time.Set_Time(nowYear,nowMonth,nowDay,nowHour,nowMin,nowSec);
            AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "TimeSet_OK");
            response->addHeader("Access-Control-Allow-Origin","*");
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