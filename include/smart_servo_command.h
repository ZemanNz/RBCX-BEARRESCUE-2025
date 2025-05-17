#include <Arduino.h>
#include "robotka.h"

using namespace lx16a;

// Získání instance sběrnice pro komunikaci se servy
auto &bus = rkSmartServoBus(0);

// Funkce pro inicializaci serva
// id: ID serva (0–253)
// low, high: Dolní a horní limit úhlu serva v ° (výchozí 0 a 240)
void s_s_init(int id, int low = 0, int high = 240) {
    bus.setAutoStop(id, false); // Vypnutí auto-stopu (ochrany proti zaseknutí)
    bus.limit(id, Angle::deg(low), Angle::deg(high)); // Nastavení mechanických limitů pohybu
    bus.setAutoStopParams(
        SmartServoBus::AutoStopParams{
            .max_diff_centideg = 2000,     // Max. rozdíl mezi očekávanou a reálnou pozicí v setinách stupně
            .max_diff_readings = 3,        // Kolikrát za sebou musí být rozdíl překročen, aby se aktivoval auto-stop
        });
    Serial.printf("Servo %d inicializováno\n", id);
}

// Funkce pro rychlý a přímý pohyb serva bez regulace
// id: ID serva
// angle: požadovaný cílový úhel v rozsahu 0–240°
void s_s_move(int id, int angle) {
    if (angle < 0 || angle > 240) {
        Serial.println("Chyba: Úhel musí být v rozsahu 0–240 stupňů.");
        return;
    }
    bus.setAutoStop(id, false); // Vypnutí auto-stopu pro přímý pohyb
    bus.set(id, Angle::deg(angle)); // Odeslání cílové pozice (bez rychlosti -> okamžitý skok)
    Serial.printf("Servo %d nastaveno na %d stupňů\n", id, angle);
}

// Funkce pro plynulý pohyb serva s ochranou proti zaseknutí
// id: ID serva
// angle: požadovaný úhel
// speed: rychlost pohybu v jednotkách (výchozí 200)
//        vyšší = rychlejší; 0 = nejrychlejší možný pohyb (skok)
void s_s_soft_move(int id, int angle, int speed = 200.0) {
    if (angle < 0 || angle > 240) {
        Serial.println("Chyba: Úhel musí být v rozsahu 0–240 stupňů.");
        return;
    }
    bus.setAutoStop(id, true); // Zapnutí auto-stopu – ochrana proti přetížení
    bus.set(id, Angle::deg(angle), speed); // Nastavení pozice s rychlostí
    Serial.printf("Servo %d soft_move na %d stupňů rychlostí %d\n", id, angle, speed);
}
