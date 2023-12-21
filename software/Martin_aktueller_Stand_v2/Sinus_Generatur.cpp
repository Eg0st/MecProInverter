#include "Sinus_Generatur.hpp"

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
