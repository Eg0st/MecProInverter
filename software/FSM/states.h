#ifndef STATES_H
#define STATES_H
#include "IState.h"
#include "state_machine.h"

class Power_Up: public ISTate<class State_Machine>
{
    void enter(State_Machine* pOwner);
    void Execute(State_Machine* pOwner);
    void exit(State_Machine* pOwner);
};

class Self_Test: public ISTate<class State_Machine>
{
    void enter(State_Machine* pOwner);
    void Execute(State_Machine* pOwner);
    void exit(State_Machine* pOwner);
};

class Pre_Charge: public ISTate<class State_Machine>
{
    void enter(State_Machine* pOwner);
    void Execute(State_Machine* pOwner);
    void exit(State_Machine* pOwner);
};

class Standby: public ISTate<class State_Machine>
{
    void enter(State_Machine* pOwner);
    void Execute(State_Machine* pOwner);
    void exit(State_Machine* pOwner);
};

class Run: public ISTate<class State_Machine>
{
    void enter(State_Machine* pOwner);
    void Execute(State_Machine* pOwner);
    void exit(State_Machine* pOwner);
};

class Safestate: public ISTate<class State_Machine>
{
    void enter(State_Machine* pOwner);
    void Execute(State_Machine* pOwner);
    void exit(State_Machine* pOwner);
};

#endif // STATES_H
