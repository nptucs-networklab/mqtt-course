#ifndef LIQUID_H
#define LIQUID_H

LiquidCrystal lcd(PIN_LCD);

void lcdInit() {
  lcd.begin(16, 2);
}

void lcdClear() {
  lcd.clear();
}

void lcdPrint(String msg, short y = 0, short x = 0) {
  lcd.setCursor(x, y);
  lcd.print(msg);
}

void lcdModeSwitch(short mode) {
  lcdClear();

  switch (mode) {
    case 0:
      lcd.setCursor(0, 0);
      lcd.print("I");
      lcd.print(WiFi.localIP());
      lcd.setCursor(0, 1);
      lcd.print("G");
      lcd.print(WiFi.gatewayIP());
      return;
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("Temp: ");
      lcd.print(getTemperature());
      lcd.setCursor(1, 1);
      lcd.print("CDS: ");
      lcd.print(getPhotoresistor());
      return;
    case 2:
      lcdPrint("Mode 2");
      return;
    default:
      return;
  }
}

#endif