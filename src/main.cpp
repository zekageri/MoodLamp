#include <Headers/Includes.h>


void setup() {
  Serial.begin(115200);
  Main_Setup();
}

void loop() {
  dnsServer.processNextRequest();
  vTaskDelay(2);
}