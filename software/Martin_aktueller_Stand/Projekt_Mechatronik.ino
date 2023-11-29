#include "Projekt_Mechatronik.hpp"




// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

float readTemperature() {
  // löst die Temperaturabfrage für alle Sensoren aus
  sensors.requestTemperatures();
  
  // Get temperature in Celsius for the first device
  float temperatureC = sensors.getTempCByIndex(0);
  
  // Check for errors in reading temperature
  if (temperatureC == -127.00) {
    Serial.println("Error reading temperature");
    return -1;
  } else {
    // Return temperature
    return temperatureC;
  }
}


void setup() {
  

  // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
  // Object Creation
  Adafruit_SSD1306 display=Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
  State_Machine fsm();
  Serial.begin(115200);
  //Display_Anzeige(display);

    // Start the Dallas Temperature sensor
  sensors.begin();
}

void loop()
{
  // temperatur scheiße
   // Read temperature from MAX31820MCR
  float temperature = readTemperature();
  
  // Check if temperature was read successfully
  if (temperature != -1) {
    // Print temperature to serial monitor
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" degrees C");
  }
  
  // Wait 1 second before requesting temperature again
  delay(1000);
}
