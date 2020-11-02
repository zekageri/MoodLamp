#ifndef Server_Handles_h
#define Server_Handles_h
    static inline void HTTP_Requests(){
        server.onNotFound([](AsyncWebServerRequest *request){
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/NotFound.html", "text/html");
            //response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });

        server.on("/Bootstrap.min.css", HTTP_GET, [](AsyncWebServerRequest *request) {
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/Bootstrap.min.css", "text/css");
            //response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });

        server.on("/Index.css", HTTP_GET, [](AsyncWebServerRequest *request) {
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/Index.css", "text/css");
            //response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });

        server.on("/Bootstrap.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/Bootstrap.min.js", "text/javascript");
            //response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });

        server.on("/Jquery_3.3.5.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/Jquery_3.3.5.min.js", "text/javascript");
            //response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });

        server.on("/Index.js", HTTP_GET, [](AsyncWebServerRequest *request) {
            AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/Index.js", "text/javascript");
            //response->addHeader("Content-Encoding", "gzip");
            request->send(response);
        });

    }

#endif