//#include "main.hpp"
#include <Arduino.h>
#include <stdlib.h>
#include <stdio.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "conf.hpp"

// Objekt-Declaration that it is seeable, by the loop

#ifdef PWM_TEST

#include "foc_pwm.hpp"
#define FREQUENZ 10

BLDCDriver6PWM*driver;
BLDCMotor*motor;

void setup()
{

  Serial.begin(115200);
  FOC::init(&driver,&motor);
  Serial.println("Test");
   //FOC::init(driver,motor);
  Serial.println("Test");
}

void loop()
{
  //USBSerial.print(".");
  FOC::PWM_Generation(motor,2*PI*FREQUENZ);
}

#endif

#ifdef MEASURE_PRE_CHARGE
#include "state_machine.hpp"
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

#endif
#ifdef ADC_TEST
#include "sensor_func.hpp"
#define I2C_SDA 8
#define I2C_SLK 9

TwoWire*twowire=new TwoWire(BUS_NUM);
uint8_t ergebnis;
void setup()
{
  USBSerial.begin(115200);
  twowire->begin(I2C_SDA,I2C_SLK);
  ergebnis=TLA2528::StartUp_TLA2528(twowire);
}

void loop()
{
  USBSerial.println(ergebnis);
  TLA2528::man_CHA_Read(twowire,V_15);
}
#endif

#ifdef TEMP_TEST
#include "sensor_func.hpp"
OneWire*onewire=new OneWire(ONE_WIRE_PIN);
DallasTemperature*temp=new DallasTemperature(onewire);

void setup()
{
  Serial.begin(115200);
  temp->begin();
}

void loop()
{
  float ergebnis=MAX31820::readTemperature(*temp);
  Serial.println(ergbnis);
}
#endif

#ifdef TIMING
#include "foc_pwm.hpp"
void setup()
{
  Serial.begin(115200);
  // Set timer frequency to 1Mhz
  TIMING::initTimer(1000000);
  delay(3000);
  TIMING::startTimer();
  delay(5000);
  Serial.println(flag);
  TIMING::stopTimer();
  flag=false;
  delay(2000);
}

  

void loop()
{
  Serial.println(flag); 
}


#endif

#ifdef WHOLE_TEST
#include "state_machine.hpp"
State_Machine fsm;

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  /*  while Schleife der Routine  */
  fsm.Update();
  fsm.Transition(Check_Ok);
}

#endif
/*********************************************************************************************************
Plan B falls das in einer Klasse nicht funktioniert:

// aus Zeitgründen soll nur ein flag übergeben werden, aus Zeitgründen
volatile uint8_t flag;

// Definition of the Callback Function
// IRAM put it into RAM for faster Execution
void IRAM_ATTR timer_isr_callback(void*arg) {
  // Umcastung von den void arg, da nur void übergeben werden darf
  Interface* inte=static_cast<Interface*>(arg);
  inte->flag
  flag=true;
}

void setup()
{
  // Übergabe der Argumente für den Interrupt
  //  * callback: Name der ISR Funktion
  //  * arg: Übergabe der argumentde, in dem Fall dem Interface
  //  * name: Name der callback Funktion

  const esp_timer_create_args_t periodic_timer_args = {
    .callback = &timer_isr_callback,
    .arg=fsm.getInterface(),  //Aufruf einer static function
    .name = "periodic"
  };

  // Erstellung einer Instanz
  esp_timer_handle_t periodic_timer;

  // Erstellung des Timers
  esp_timer_create(&periodic_timer_args,&periodic_timer);

  // Setzen der Periode
  esp_timer_start_periodic(periodic_timer,1000000/TIMER_FREQUENCY_HZ);

  // Setzen des Stops
  //esp_timer_stop(periodic_timer);
  
  Serial.begin(115200);
}
*********************************************************************************************************/