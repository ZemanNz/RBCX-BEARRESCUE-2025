# README pro projekt rbcx-upgrade

## 🚀 Účel projektu

Cílem projektu **rbcx-upgrade** je vylepšit funkčnost knihovny RBCX pomocí knihovny Robotka. Projekt přináší nové funkce a optimalizace, které zlepšují použitelnost a efektivitu knihovny.

### Klíčové vlastnosti:

- **Uvolnění paměti:** Optimalizace knihovny snížila využití paměti z přibližně 60 % na 14 %, což zvyšuje efektivitu.
- **Desetinné řízení rychlosti:** Přidána možnost nastavit rychlost s desetinnou hodnotou, např. 50.5 místo pouze celých čísel (50 nebo 51).
- **Integrace senzorů:** Nové funkce pro inicializaci a měření pomocí barevných a laserových senzorů. Podpora až dvou laserových senzorů pro přesnější měření.
- **Bezpečnost motorů:** Zaveden bezpečnostní mechanismus, který zabraňuje zaseknutí motoru při nedosažení cílové pozice. Nastaven timeout pro případ, že motor nepostupuje.

---

## 📝 Shrnutí

Projekt **rbcx-upgrade** zlepšuje knihovnu RBCX přidáním funkcí, jako je podpora barevných a laserových senzorů, optimalizace paměti a zavedení bezpečnostních mechanismů pro motory. Tyto upgrady zvyšují spolehlivost a efektivitu knihovny, zejména v robotických aplikacích.

---

## 📂 Struktura projektu

