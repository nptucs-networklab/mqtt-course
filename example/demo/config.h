#ifndef CONFIG_H
#define CONFIG_H

#define PIN_TEMPERATURE A0
#define PIN_CDS A1
#define PIN_LCD 8,7,6,5,4,3,2 // RS, R/W, Enable, D4, D5, D6, D7
#define PIN_MODE_BUTTON 12
#define PIN_PUBLISH_BUTTON 13
#define PIN_LED_STCP 10
#define PIN_LED_SHCP 11
#define PIN_LED_DS 9


#define SSID "JunYu"
#define WIFI_PASSWORD "98765432"

#define BROKER_HOST "mqtt.nptucsai.org"
#define BROKER_PORT 1883

#define TOPIC "ARDUINO/CONTROLL/#"


#endif