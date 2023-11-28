// Title  : Connect to WiFi
// Author : 咪路 <mail@mirumo.org>
// License: MIT (https://opensource.org/licenses/MIT)

#include <WiFiNINA.h>
#include <ArduinoMqttClient.h>

WiFiClient wifi;
MqttClient mqttClient(wifi);

#define ssid       ""
#define pass       ""
#define brokerHost ""
#define brokerPort 1883
#define led        9
#define temp       A1
#define button     10
#define topic      "arduino/controll/#"

unsigned long mqttPublishClock = 0;
short int ledStatus = 0;
bool buttonStatus = false;

void setup() {
  Serial.begin(9600);
  // while (!Serial) delay(1);

  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);

  _init();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnect!\nReconnect to WiFi.");
    _init();
    return;
  }

  if (!mqttClient.connected()) {
    Serial.println("Broker disconnect!\nReconnect to broker.");
    connectToMqttBroker();
    return;
  }

  mqttClient.poll();

  if (millis() - mqttPublishClock > 5000) {
    publishMessage("arduino/tempture", String(125. * analogRead(temp) / 256));
    publishMessage("arduino/led", String(ledStatus));
    mqttPublishClock = millis();
  }

  if (!digitalRead(button) && buttonStatus) {
    publishMessage("arduino/button", "Button is pressed");
    buttonStatus = false;
  }
  if (digitalRead(button)) {
    buttonStatus = true;
  }

  delay(20);
}

void _init() {
  connectToWifi();
  connectToMqttBroker();
}

void connectToWifi() {
  Serial.print("Try to connect to WiFi: ");
  Serial.print(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print('.');
    delay(3000);
  }
  Serial.println();
  Serial.println("Connect WiFi scuuessfully.");
  Serial.println();
}

void connectToMqttBroker() {
  Serial.print("Try to connect to broker: ");
  Serial.print(brokerHost);

  if (!mqttClient.connect(brokerHost, brokerPort)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    delay(3000);
    return;
  }

  Serial.println();
  Serial.println("Connect to broker successfully.");
  Serial.println();

  mqttClient.onMessage(onMqttMessage);
  mqttClient.subscribe(topic);
}

void onMqttMessage(int length) {
  // we received a message, print out the topic and contents
  Serial.println("Received a message with topic '");
  Serial.print(mqttClient.messageTopic());
  Serial.print("', length ");
  Serial.print(length);
  Serial.println(" bytes:");

  String _topic = String(mqttClient.messageTopic());

  if (_topic == "arduino/controll/led") {
    ledStatus = (char)mqttClient.read() - '0';
    digitalWrite(led, ledStatus);
  }
}

void publishMessage(String _topic, String payload) {
  mqttClient.beginMessage(_topic);
  mqttClient.print(payload);
  mqttClient.endMessage();
}

