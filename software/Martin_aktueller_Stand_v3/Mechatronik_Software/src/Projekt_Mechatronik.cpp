#include "Projekt_Mechatronik.hpp"

// Objekt-Declaration that it is seeable, by the loop
State_Machine fsm;

void setup()
{
  USBSerial.begin(115200);
}

void loop()
{
  USBSerial.print(".");
  /*  while Schleife der Routine  */
  fsm.Update();
}
