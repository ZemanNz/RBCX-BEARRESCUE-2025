#include <Arduino.h>
#include "robotka.h"
#include "motor_commands.h"

void projeti_bludiste_tam(){
    Serial.println("projeti bludiště tam");
    // Příkaz pro projetí bludiště
    forward(595, 70); // Předpokládáme, že tato funkce je definována v motor_commands.h
    radius_r(180, 200, 60);
    radius_l(190, 200, 60); 
    back_buttons(60);
    forward(1400, 95);
    Serial.println("projeti bludiště hotova");
}

void setup() {
  Serial.begin(115200);
  rkConfig cfg;
  rkSetup(cfg);
  Serial.printf("Battery percent: \n");
  printf(":", rkBatteryPercent());
  Serial.printf("Battery voltage: \n");
  printf(":",rkBatteryVoltageMv());
  //rkLedRed(true); // Turn on red LED
  rkLedBlue(true); // Turn on blue LED
  printf("Robotka started!\n");
    // Nastavení tlačítek
  pinMode(Bbutton1, INPUT_PULLUP);
  pinMode(Bbutton2, INPUT_PULLUP);
  Serial.println("Motor example started!");

}

void loop() {
    // Kontrola stavu tlačítek
    if(digitalRead(Bbutton1) == LOW) {
        Serial.println("Button 1 pressed");
        rkLedGreen(true); // Turn on blue LED
        delay(3000); // Wait for 500 milliseconds
        projeti_bludiste_tam(); // Call the function to drive through the maze
        //delay(1000); // Wait for the motor function to execute
        rkLedGreen(false); // Turn off blue LED
    } else if(digitalRead(Bbutton2) == LOW) {
        Serial.println("Button 2 pressed");
        rkLedYellow(true); // Turn on yellow LED
        delay(3000); // Wait for 500 milliseconds
        
        rkLedYellow(false); // Turn off yellow LED
    }
    delay(100); // Small delay to prevent busy waiting
}