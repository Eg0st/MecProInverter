#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H
#include "TState_Machine.h"
#include "states.h"

enum Transitions {Check_Ok,failure,U_Ok,Reset,On_Switch,Off_Switch};

class State_Machine: public TState_Machine<State_Machine>
{
public:
    State_Machine();
    ~State_Machine();
    inline void Init_Table()
    {
        table[0]={Power_Up_a     ,Check_Ok  ,Pre_Charge_a};
        table[1]={Pre_Charge_a   ,U_Ok      ,Standby_a};
        table[2]={Standby_a      ,On_Switch ,Run_a};
        table[3]={Run_a          ,Off_Switch,Standby_a};
        table[4]={Safestate_a    ,Reset     ,Standby_a};
        table[5]={Power_Up_a     ,failure   ,Safestate_a};
        table[6]={Pre_Charge_a   ,failure   ,Safestate_a};
        table[7]={Standby_a      ,failure   ,Safestate_a};
        table[8]={Run_a          ,failure   ,Safestate_a};

    }
    void Transition(Transitions tran);
    void Update()
    {
        TState_Machine<State_Machine>::Update(this);
    }
private:
    ISTate<State_Machine>*Power_Up_a;
    ISTate<State_Machine>*Pre_Charge_a;
    ISTate<State_Machine>*Standby_a;
    ISTate<State_Machine>*Run_a;
    ISTate<State_Machine>*Safestate_a;

    Table_Entry<State_Machine,Transitions> table[9];
    // friend um aauf die protective und die private Variablen zuzugreifen
    friend class Power_Up;
    friend class Self_Test;
    friend class Pre_Charge;
    friend class Standby;
    friend class Run;
    friend class Safestate;
};

#endif

