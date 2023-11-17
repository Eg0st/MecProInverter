#include "state_machine.h"
#include <iostream>
State_Machine::State_Machine()
{

    Power_Up_a    =   new Power_Up();
    Pre_Charge_a  =   new Pre_Charge();
    Standby_a     =   new Standby();
    Run_a         =   new Run();
    Safestate_a   =   new Safestate();
    Init_Table();
    TState_Machine<State_Machine>::Init(this,Power_Up_a);
}

State_Machine::~State_Machine()
{
    delete Power_Up_a;
    delete Pre_Charge_a;
    delete Standby_a;
    delete Run_a;
    delete Safestate_a;
}

void State_Machine::Transition(Transitions tran)
{
    for(int i=0;i<9;i++)
    {
        if(table[i].current_state_id==getState() && table[i].transition_id==tran)
        {
            TState_Machine<State_Machine>::ChangeState(table[i].next_state_id);
            return;
        }
    }
    std::cout<<"Fehler"<<std::endl;
}
