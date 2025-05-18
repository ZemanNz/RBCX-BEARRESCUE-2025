#include <Arduino.h>
#include <stdint.h>
#include "smart_servo_command.h"
#include "robotka.h"

#define RX1_PIN   5
#define TX1_PIN   4  // mimochodem nepotřebujeme, ale Arduino vyžaduje parametry

// Stejná struktura (packed implicitně)
typedef struct __attribute__((packed)) {
    uint8_t  id;
    int16_t  value;
} ServoMsg;


const uint8_t SYNC0 = 0xAA;
const uint8_t SYNC1 = 0x55;

enum RxState { WAIT_SYNC0, WAIT_SYNC1, READ_PAYLOAD };
RxState state = WAIT_SYNC0;

static const size_t PAYLOAD_SIZE = sizeof(ServoMsg);
uint8_t buf[PAYLOAD_SIZE];
size_t idx = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("UART1 Receiver with framing");
  rkConfig cfg;
  rkSetup(cfg);
  delay(1000);
  rkLedRed(true); // Turn on red LED
  rkLedBlue(true); // Turn on blue LED
  Serial2.begin(115200, SERIAL_8N1, 16,17); // Nastavení UART2
}

void loop() {
  while (Serial2.available()) {
    uint8_t c = Serial2.read();
    switch (state) {
      case WAIT_SYNC0:
        if (c == SYNC0) state = WAIT_SYNC1;
        break;
      case WAIT_SYNC1:
        if (c == SYNC1) {
          state = READ_PAYLOAD;
          idx = 0;
        } else {
          // možná c je už SYNC0, zkusit znovu
          state = (c == SYNC0) ? WAIT_SYNC1 : WAIT_SYNC0;
        }
        break;
      case READ_PAYLOAD:
        buf[idx++] = c;
        if (idx >= PAYLOAD_SIZE) {
          // máme celý payload
          ServoMsg m;
          memcpy(&m, buf, PAYLOAD_SIZE);
          Serial.print("Received: ");
          Serial.print(m.id);
          Serial.print(", ");
          Serial.println(m.value);
          ////////////////////////
          s_s_soft_move(m.id, m.value, 70);
          //////////////
          // zpracování zprávy
          state = WAIT_SYNC0;
        }
        break;
    }
  }
}