📁 **RBCX-Robot - version_for_github/**

- 📂 `.pio/`           – Výstup sestavení PlatformIO  
- 📂 `.vscode/`        – Nastavení VS Code  
- 📂 `include/`        – Vlastní knihovny (např. `colors.h`, `motorcommands.h`)  
- 📂 `src/`            – Hlavní kód (např. `main.cpp`)  
- 📂 `test/`           – Testovací kód  
- 📜 `csache.py`       – Skript pro optimalizaci sestavení  
- 📜 `partitions.csv`  – Konfigurace paměti ESP32  
- 📜 `platformio.ini`  – Konfigurační soubor PlatformIO (důležité: obsahuje `lib_deps` a nastavení paměti desky)  
- 📂 `lib/`            – Stažené knihovny  
- 📜 `README.md`       – Dokumentace  

---

## 🚀 Instalace a použití

1️⃣ **Nainstalujte VS Code a PlatformIO**  
   - Stáhněte a nainstalujte VS Code.  
   - Přidejte rozšíření PlatformIO a potřebné balíčky pro C++.  

2️⃣ **Stáhněte projekt**  
   - Navštivte GitHub, klikněte na "Code" → "Download ZIP".  
   - Rozbalte ZIP soubor a otevřete jej ve VS Code (PlatformIO → Open Folder).  

3️⃣ **Sestavení a nahrání**  
   - Otevřete terminál pomocí "Ctrl + Shift + P" a spusťte příkazy PlatformIO. Ujistěte se, že máte správně vybraný COM port (např. COM4).  
   - Alternativně použijte následující příkazy:  

   ```bash
   pio run                 # Kompilace
   pio run --target upload # Nahrání na desku
   pio run --target clean  # Vyčištění sestavení
   pio run --target info   # Zobrazení informací o projektu

## 🔧 Ovládání tlačítek a LED

**Tlačítka na desce:**  
- Button1, Button2, Button3, Button4 (Směry: Nahoru, Vlevo, Vpravo, Dolů)
- On, Off, Reset

Tato tlačítka lze také připojit externě k určeným pinům na desce.

**LED indikátory:**  
Na desce jsou čtyři LED diody: Červená, Zelená, Modrá, Žlutá.  
Lze je ovládat pomocí:

```cpp
RK_LED_Blue(true);   // Zapnutí modré LED
RK_LED_Blue(false);  // Vypnutí modré LED
```

## 🔌 Připojení periférií

- 4x konektory pro motory s enkodéry.
- 4x piny pro ultrazvukové senzory (označené U1–U4).
- 4x servo konektory.
- Tlačítka lze připojit na IN1 a IN2 (analogové hodnoty, ale mohou se použít i jako digitální): Piny 36, 39; IN3 a IN4: Piny 34, 35.
- GPIO piny (vzdálenější od středu): Pin 27; blíže ke středu: Pin 14. Pro další piny doporučujeme konzultaci s dokumentací.

## 🔌 Zapojení a konfigurace pinů

### Zapojení I2C:
Sběrnice I2C umožňuje připojení více zařízení na stejné vodiče. V tomto projektu jsou pro komunikaci I2C použity následující piny:

- **SDA (datový vodič)** → GPIO21
- **SCL (hodinový vodič)** → GPIO22

Ujistěte se, že připojená I2C zařízení mají správnou adresu a odpovídající napájecí napětí (3.3V nebo 5V podle specifikace).

### Zapojení digitálních pinů:
Deska poskytuje několik digitálních pinů, které lze využít pro různá zařízení (tlačítka, senzory atd.). Klíčové digitální piny:

- **GPIO14** → Lze použít pro tlačítka nebo jiná digitální zařízení.
- **GPIO27** → Další možnost pro připojení digitálních zařízení.

Dbejte na to, aby na každý pin nebyl připojen nepřiměřený počet zařízení a bylo dodrženo napájecí napětí.

## ⚙️ Příkazy pro GitHub

Zde je několik užitečných příkazů pro správu repozitáře GitHub:

```bash
git init                 # Inicializace nového git repozitáře
git clone <url>          # Klonování existujícího repozitáře
git add .                # Přidání změn ke commitnutí
git commit -m "zpráva"  # Commit změn
git push                 # Odeslání na vzdálený repozitář
git pull                 # Stažení posledních změn z repozitáře
```

## ⚙️ Konfigurace (`rk-config`)

`rk-config` je součást knihovny Robotka a najdeš ji v souboru `robotka.h`. Umožňuje nakonfigurovat různé parametry hardware, například nastavení pinů pro motory, polaritu motorů, konfiguraci serv a podobně.

### Ukázková konfigurace:

```cpp
rk_config.motor_pins = {GPIO12, GPIO13}; // Přiřazení pinů motorům
rk_config.servo_pins = {GPIO14, GPIO15}; // Přiřazení pinů servům
rk_config.motor_polarity = true;        // Nastavení polarity motorů
```

## 🧪 Testování

Ve složce `test/` najdeš ukázkové testovací skripty pro motory, senzory a další periférie. Můžeš si také přidat vlastní testy podle potřeby.

## 🔧 Konfigurace PlatformIO (`platformio.ini`)

Soubor `platformio.ini` definuje prostředí a nastavení projektu. Obsahuje například:

- Verzi platformy (`platform = espressif32`)
- Definici desky (`board = esp32dev`)
- Další volby jako `monitor_speed` a `upload_port`
- Knihovny uvedené pod klíčem `lib_deps`

```ini
; PlatformIO Project Configuration File
;
;   Build options: build flags, source filter
;   Upload options: custom upload port, speed and extra flags
;   Library options: dependencies, extra library storages
;   Advanced options: extra scripting
;
; Please visit documentation for the other options and examples
; https://docs.platformio.org/page/projectconf.html

[env:esp32dev]
platform = espressif32@~1.12.4
board = esp32dev
framework = arduino
monitor_speed = 115200
upload_speed = 921600
board_build.partitions = partitions.csv
build_flags = -std=c++14 -DUSE_PRECOMPILED_LIBRARIES -DCCACHE -DUSE_VL53L0X
build_unflags = -std=gnu++11
monitor_filters = esp32_exception_decoder
extra_scripts = pre:ccache.py
lib_deps = 
        https://github.com/adafruit/Adafruit_TCS34725/archive/refs/tags/1.3.6.tar.gz
        SPI
        adafruit/Adafruit_VL53L0X @ ^1.2.4

```

## 👨‍💻 Další kroky

1. Přizpůsob si projekt podle vlastních potřeb.
2. Přidej další senzory nebo periférie.
3. Důkladně otestuj celý systém, zda správně fungují motory, senzory i serva.

