#ifndef STATES_H
#define STATES_H
#include "IState.hpp"
#include "conf.hpp"

class Power_Up: public ISTate<class State_Machine, struct Interface>
{
    void enter(State_Machine* pOwner, Interface* interface);
    void Execute(State_Machine* pOwner, Interface* interface);
    void exit(State_Machine* pOwner, Interface* interface);
};

class Self_Test: public ISTate<class State_Machine, struct Interface>
{
    void enter(State_Machine* pOwner, Interface* interface);
    void Execute(State_Machine* pOwner, Interface* interface);
    void exit(State_Machine* pOwner, Interface* interface);
};

class Pre_Charge: public ISTate<class State_Machine, struct Interface>
{
    void enter(State_Machine* pOwner, Interface* interface);
    void Execute(State_Machine* pOwner, Interface* interface);
    void exit(State_Machine* pOwner, Interface* interface);
};

class Standby: public ISTate<class State_Machine, struct Interface>
{
    void enter(State_Machine* pOwner, Interface* interface);
    void Execute(State_Machine* pOwner, Interface* interface);
    void exit(State_Machine* pOwner, Interface* interface);
};

class Run: public ISTate<class State_Machine, struct Interface>
{
    void enter(State_Machine* pOwner,Interface* interface);
    void Execute(State_Machine* pOwner,Interface* interface);
    void exit(State_Machine* pOwner,Interface* interface);
};

class Safestate: public ISTate<class State_Machine, struct Interface>
{
    void enter(State_Machine* pOwner,Interface* interface);
    void Execute(State_Machine* pOwner,Interface* interface);
    void exit(State_Machine* pOwner,Interface* interface);
};

#endif // STATES_H
