
#include <Arduino.h>
#include "robotka.h"
#include "smart_servo_command.h"
using namespace lx16a;

// Pomocná funkce pro parsování parametrů z řetězce
bool parseParams(const String& params, int* out, int count) {
  int idx = 0, last = 0;
  for (int i = 0; i < count; ++i) {
    idx = params.indexOf(',', last);
    String val = (idx == -1) ? params.substring(last) : params.substring(last, idx);
    val.trim();
    if (!val.length()) return false;
    out[i] = val.toInt();
    last = idx + 1;
    if (idx == -1 && i < count - 1) return false;
  }
  return true;
}

void processCommand(const String &cmd) {
  if (cmd.startsWith("s_s_init(")) {
    int params[3];
    int start = cmd.indexOf('(') + 1;
    int end = cmd.indexOf(')');
    if (start < 1 || end < 0) {
      Serial.println("Chybný formát s_s_init");
      return;
    }
    String paramStr = cmd.substring(start, end);
    if (!parseParams(paramStr, params, 3)) {
      Serial.println("Chyba v parametrech s_s_init");
      return;
    }
    s_s_init(params[0], params[1], params[2]);
    Serial.println("s_s_init zavoláno");
    return;
  }
  if (cmd.startsWith("s_s_move(")) {
    int params[2];
    int start = cmd.indexOf('(') + 1;
    int end = cmd.indexOf(')');
    if (start < 1 || end < 0) {
      Serial.println("Chybný formát s_s_move");
      return;
    }
    String paramStr = cmd.substring(start, end);
    if (!parseParams(paramStr, params, 2)) {
      Serial.println("Chyba v parametrech s_s_move");
      return;
    }
    s_s_move(params[0], params[1]);
    Serial.println("s_s_move zavoláno");
    return;
  }
  if (cmd.startsWith("s_s_soft_move(")) {
    int params[3];
    int start = cmd.indexOf('(') + 1;
    int end = cmd.indexOf(')');
    if (start < 1 || end < 0) {
      Serial.println("Chybný formát s_s_soft_move");
      return;
    }
    String paramStr = cmd.substring(start, end);
    if (!parseParams(paramStr, params, 3)) {
      Serial.println("Chyba v parametrech s_s_soft_move");
      return;
    }
    s_s_soft_move(params[0], params[1], params[2]);
    Serial.println("s_s_soft_move zavoláno");
    return;
  }
  Serial.println("Neznámý příkaz");
}

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(10); }
}

void loop() {
  // Pokud je aspoň jeden znak k dispozici, přečteme až po '\n'
  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    line.trim();               // odstraní CR/LF a mezery navíc
    if (line.length() > 0) {
      Serial.print("Dostal jsem řetězec: "); 
      Serial.println(line);
      processCommand(line);
    }
  }
}
/*
s_s_init(1, 0, 160)
s_s_move(1, 90)
s_s_soft_move(1, 150, 150)
*/
