#include <Arduino.h>
#include <Wire.h>
#include "motor_commands.h"
#include <iostream>
#include <RBCX.h>
//#include <Adafruit_TCS34725.h>

void trap() {
    Serial.println("trap\n");
    while (1);
}

//Adafruit_VL53L0X lox1; // První senzor (bude mít adresu 0x31)
//Adafruit_VL53L0X lox2; // Druhý senzor (bude mít adresu 0x32)

// Funkce pro inicializaci laserového senzoru
bool initLaserSensor(uint8_t address, Adafruit_VL53L0X &sensor) {
    Serial.print("Inicializace senzoru na adrese: 0x");
    Serial.println(address, HEX);

    if (!rkLaserInit(address, sensor, true)) {
        Serial.print("Nepodarilo se inicializovat laserovy senzor na adrese: 0x");
        Serial.println(address, HEX);
        return false;
    }

    Serial.print("Laserovy senzor inicializovan na adrese: 0x");
    Serial.println(address, HEX);
    return true;
}

void setup() {
    Serial.begin(115200);
    Serial.println("RB3204-RBCX");

    // Inicializace vlastní instance I2C s definovanými piny
    const int SDA_PIN = 21; // Replace with your SDA pin
    const int SCL_PIN = 22; // Replace with your SCL pin
    if (!Wire.begin()) {
        Serial.println("Error: Failed to initialize I2C bus. Check wiring and pin definitions.");
        trap();
    }

    /*/ Inicializace prvního laserového senzoru
    if (!initLaserSensor(0x31, lox1)) {
        trap();
    }

    // Inicializace druhého laserového senzoru
    if (!initLaserSensor(0x32, lox2)) {
        trap();
    }
    */
    Serial.println("Vsechny senzory inicializovany.");
}
void loop() {
    // Kontrola stavu tlačítek
    if (rkButtonIsPressed(BTN_ON)) {
        Serial.println("Button ON pressed");
        rkLedRed(true); // Turn on red LED
        delay(1000); // Wait for 500 milliseconds
        forward(-2000, 70); // Call a motor function
        delay(500); // Wait for the motor function to execute
        rkLedRed(false); // Turn off red LED
    } else if (rkButtonIsPressed(BTN_RIGHT)) {
        Serial.println("Button OFF pressed");
        rkLedBlue(true); // Turn on blue LED
        delay(1000); // Wait for 500 milliseconds
        forward(2000, 40); // Call a motor function
        delay(500); // Wait for the motor function to execute
        rkLedBlue(false); // Turn off blue LED
    } else if (rkButtonIsPressed(BTN_UP)) {
        Serial.println("Button UP pressed");
        rkLedGreen(true); // Turn on green LED
        delay(1000); // Wait for 500 milliseconds
        radius_r(-360, 200, 40); // Call a radius turn function
        delay(500); // Wait for the motor function to execute
        rkLedGreen(false); // Turn off green LED
    } else if (rkButtonIsPressed(BTN_DOWN)) {
        Serial.println("Button DOWN pressed");
        rkLedYellow(true); // Turn on yellow LED
        delay(1000); // Wait for 500 milliseconds
        radius_r(360, 200, 40); // Call a radius turn function
        delay(500); // Wait for the motor function to execute
        rkLedYellow(false); // Turn off yellow LED
    } else if (rkButtonIsPressed(BTN_LEFT)) {
        Serial.println("Button LEFT pressed");
        rkLedAll(true); // Turn on all LEDs
        delay(1000); // Wait for 500 milliseconds
        turn_on_spot(360); // Call a turn on spot function
        delay(500); // Wait for the motor function to execute
        rkLedAll(false); // Turn off all LEDs
    }
    delay(100); // Small delay to prevent busy waiting
}
/*
hele, tak to jsme nejak celkove osekaly a vylepsily tuhle knihovnu,
 ted by bylo dobry jeste udelat: 
 1) Pridat sem funkce na inializaci 
 a vyuziti laseroveho senzoru (ta inicializace by mela byt i pro vyce stejnych
  senzoru, takze budeme muset nastavovat adresy) 
  2) Pridat sem funkce na inializaci a vyuziti barevneho senzoru(ten staci 1) 
  3) vytvorit examply pro tuto novou knihovnu 
  4) nahrat na muj githab a udelat readme.md -- kde bude vse popsane
*/