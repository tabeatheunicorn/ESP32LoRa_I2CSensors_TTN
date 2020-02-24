# ESP32LoRa_I2CSensors_TTN
Repository where the firmware usable for the Heltec LoRa 32 V2 Board goes

## Getting started
This is like a diary of things accomplished during the project.
Corresponding hardware layout can be found here.

### Choosing an IDE
Because of no other reason than that it is easy to start with, the very first part of the project is done in the Arduino IDE (I got Versioin 1.8.12, but that shouldn't matter that much).

### Choosing a suitable library
Because the board was already selected (Heltec V2 LoRa Board with Wifi, just because it was there), a suitable library that supports LoRa for this particular board and can be used in Arduino IDE has to be choosen. I read [this overview](https://www.thethingsnetwork.org/forum/t/overview-of-lorawan-libraries-howto/24692) and decided for [the arduino lmic library](https://github.com/matthijskooijman/arduino-lmic).
`#include "lmic.h"` includes this library.
`#include "hal/hal.h"`comes in quite handy. As you can see in the lmic/src repository, this header file allows to easily map the hardware pins used correctly.

#### Other useful libraries
The SPI.h Library is explained [here](https://www.arduino.cc/en/Reference/SPI). 

For I2C/TWI, [Wire.h](https://www.arduino.cc/en/reference/wire) is extremly useful.

## First steps
The very first goal is to send data to TTN. Therefore, you need your TTN account and your own application where you can register devices. Because you want to accomplish a LoRa project, I assume that you have a gateway in reach. If you are not sure about this one, find out beforehand!

### TTN setup
If you have your own application, register a device! Every device has its own Device ID and an App ID that is needed later to make sure your data is send to the right adress. 

### Hardware setup
We use the LoRa Module of the Hardware only, so no need to wire any sensors etc. Just make sure that the antenna is plugged in before powercycling (I learned that you might damage the board otherwise). 

For flashing (e.g. transferring the compiled programm to the board, you need a USB-cable that connects your computer with the board).

### Firmware
The **only** thing leftover now is the firmware we need to send LoRa packages to the nearest Gateway which then sends the package to the TTN server.
You find the code in the folder: ***FirstSteps/SendingData*** I tried to document it as good as possible. If you still encouter any questions, just send me an email.
