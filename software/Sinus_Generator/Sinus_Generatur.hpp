#include <stdio.h>

constexpr float PI_n = __builtin_atan(1) * 4;
typedef unsigned char byte;

class sinustab_t
{
  private:
    byte a[256];

  public:
    sinustab_t();

    int16_t sin(uint16_t w) const;
};
