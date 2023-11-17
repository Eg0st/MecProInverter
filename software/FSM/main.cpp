#include <stdlib.h>
#include <stdio.h>
#include "state_machine.h"

// kleiner Test

int main()
{
    State_Machine* fsm=new State_Machine;
    fsm->Update();
    fsm->Update();
    fsm->Update();

    //StartUp_Routine
    // Klasse die nur mit dem eintrag external event, die transitions ändert und auch executed
}
