#include <Wire.h>
#include <Adafruit_VL53L0X.h>
#include <iostream>
#include <robotka.h> // Zahrnutí hlavičkového souboru s funkcemi rkLaserInit a rkLaserGetDistance
// Vytvoření dvou objektů pro senzory
Adafruit_VL53L0X lox1; // První senzor (bude mít adresu 0x31)
Adafruit_VL53L0X lox2; // Druhý senzor (zůstane na adrese 0x29)

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(10); } // Počká, dokud se sériová linka nezačne

  // Inicializace prvního senzoru (změní adresu na 0x31)
  if (!rkLaserInit(0x31, lox1, true)) {
    Serial.println("Nepodarilo se inicializovat prvni senzor!");
    while (1);
  }

  // Inicializace druhého senzoru (zůstane na výchozí adrese 0x29)
  if (!rkLaserInit(0x29, lox2, false)) {
    Serial.println("Nepodarilo se inicializovat druhy senzor!");
    while (1);
  }

  Serial.println("Oba senzory byly uspesne inicializovany.");
}

void loop() {
  // Získání vzdálenosti z prvního senzoru
  int16_t distance1 = rkLaserGetDistance(lox1);
  Serial.print("Sensor1 (adresa 0x31): ");
  if (distance1 != -1) {
    Serial.print("Vzdalenost: ");
    Serial.print(distance1);
    Serial.println(" cm");
  } else {
    Serial.println("Mimo dosah");
  }

  // Získání vzdálenosti z druhého senzoru
  int16_t distance2 = rkLaserGetDistance(lox2);
  Serial.print("Sensor2 (adresa 0x29): ");
  if (distance2 != -1) {
    Serial.print("Vzdalenost: ");
    Serial.print(distance2);
    Serial.println(" cm");
  } else {
    Serial.println("Mimo dosah");
  }

  Serial.println("-----------------------------");
  delay(500); // Krátká prodleva mezi měřeními
}