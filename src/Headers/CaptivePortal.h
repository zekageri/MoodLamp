#ifndef CaptivePortal_h
#define CaptivePortal_h

class CaptiveRequestHandler : public AsyncWebHandler {
public:
  CaptiveRequestHandler() {}
  virtual ~CaptiveRequestHandler() {}
  bool canHandle(AsyncWebServerRequest *request){
    return true;
  }

void handleRequest(AsyncWebServerRequest *request) {
    AsyncWebServerResponse* response = request->beginResponse(LITTLEFS, "/Index.html", "text/html");
    request->send(response);
 }
};

#endif