#ifndef MQTT_H
#define MQTT_H

WiFiClient wifi;
MqttClient mqttClient(wifi);

void publishMessage();

void onMqttMessage(int length) {
  String topic = String(mqttClient.messageTopic());
  Serial.println(topic);
  if (topic == "ARDUINO/CONTROLL/PUBLISH") {
    publishMessage();
  }
}

bool connectToMqttBroker() {
  lcdClear();
  lcdPrint("Connect broker.");

  if (!mqttClient.connect(BROKER_HOST, BROKER_PORT)) {
    lcdPrint("Failed", 1);
    delay(3000);
    return false;
  }
  lcdPrint("Successful", 1);

  mqttClient.onMessage(onMqttMessage);
  mqttClient.subscribe(TOPIC);

  return true;
}

void publishMessage() {
  mqttClient.beginMessage("ARDUINO/TEMPERATURE");
  mqttClient.print((String)getTemperature());
  mqttClient.endMessage();

  mqttClient.beginMessage("ARDUINO/PHOTORESISTOR");
  mqttClient.print((String)getPhotoresistor());
  mqttClient.endMessage();
}

#endif