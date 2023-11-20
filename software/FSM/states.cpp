#include "states.h"
#include "delay.h"

using namespace DELAY;
using namespace std;
void Power_Up::enter(State_Machine* pOwner)
{

}
void Power_Up::Execute(State_Machine* pOwner)
{
    pOwner->Transition(Check_Ok);
    cout<<"Check"<<endl;
}
void Power_Up::exit(State_Machine* pOwner)
{

}


void Pre_Charge::enter(State_Machine* pOwner)
{

}
void Pre_Charge::Execute(State_Machine* pOwner)
{
    cout<<"Chec"<<endl;
    pOwner->Transition(Check_Ok);

}
void Pre_Charge::exit(State_Machine* pOwner)
{

}


void Standby::enter(State_Machine* pOwner)
{

}
void Standby::Execute(State_Machine* pOwner)
{

}
void Standby::exit(State_Machine* pOwner)
{

}


void Run::enter(State_Machine* pOwner)
{

}
void Run::Execute(State_Machine* pOwner)
{

}
void Run::exit(State_Machine* pOwner)
{

}


void Safestate::enter(State_Machine* pOwner)
{

}
void Safestate::Execute(State_Machine* pOwner)
{

}
void Safestate::exit(State_Machine* pOwner)
{

}
