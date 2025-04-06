#ifdef USE_VL53L0X
#include <Wire.h>
#include <Adafruit_VL53L0X.h>

#define SENSOR2_XSHUT_PIN 3  // Pro senzor, který zůstane na výchozí adrese
#define VL53L0X_DEFAULT_ADDR 0x29  // Výchozí adresa senzoru
#define VL53L0X_NEW_ADDR     0x31  // Nová adresa pro první senzor
#define I2C_SLAVE_DEVICE_ADDRESS 0x8A  // Registr, do kterého se zapíše nová adresa

void writeRegister(uint8_t deviceAddress, uint8_t reg, uint8_t value) {
    Wire.beginTransmission(deviceAddress);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

bool rkLaserInit(uint8_t address, Adafruit_VL53L0X& sensor, bool prvni) {
    delay(10);  // Krátká prodleva na reset
    // Nastavení XSHUT pinu jako výstup
    pinMode(SENSOR2_XSHUT_PIN, OUTPUT);
    // Resetujeme senzor (XSHUT = LOW)
    digitalWrite(SENSOR2_XSHUT_PIN, LOW);
    delay(10);
    if(prvni){
        sensor.begin();
        delay(10);
        writeRegister(VL53L0X_DEFAULT_ADDR, I2C_SLAVE_DEVICE_ADDRESS, VL53L0X_NEW_ADDR);
        delay(10);
        sensor.begin(VL53L0X_NEW_ADDR);
        delay(10);  // Počkej, než se sensor2 spustí
        return true;
    }
    else{
        digitalWrite(SENSOR2_XSHUT_PIN, HIGH);
        delay(10);  // Počkej, než se sensor2 spustí
        sensor.begin();
        return true;
    }
    // Nejprve resetneme oba senzory: oba XSHUT nastavíme na LOW
}

int16_t rkLaserGetDistance(Adafruit_VL53L0X& sensor) {
    VL53L0X_RangingMeasurementData_t measure1;
    sensor.rangingTest(&measure1, true);
    if (measure1.RangeStatus != 4) {
        return measure1.RangeMilliMeter / 10.0; // Vzdálenost v cm
    } else {
        return -1; // Mimo dosah
    }
}
#endif