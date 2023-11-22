#include "main.hpp"




void setup() {
  

  // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
  // Object Creation
  Adafruit_SSD1306 display=Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
  State_Machine fsm();
  Serial.begin(115200);
  //Display_Anzeige(display);
}

void loop()
{
  
}
