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
    AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/Admin.html.gz", "text/html");
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
 }

};

void CaptivePortal( void * parameter ){
  Handle_Captive();
  for ever{
    dnsServer.processNextRequest();
    vTaskDelay(1);
  }
}
#endif