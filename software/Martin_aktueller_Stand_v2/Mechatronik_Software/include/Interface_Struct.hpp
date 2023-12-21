#ifndef INTERFACE_STRUCT_H
#define INTERFACE_STRUCT_H

#include "Projekt_Mechatronik.hpp"

//hier sollen alle Strukturen rein, die als Interface dienen, um Daten zw. den Klassen zu transportieren
struct Interface{
  // Error Flags
  uint8_t error_flag_per;
  uint8_t error_flag_pwr;

  // Datentypen Peripheriegeräte
  Adafruit_SSD1306 display;
  DallasTemperature temp;
  OneWire oneWire;
  TwoWire myWire;
  
  // Motortreiber
  BLDCMotor*motor;
  BLDCDriver6PWM*driver;
  //TwoWire myWire;
};

#endif
