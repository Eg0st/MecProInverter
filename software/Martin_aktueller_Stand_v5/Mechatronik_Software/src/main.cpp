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
#define FREQUENZ 50

#include "sensor_func.hpp"
#define I2C_SDA 8
#define I2C_SLK 9

TwoWire*twowire=new TwoWire(BUS_NUM);


BLDCDriver6PWM*driver;
BLDCMotor*motor;

void setup()
{

  USBSerial.begin(115200);
  
  FOC::init(&driver,&motor);
  USBSerial.println("Test");
   //FOC::init(driver,motor);
  USBSerial.println("Test");

  pinMode(I_TRIP, OUTPUT);
  digitalWrite(I_TRIP, LOW);

  pinMode(RELAY_SHUNT_AC, OUTPUT);
  digitalWrite(RELAY_SHUNT_AC, HIGH);
  USBSerial.println(TLA2528::StartUp_TLA2528(twowire));
}

void loop()
{
  //USBUSBSerial.print(".");
  FOC::PWM_Generation(motor,2*PI*FREQUENZ);


  uint16_t voltage_15_bit = TLA2528::man_CHA_Read(twowire,V_15);
  float voltage_15_volt = (voltage_15_bit / 3029.39);
  USBSerial.print("Volatge 15 Volt: ");
  USBSerial.print(voltage_15_volt);
  USBSerial.print(" V\n");

  uint16_t voltage_3_3_bit = TLA2528::man_CHA_Read(twowire,V_3_3);
  float voltage_3_3_volt = (voltage_3_3_bit / 15276.46);
  USBSerial.print("Volatge 3.3 Volt: ");
  USBSerial.print(voltage_3_3_volt);
  USBSerial.print(" V\n");

  uint16_t voltage_TANK_bit = TLA2528::man_CHA_Read(twowire,V_TANK);
  float voltage_TANK_volt = (voltage_TANK_bit / 163.14);
  USBSerial.print("Volatge TANK Volt: ");
  USBSerial.print(voltage_TANK_volt);
  USBSerial.print(" V\n");

}

#endif

#ifdef ADC_TEST
#include "sensor_func.hpp"
#define I2C_SDA 8
#define I2C_SLK 9

TwoWire*twowire=new TwoWire(BUS_NUM);



void setup()
{
  USBSerial.begin(115200);
  twowire->begin(I2C_SDA,I2C_SLK);

    pinMode(LINW,OUTPUT);
    pinMode(HINW,OUTPUT);
    pinMode(LINV,OUTPUT);
    pinMode(HINV,OUTPUT);
    pinMode(LINU,OUTPUT);
    pinMode(HINU,OUTPUT);
    digitalWrite(LINW, LOW);
    digitalWrite(HINW, HIGH);
    digitalWrite(LINV, HIGH);
    digitalWrite(HINV, LOW);
    digitalWrite(LINU, LOW);
    digitalWrite(HINU, HIGH);

  pinMode(I_TRIP, OUTPUT);
  digitalWrite(I_TRIP, LOW);

  pinMode(RELAY_SHUNT_AC, OUTPUT);
  digitalWrite(RELAY_SHUNT_AC, HIGH);
  USBSerial.println(TLA2528::StartUp_TLA2528(twowire));
}

void loop()
{
  uint16_t voltage_15_bit = TLA2528::man_CHA_Read(twowire,V_15);
  float voltage_15_volt = (voltage_15_bit / 3029.39);
  USBSerial.print("Volatge 15 Volt: ");
  USBSerial.print(voltage_15_volt);
  USBSerial.print(" V\n");

  uint16_t voltage_3_3_bit = TLA2528::man_CHA_Read(twowire,V_3_3);
  float voltage_3_3_volt = (voltage_3_3_bit / 15276.46);
  USBSerial.print("Volatge 3.3 Volt: ");
  USBSerial.print(voltage_3_3_volt);
  USBSerial.print(" V\n");

  uint16_t voltage_TANK_bit = TLA2528::man_CHA_Read(twowire,V_TANK);
  float voltage_TANK_volt = (voltage_TANK_bit / 163.14);
  USBSerial.print("Volatge TANK Volt: ");
  USBSerial.print(voltage_TANK_volt);
  USBSerial.print(" V\n");

  delay(1000);


}
#endif

#ifdef TEMP_TEST
#include "sensor_func.hpp"
OneWire*onewire=new OneWire(ONE_WIRE_PIN);
DallasTemperature*temp=new DallasTemperature(onewire);

void setup()
{
  USBSerial.begin(115200);
  temp->begin();
}

void loop()
{
  float ergebnis=MAX31820::readTemperature(*temp);
  USBSerial.println(ergbnis);
}
#endif

#ifdef TIMING
#endif

#ifdef WHOLE_TEST
State_Machine fsm;

void setup()
{
  USBSerial.begin(115200);
}

void loop()
{
  /*  while Schleife der Routine  */
  fsm.Update();
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
  
  USBSerial.begin(115200);
}
*********************************************************************************************************/