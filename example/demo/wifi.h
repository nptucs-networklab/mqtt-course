#ifndef WIFI_H
#define WIFI_H

bool connectToWifi() {
  lcdClear();
  lcdPrint("WiFi connecting.");
  auto status = WiFi.begin(SSID, WIFI_PASSWORD);
  if (status != WL_CONNECTED) {
    lcdPrint("Failed", 1);
    return false;
  }

  lcdPrint("Successful", 1);
  return true;
}

#endif