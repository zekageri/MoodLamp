#ifndef Socket_h
#define Socket_h

    AsyncWebSocketClient * globalClient = NULL;
    void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
        if(type == WS_EVT_CONNECT){
            String bright = String(currentBrightness)+";Brightness";
            globalClient = client;
            ws.text(client->id(),bright);
        } else if(type == WS_EVT_DISCONNECT){
            globalClient = NULL;
        }
    }

    static const inline void Send_Async(String msg,String SpecChar){
        if(globalClient != NULL && globalClient->status() == WS_CONNECTED){
            if (ws.count() > 0){
                msg += SpecChar;
                char textBuffer[msg.length()+1];
                msg.toCharArray(textBuffer,msg.length()+1);
                ws.textAll(textBuffer);
            }
        }
    }

#endif