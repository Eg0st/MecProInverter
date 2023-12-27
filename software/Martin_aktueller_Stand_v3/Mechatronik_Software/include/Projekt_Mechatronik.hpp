#ifndef MAIN_H
#define MAIN_H

//wichtige include Dateien, die mehrmals gebraucht werden
#include <Arduino.h>
#include <stdlib.h>
#include <stdio.h>
#include <Wire.h>
#include "Adafruit_SSD1306.h"

//allgemeine Funktionen
#include "Sensor_Funktionen.hpp"
#include "FOC_A.hpp"
#include "Sinus_Generatur.hpp"

// State Machine als absolut letzes
#include "state_machine.hpp"

//namespaces
using namespace std;




#endif
