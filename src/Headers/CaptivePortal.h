#ifndef CaptivePortal_h
#define CaptivePortal_h


class CaptiveRequestHandler : public AsyncWebHandler {
public:
  CaptiveRequestHandler() {HTTP_Requests();}
  virtual ~CaptiveRequestHandler() {}
  bool canHandle(AsyncWebServerRequest *request){
    return true;
  }

void handleRequest(AsyncWebServerRequest *request) {
    AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/LampBundle.html.gz", "text/html");
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
 }

};

static const inline void Handle_Captive(){
    WiFi.softAP(ssid); //, password
    delay(100);
    dnsServer.start(53, "*", WiFi.softAPIP());
    ws.onEvent(onWsEvent);
    server.addHandler(&ws);
    server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);
    server.begin();
    delay(100);
    IPAddress IP = WiFi.softAPIP();
    Serial.print("Mood Lamp Started with ip: ");
    Serial.println(IP);
}

void CaptivePortal( void * parameter ){
  //Handle_STA();
  //vTaskDelete(NULL);
  //Handle_Captive();
  /*for ever{
    dnsServer.processNextRequest();
    vTaskDelay(1);
  }*/
}
#endif