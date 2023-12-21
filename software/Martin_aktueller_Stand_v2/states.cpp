#include "states.hpp"


void Power_Up::enter(State_Machine* pOwner, Interface* interface)
{

}
void Power_Up::Execute(State_Machine* pOwner,Interface* interface)
{
  // Initialisierungen der Sinus_Tabelle
  PROGMEM Sin_Gen::Sin_Tab(); //wurde auch zu dem ESP32 exportiert

  //Initialisierungen der BUS-Systeme
  interface->oneWire=OneWire(ONE_WIRE_BUS);
  interface->myWire=TwoWire(0);

  //Check of the I2C Bus (nicht möglich für den OneWire Bus)
  interface->error_flag_per += (interface->myWire.begin())  ? 0 : 1;
  
  // Intitialisierungen_Sensorik
  interface->display=Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &interface->myWire, -1); // Der -> hat eine höhere Prio als &
  interface->temp=DallasTemperature(&(interface->oneWire));

  //initialisierungen der Sensoren (begin methode ohne Rueckgabewert
  interface->temp.begin();


  //Initialisierungen oder erste Kommunikation oder beides
  interface->error_flag_per+= ((interface->temp).getDeviceCount()>0) ? 0 : 1;
  interface->error_flag_per+= (interface->display).begin(SSD1306_SWITCHCAPVCC, 0x3C,true,false) ? 0 : 1;  // Mit dem letzten false teilt man dem Konstruktor mit, dass ein begin schon initialisiert wurde, bei dem I2C Bus
  
  
  // State Transition
  if(interface->error_flag_per>0)  { pOwner->Transition(failure); } else { pOwner->Transition(Check_Ok); }
}
void Power_Up::exit(State_Machine* pOwner, Interface* interface)
{

}


void Pre_Charge::enter(State_Machine* pOwner, Interface* interface)
{

}
void Pre_Charge::Execute(State_Machine* pOwner, Interface* interface)
{
  // hier kommt alles rein, was mit dem Pre Charge zu tun hat, verkettete Liste,
  // die das letzte Element mit dem ersten Wert vergleicht, Timer gesteuert
}
void Pre_Charge::exit(State_Machine* pOwner, Interface* interface)
{

}


void Standby::enter(State_Machine* pOwner, Interface* interface)
{

}
void Standby::Execute(State_Machine* pOwner, Interface* interface)
{

}
void Standby::exit(State_Machine* pOwner, Interface* interface)
{

}


void Run::enter(State_Machine* pOwner, Interface* interface)
{

}
void Run::Execute(State_Machine* pOwner, Interface* interface)
{

}
void Run::exit(State_Machine* pOwner, Interface* interface)
{

}


void Safestate::enter(State_Machine* pOwner, Interface* interface)
{

}
void Safestate::Execute(State_Machine* pOwner, Interface* interface)
{

}
void Safestate::exit(State_Machine* pOwner, Interface* interface)
{

}
