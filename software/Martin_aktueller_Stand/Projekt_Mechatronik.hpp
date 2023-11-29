#ifndef MAIN_H
#define MAIN_H

//include Dateien
#include <Arduino.h>
#include <stdlib.h>
#include <stdio.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "Adafruit_SSD1306.h"
#include "state_machine.hpp"
#include "Sinus_Generatur.hpp"

//namespaces
using namespace std;

// Definitionen für den Display
#define SSD1306_I2C_ADDR 0x3D
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define WIRE_MAX 32

// Definitionen der Konstanten für den Temperatursensor
// Data wire is connected to GPIO 4
#define ONE_WIRE_BUS 4



#endif
