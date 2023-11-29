#ifndef LED_H
#define LED_H


void setLED(short input) {
  digitalWrite(PIN_LED_STCP, LOW);
  shiftOut(PIN_LED_DS, PIN_LED_SHCP, LSBFIRST, input);
  digitalWrite(PIN_LED_STCP, HIGH);
}

void runLED() {
  short value = 1;
  while (value < 512) {
    setLED(value);

    value <<= 1;
    delay(50);
  }

  setLED(0);
}


#endif