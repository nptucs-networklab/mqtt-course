#ifndef CONFIG_H
#define CONFIG_H

#define PIN_TEMPERATURE A0
#define PIN_CDS A1
#define PIN_LCD 2,3,4,5,6,7,8 // RS, R/W, Enable, D4, D5, D6, D7
#define PIN_MODE_BUTTON 10
#define PIN_LED_STCP 9
#define PIN_LED_SHCP 11
#define PIN_LED_DS 12


#define SSID "咪路"
#define WIFI_PASSWORD "mysteryperson"

#define BROKER_HOST "mqtt.nptucsai.org"
#define BROKER_PORT 1883

#define TOPIC "ARDUINO/CONTROLL/#"




#endif