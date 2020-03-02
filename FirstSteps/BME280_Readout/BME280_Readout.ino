/*
 * Program by Tabea Röthemeyer (@tabeatheunicorn)
 * Dieses Programm gibt die vom BME280 Sensor gemessenen Werte aus (alle 10 Sekunden, wenn der Delay-Wert nicht angepasst wurde)
 * Dazu Werkzeuge ->Serieller Monitor öffnen und Programm auf das Board laden.
 */
#include <Wire.h>
#include <Adafruit_BME280.h>
#include <SPI.h> //Serial Peripheral Interface


//Using I2C as Protocol. has to be global as variable is used in setup and loop
Adafruit_BME280 bme; //I2C as no SPI pins are defined.

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  if (!bme.begin()){
    Serial.println("Could not find BME Sensor, check wiring.");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  float temperature = bme.readTemperature(); //float, in centigrade
  int pressure = bme.readPressure(); //32bit int in pascal
  int rel_humidity = bme.readHumidity(); //percentage relative humidity
  Serial.print(temperature);
  Serial.println(" °C"); //println ends line, print doesn't
  Serial.print(pressure);
  Serial.println("Ps");
  Serial.print(rel_humidity);
  Serial.println("% Humidity");
  delay(10000);//dealy in milliseconds

}
