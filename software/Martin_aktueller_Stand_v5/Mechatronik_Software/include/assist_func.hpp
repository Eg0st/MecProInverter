#ifndef ASSIST_FUNC_HPP
#define ASSIST_FUNC_HPP

#include <stdio.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "FastLED.h"

namespace Sin_Gen
{
  constexpr float PI_n = __builtin_atan(1) * 4;
  typedef unsigned char byte;
  extern byte SinTab[256];
  
  void Sin_Tab();
  int16_t sin(uint16_t w);
}

namespace DISP_FKT
{
  void setText(Adafruit_SSD1306*display,uint8_t size,uint8_t x_pos, uint8_t y_pos,char*text);
}


namespace RGB_LED
{
  void begin();
  void setColor(uint8_t red, uint8_t green, uint8_t blue);
}

#endif
