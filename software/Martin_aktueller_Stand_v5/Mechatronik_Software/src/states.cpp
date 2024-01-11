#include "states.hpp"

/**************************************************************************************************************************************
* POWER_UP
Anmerkungen:
PROGMEM auch zu ESP32 exportiert
temp.begin() besitzt keinen Rückgabewert
**************************************************************************************************************************************/
void Power_Up::enter(State_Machine* pOwner, Interface* interface)
{
  // Initialisierungen der Sinus_Tabelle
  PROGMEM Sin_Gen::Sin_Tab();

  //Initialisierung der Switch_Assembly
  pinMode(SW1,INPUT);
  pinMode(SW2,INPUT);
  pinMode(SW3,INPUT);

  //Initialisierungen der BUS-Systeme
  interface->oneWire=new OneWire(ONE_WIRE_PIN);
  interface->twoWire=new TwoWire(BUS_NUM);

  // Intitialisierungen_Sensorik
  interface->temp=new DallasTemperature(interface->oneWire);
  interface->temp->begin();

}

void Power_Up::Execute(State_Machine* pOwner,Interface* interface)
{
  // Referenzen, zur Vereinfachung
  auto &twoWire=interface->twoWire;
  auto &oneWire=interface->oneWire;
  auto &display=interface->display;
  auto &temp=interface->temp;
  // Check of the I2C Bus (nicht möglich für den OneWire Bus)
  interface->error_flag_per += (twoWire->begin(I2C_SDA,I2C_SLK))  ? 0 : 1;

  // Definitionen aller I2C-Bus Definitionen erst danach, da begin Funktionen erst danach aufgerufen
  interface->display=new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, interface->twoWire, -1); // Der -> hat eine höhere Prio als &

  //Check bzw. erste Kommunikation
  interface->error_flag_per+= (temp->getDeviceCount()>0) ? 0 : 1;
  interface->error_flag_per+= (display->begin(SSD1306_SWITCHCAPVCC, 0x3C,true,false)) ? 0 : 1;  // Mit dem letzten false teilt man dem Konstruktor mit, dass ein begin schon initialisiert wurde, bei dem I2C Bus
  
  // State Transition
  if(interface->error_flag_per>0)  { pOwner->Transition(failure); } else { pOwner->Transition(Check_Ok); }
}
void Power_Up::exit(State_Machine* pOwner, Interface* interface)
{

}

/**************************************************************************************************************************************
* PRE_CHARGE
* Anmerkungen: pinMode fürs Relay hier definiert,
* sollte aber pasen da loop auch nur einmal aufgerufen und anschließend verlassen wird
* static last timestamp: falls man nochmal in die Funktion reingeht
**************************************************************************************************************************************/
void Pre_Charge::enter(State_Machine* pOwner, Interface* interface)
{
  //pinMode/digitalWrite
  pinMode(RELAY_SHUNT_AC,OUTPUT);
  digitalWrite(RELAY_SHUNT_AC,LOW);
  
}

void Pre_Charge::Execute(State_Machine* pOwner, Interface* interface)
{  
  //Logik
  uint8_t Spannung_alt;
  uint8_t Spannung;
  static unsigned long last_timestamp;
  while(Spannung_alt>=Spannung)
  {
    Spannung=Spannung_alt;
    if ((millis()-last_timestamp)>=5000)
    {
      last_timestamp=millis();
      pOwner->Transition(failure);
      return;
    }
    Spannung=TLA2528::man_CHA_Read(interface->twoWire,V_TANK);
  }
  last_timestamp=millis();
  digitalWrite(RELAY_SHUNT_AC,HIGH);
  pOwner->Transition(U_Ok);
}

void Pre_Charge::exit(State_Machine* pOwner, Interface* interface)
{

}

/**************************************************************************************************************************************
* STANDBY
**************************************************************************************************************************************/
void Standby::enter(State_Machine* pOwner, Interface* interface)
{
  interface->timing=new Timing();
  interface->timing->start(VELOCITY_LIMIT);
}
void Standby::Execute(State_Machine* pOwner, Interface* interface)
{  
  //Entprellsoftware
  if(digitalRead(SW1)) pOwner->Transition(On_Switch);
}
void Standby::exit(State_Machine* pOwner, Interface* interface)
{

}

/**************************************************************************************************************************************
* RUN
**************************************************************************************************************************************/
void Run::enter(State_Machine* pOwner, Interface* interface)
{
  //FOC::init(interface->driver,interface->motor);
  analogReadResolution(ADC_RESOLUTION);
}
void Run::Execute(State_Machine* pOwner, Interface* interface)
{
  if(!digitalRead(SW1))
  {
    float new_target_value=POTI_FKT::Read_Out_Frequency(POT1,ADC_RESOLUTION,VELOCITY_LIMIT);
    FOC::PWM_Generation(interface->motor,new_target_value);

  }
  else
  {
    pOwner->Transition(Off_Switch);
  }
}
void Run::exit(State_Machine* pOwner, Interface* interface)
{

}

/**************************************************************************************************************************************
* SAFESTATE
**************************************************************************************************************************************/
void Safestate::enter(State_Machine* pOwner, Interface* interface)
{

}
void Safestate::Execute(State_Machine* pOwner, Interface* interface)
{
  //hier eventueller Check das alles Ok und manuelle Freigabe für den Controller
}
void Safestate::exit(State_Machine* pOwner, Interface* interface)
{

}
