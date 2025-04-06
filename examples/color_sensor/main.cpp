#include "robotka.h"

void setup() {
    Serial.begin(115200);

    // Inicializace barevného senzoru
    if (!rkColorSensorInit()) {
        Serial.println("Failed to initialize color sensor!");
        while (true);
    }
}

void loop() {
    float r, g, b;

    // Čtení hodnot RGB z barevného senzoru
    if (rkColorSensorGetRGB(&r, &g, &b)) {
        Serial.printf("RGB: R = %f, G = %f, B = %f\n", r, g, b);
    } else {
        Serial.println("Failed to read RGB values.");
    }

    delay(500);
}