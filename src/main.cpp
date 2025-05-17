#include <Arduino.h>
#include "robotka.h"

using namespace lx16a;  // pro zjednodušení názvů

String receivedMessage = "";             // buffer pro příchozí zprávu
auto &bus = rkSmartServoBus(0);          // sběrnice na UART1 (pin definovaný v robotka.h)

void setup() {
  // Serial pro komunikaci s PC
  Serial.begin(115200);
  while (!Serial) { delay(10); }
  Serial.println("ESP32 Servo Control (ID=0). Zadej úhel 0–240:");

  // Inicializace Robotka knihovny
  rkConfig cfg;
  cfg.motor_max_power_pct = 90;
  rkSetup(cfg);
}

void loop() {
  // Čtení ze sériové linky
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') {
      // Konec zprávy: zpracuj buffer
      receivedMessage.trim();
      if (receivedMessage.length() > 0) {
        int angle = receivedMessage.toInt();
        // Validace rozsahu 0–240°
        if (angle >= 0 && angle <= 240) {
          bus.set(0, Angle::deg(angle));
          Serial.printf("Servo 0 → %d°\n", angle);
        } else {
          Serial.println("Chyba: úhel musí být 0–240");
        }
      }
      receivedMessage = "";
    } else {
      // Přidávej znaky do bufferu
      receivedMessage += c;
    }
  }
}
//nefunguje!!!