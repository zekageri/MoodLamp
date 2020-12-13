#ifndef Setups_h
#define Setups_h


static const inline void I2C_Begin(){Wire.begin(SDA,SCL,400000);}
static const inline void Get_Config(){}

const char* STA_ssid = "Emelet";
const char* STA_password = "Administrator";

int Attempts = 0;
static const inline void Handle_STA(){
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(STA_ssid, STA_password);
  delay(50);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      WiFi.disconnect();
      if(Attempts < 4){
        Attempts++;
        Handle_STA();
      }else{
        Serial.printf("WiFi Failed!\n");
        return;
      }
  }

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);
  HTTP_Requests();
  server.begin();
}

static const inline void Main_Setup(){
    Serial.begin(115200);
    I2C_Begin();
    delay(200);
    //adxl_Setup();
    Init_Tasks();
}

#endif