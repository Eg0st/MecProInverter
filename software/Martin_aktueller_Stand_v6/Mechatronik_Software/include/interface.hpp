#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "main.hpp"

/**************************************************************************************************************************************
Interface Struct:
* hält alle Zeiger von Objekten (wie TwoWire, OneWire)
* dient dem Transport von Daten zw. den Klassen oder der main

Anmerkungen:
* Die die Klassen für die Peripherie Geräte halten, sind alles Pointer, da sie relativ langlebig über das gesamte Projekt sind
  Zudem, wird bei der Deklaration eines Zeigers, nicht der Konstruktor default mäßig aufgerufen
**************************************************************************************************************************************/

struct Interface{
  // Error Flags
  uint8_t error_flag_per;
  uint8_t error_flag_pwr;
  
  
  // Datentypen Peripheriegeräte
  Adafruit_SSD1306*display;
  DallasTemperature*temp;
  OneWire*oneWire;
  TwoWire*twoWire;

  // Datentypen für die PWM Erzeugung
  BLDCDriver6PWM*driver;
  BLDCMotor*motor;
};

#endif
