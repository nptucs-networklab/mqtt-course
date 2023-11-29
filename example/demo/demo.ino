#include "library.h"

bool modeBtnStatus = true;
short liquidMode = 0;
int lcdInterval;

void setup() {

  lcdInit();
  lcdPrint("Start...");
  do {
    delay(5000);
  } while (!connectToWifi());

  connectToMqttBroker();

  lcdInterval = millis() + 500;
}

void loop() {

  // if (wifi.status() != WL_CONNECTED) {
  //   lcdClear();
  //   lcdPrint("Wifi disconnect.");
    
  //   do {
  //     delay(5000);
  //   } while (!connectToWifi());
  //   return;
  // }

  // if (!mqttClient.connected()) {
  //   lcdClear();
  //   lcdPrint("Broker disconnect.");
  //   connectToMqttBroker();
  //   return;
  // }

  int current = millis();
  mqttClient.poll();


  if (modeBtnStatus && digitalRead(PIN_MODE_BUTTON)) {
    ++liquidMode %= 3;
    modeBtnStatus = false;
  }

  while(current - lcdInterval > 500) {
    lcdModeSwitch(liquidMode);
    lcdInterval = current;
  }


  if (!digitalRead(PIN_MODE_BUTTON)) modeBtnStatus = true;
  delay(10);
}
