#include "Projekt_Mechatronik.hpp"

// Objekt-Declaration that it is seeable, by the loop
State_Machine fsm;

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  /*  while Schleife der Routine  */
  fsm.Update();
}
