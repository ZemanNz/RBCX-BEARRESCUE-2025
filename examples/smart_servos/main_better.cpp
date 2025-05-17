#include <Arduino.h>
#include "robotka.h"
#include "smart_servo_command.h"
using namespace lx16a;

void close_claw() {
    s_s_soft_move(1, 0, 70.0); // Zavření klepeta na 10° s rychlostí 200
    delay(1000); // Počkáme, až servo dokončí pohyb
}
void open_claw() {
    s_s_move(1, 160); // Otevření klepeta na 160° s rychlostí 200
    delay(1000); // Počkáme, až servo dokončí pohyb
}
void setup() {
    Serial.begin(115200);
    delay(1000); // Krátká pauza pro inicializaci sériové linky

    // Inicializace serva s ID 1 a limity 10° až 200°
    s_s_init(1, 0, 160);

    delay(1000); // Pauza před dalším příkazem

    // Tvrdý přímý pohyb na 90°
    s_s_move(1, 90);

    delay(2000); // Počkáme, až servo dokončí pohyb

    // Jemný plynulý pohyb na 150° s rychlostí 150
    s_s_soft_move(1, 150, 150);

    delay(2000); // Počkáme, až servo dokončí pohyb

    // Zavření klepeta
    close_claw();
    delay(2000); // Počkáme, až servo dokončí pohyb
    // Otevření klepeta
    open_claw();
}

void loop() {
    // Prázdná smyčka
}
