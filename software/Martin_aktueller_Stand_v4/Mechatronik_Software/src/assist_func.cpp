#include "assist_func.hpp"

namespace Sin_Gen
{
  byte SinTab[256];

  void Sin_Tab()
  {
    for (size_t i = 0; i < 256; i++)
    {
      SinTab[i] = int(__builtin_sin(i * PI_n / 512) * 256) & 0xFF;
    }
  }

  int16_t sin(uint16_t w)
  {
    int16_t mag = (int16_t)w;
    int16_t sinwert;
    if (mag & 0x100)
    {
      if ((w & 0x1FF) == 0x100) ++w;
      mag = 512 - w;
    }
    sinwert = (*(const unsigned char *)(SinTab + (mag & 0xFF)));
    if (mag & 0x200)
    {
      sinwert = -sinwert;
    }
    return sinwert;
  }
}

namespace DISP_FKT
{
  void setText(Adafruit_SSD1306*display,uint8_t size,uint8_t x_pos, uint8_t y_pos,char*text)
  {
    display->clearDisplay();
    display->setTextSize(size);
    display->setTextColor(SSD1306_WHITE);
    display->setCursor(x_pos,y_pos);
    display->print(text);  // prints string and goes to next line
    display->display();
  }
}




namespace RGB_LED
{
  CRGB StatusLED[1];
  void begin()
  {
    
    FastLED.addLeds<WS2812, CRGB, GRB>(StatusLED, 1);
    StatusLED[0] = CRGB(255, 0, 0);
    FastLED.show();
  }


  void setColor(uint8_t red, uint8_t green, uint8_t blue)
  {
    StatusLED[0] = CRGB(red, green, blue);
    FastLED.show();
  }
}
