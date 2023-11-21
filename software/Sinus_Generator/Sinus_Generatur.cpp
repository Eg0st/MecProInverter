#include "Sinus_Generatur.hpp"

sinustab_t::sinustab_t()
{
  for (size_t i = 0; i < 256; i++)
    a[i] = int(__builtin_sin(i * PI_n / 512) * 256) & 0xFF;
}

int16_t sinustab_t::sin(uint16_t w) const
{
  int16_t mag = (int16_t)w;
  int16_t sinwert;
  if (mag & 0x100)
  {
    if ((w & 0x1FF) == 0x100) ++w;
    mag = 512 - w;
  }
  sinwert = (*(const unsigned char *)(a + (mag & 0xFF)));
  if (mag & 0x200)
  {
    sinwert = -sinwert;
  }
  return sinwert;
}
