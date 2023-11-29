#ifndef INTERFACE_STRUCT_H
#define INTERFACE_STRUCT_H

#include "Projekt_Mechatronik.hpp"

//hier sollen alle Strukturen rein, die als Interface dienen, um Daten zw. den Klassen zu transportieren
struct Interface{
  uint8_t error_flag_pwr;
  Adafruit_SSD1306 display;
};

#endif
