#ifndef SINUS_GE
#define SINUS_GE

#include <stdio.h>

namespace Sin_Gen
{
  constexpr float PI_n = __builtin_atan(1) * 4;
  typedef unsigned char byte;
  extern byte SinTab[256];
  
  void Sin_Tab();
  int16_t sin(uint16_t w);
}

#endif
