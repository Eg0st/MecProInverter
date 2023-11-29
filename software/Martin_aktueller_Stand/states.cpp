#include "states.hpp"


void Power_Up::enter(State_Machine* pOwner, Interface* interface)
{

}
void Power_Up::Execute(State_Machine* pOwner,Interface* interface)
{
  PROGMEM Sin_Gen::Sin_Tab(); //wurde auch zu dem ESP32 exportiert
  interface->display=Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
  interface->error_flag_pwr+=(!(interface->display).begin(SSD1306_SWITCHCAPVCC, 0x3C));
  // State Transition
  if(interface->error_flag_pwr>0)  { pOwner->Transition(failure); } else { pOwner->Transition(Check_Ok); }
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
