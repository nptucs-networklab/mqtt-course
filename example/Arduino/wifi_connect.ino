// Title  : Connect to WiFi
// Author : 咪路 <mail@mirumo.org>
// License: MIT (https://opensource.org/licenses/MIT)

#include <WiFiNINA.h>

#define ssid ""
#define pass ""

const int retry  = 3;
int status = WL_IDLE_STATUS;
void printMAC();

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Connect WiFi
  Serial.print("Try to connect to ");
  Serial.print(ssid);
  for (int i=0; i<retry; ++i) {
    status = WiFi.begin(ssid, pass);
    if (status == WL_CONNECTED) break;
    
    delay(3000);
    Serial.print('.');
  }
  Serial.println();

  if (status != WL_CONNECTED) {
    Serial.println("Connect Failed.");
    while (true);
  }

  Serial.println("Connect Successfully.");


  printWiFiInfo();
  
}

void loop() {
  delay(10);
}

void printWiFiInfo() {
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  for (int i=5; i>0; --i) {
    if (mac[i] < 16) Serial.print('0');
    Serial.print(mac[i], HEX);
    Serial.print(':');
  }

  Serial.println(mac[0], HEX);

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
}
