#ifndef Server_Handles_h
#define Server_Handles_h
    static inline void HTTP_Requests(){
        server.on("/Icon.png", HTTP_GET, [](AsyncWebServerRequest *request) {
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/Appicon.png.gz", "image/x-icon");
            response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });

        server.on("/Admin.html", HTTP_GET, [](AsyncWebServerRequest *request) {
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/Admin.html.gz", "text/html");
            response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });

        server.on("/Admin.css", HTTP_GET, [](AsyncWebServerRequest *request) {
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/Admin.min.css.gz", "text/css");
            response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });
    /*
        server.on("/Admin.css", HTTP_GET, [](AsyncWebServerRequest *request) {
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/Admin.css.gz", "text/css");
            response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });*/
/*
        server.on("/Admin.js", HTTP_GET, [](AsyncWebServerRequest *request) {
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/Admin.js.gz", "text/javascript");
            response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });

        server.on("/Bootstrap.min.css", HTTP_GET, [](AsyncWebServerRequest *request) {
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/Bootstrap.min.css.gz", "text/css");
            response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });
*/
        server.on("/Index.css", HTTP_GET, [](AsyncWebServerRequest *request) {
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/Index.css.gz", "text/css");
            response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });
/*
        server.on("/fontawesome.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/fontawesome.min.js.gz", "text/javascript");
            response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });
        server.on("/solid.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/solid.min.js.gz", "text/javascript");
            response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });
*/
        server.on("/Bootstrap.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/Bootstrap.min.js.gz", "text/javascript");
            response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });

        server.on("/Jquery_3.3.5.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
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
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/NotFound.html.gz", "text/html");
            response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });

    }

#endif