#include "uart_commands.h"
#include "robotka.h"
#include <Arduino.h>

struct MyStruct {
    uint8_t id;
    int16_t value;
};

void setup() {
    Serial.begin(115200);
    while (!Serial);
    Serial.println("UART1 Receiver with framing");
    rkConfig cfg;
    rkSetup(cfg);
    delay(1000);
    rkLedRed(true); // Turn on red LED
    rkLedBlue(true); // Turn on blue LED
    while (!Serial);
    uartInit();
}

void loop() {
    MyStruct data;
    if (uartReceiveStruct(data)) {
        Serial.print("ID: "); Serial.print(data.id);
        Serial.print(", Value: "); Serial.println(data.value);
    }
}