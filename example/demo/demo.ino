#include "library.h"

bool modeBtnStatus = true;
bool publishBtnStatus = true;
short liquidMode = 0;
int lcdInterval;

void setup() {

  lcdInit();
  lcdPrint("Start...");

  pinMode(PIN_LED_STCP, OUTPUT);
  pinMode(PIN_LED_SHCP, OUTPUT);
  pinMode(PIN_LED_DS, OUTPUT);
  pinMode(PIN_MODE_BUTTON, INPUT);
  pinMode(PIN_PUBLISH_BUTTON, INPUT);

  setLED(0);


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
  //   return;
  // }
  //   do {
  //     delay(5000);
  //   } while (!connectToWifi());
  //   return;
  // }

  if (!mqttClient.connected()) {
    lcdClear();
    lcdPrint("Broker disconnect.");
    connectToMqttBroker();
    return;
  }

  int current = millis();
  mqttClient.poll();


  if (modeBtnStatus && digitalRead(PIN_MODE_BUTTON)) {
    ++liquidMode %= 3;
    modeBtnStatus = false;
    runLED();
  }

  if (publishBtnStatus && digitalRead(PIN_PUBLISH_BUTTON)) {
    publishBtnStatus = false;
    publishMessage();
    delay(100);
  }

  while(current - lcdInterval > 500) {
    lcdModeSwitch(liquidMode);
    lcdInterval = current;
  }

  if (!digitalRead(PIN_MODE_BUTTON)) modeBtnStatus = true;
  if (!digitalRead(PIN_PUBLISH_BUTTON)) publishBtnStatus = true;

  delay(10);
}
