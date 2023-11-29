#ifndef SENSORS_H
#define SENSORS_H

float getTemperature() {
  return 125. * analogRead(PIN_TEMPERATURE) / 256;
}

int getPhotoresistor() {
  return analogRead(PIN_CDS);
}

#endif
