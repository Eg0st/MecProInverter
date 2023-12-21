#ifndef MAIN_H
#define MAIN_H

//include Dateien
#include <Arduino.h>
#include <stdlib.h>
#include <stdio.h>
#include <Wire.h>
#include "Sensor_Funktionen.hpp"
#include "Adafruit_SSD1306.h"
#include "state_machine.hpp"
#include "Sinus_Generatur.hpp"
#include <SimpleFOC.h>


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

//Definitionen der Ein-/Ausgaenge
#define PIN_IPH1 A15 //ADC2_5 == A15
#define PIN_IPH2 A16 //ADC2_6 == A16 
#define PIN_IPH3 A17 //ADC2_7 == A17

#define HALL_PH1 19
#define HALL_PH2 18
#define HALL_PH3 5

#define PIN_PH1_H 18 // 23
#define PIN_PH2_H 17 // 1
#define PIN_PH3_H 32
#define PIN_PH1_L 33
#define PIN_PH2_L 25
#define PIN_PH3_L 26




#endif
