# BME280 Readout
In diesem Projekt soll ein Minimalbeispiel, wie der BME280 ausgelesen werden kann, gezeigt werden. 

Dazu brauchst du folgendes:
## Hardware
Ein (ESP32)Board, dass I2C unterstützt (I2C erkennst du meist an den SCL und SDA Pins, dass sind die Datenleitung und Datenclock).
Einen BME280 Sensor mit Pins (es gibt den Sensor natürlich auch als SMD Bauteil, das macht das Basteln aber unnötigt kompliziert).
Ein USB-Kabel, mit dem Board und Computer verbunden werden können.
Jumperkabel und ein Breadboard zum Verbinden
![Hardwareübersicht](../../master/Pictures/Hardwareequipement.jpg?"BME280")
### Fertig zusammengebaut
Fertig zusammengebaut sieht das so aus:
Spannungsversorgung VIN vom Sensor an 3V3 ESP, GND Sensor an GND ESP, SCL Sensor an Pin 22(SCL ESP) und SDA Sensor an Pin 21(SDA ESP).
![Zusammengebaut](../../master/Pictures/Zusammengebaut.jpg?"BME280")
### Platine als Alternative
Für dieses (und ähnliche Projekte) gibt es auch fertige Platinen, die im README auf der Hauptseite vorgestellt werden.
Der Unterschied hierbei ist, dass die Kabel, die sonst auf das Breadboard gesteckt werden, durch elektrische Verbindungen auf dem Board ersetzt wurden.

## Software
Du brauchst die Arduino IDE und die Bibliotheken (die auch im "include" Teil des Programms stehen) Wire, Adafruit_BME280 und SPI. Wire und SPI sind (soweit ich weiß, installiert).
**Adafruit BME280 Library** ist der Name der BME Library. Unter Werkzeuge -> Bibliotheksverwalter kannst du Bibliotheken suchen, updaten und installieren.
