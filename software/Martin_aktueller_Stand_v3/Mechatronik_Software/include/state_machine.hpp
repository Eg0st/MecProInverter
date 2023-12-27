#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "Projekt_Mechatronik.hpp"
#include "TState_Machine.hpp"
#include "states.hpp"
#include "Interface_Struct.hpp"

#define NUM_OF_STATES 9

enum Transitions {Check_Ok,failure,U_Ok,Reset,On_Switch,Off_Switch};

/**************************************************************************************************************************************
benuterdefinierte Klasse State_Machine:
* erzeugt State Machine mit TState_Machine als Oberklasse
* Übergabe aller Templates: State_Machine, Interface, Transitions

Attribute der Klasse:
* Table_Entry<State_Machine,Interface,Transitions> table[NUM_OF_STATES]: Feld für die State tTransitions => Datentyp Table_Entry
* Interface* interface: Hält die Interface Struktur
* Nachfolgende Attrbibute halten die States
    ISTate<State_Machine,Interface>*Power_Up_a:
    ISTate<State_Machine,Interface>*Pre_Charge_a;
    ISTate<State_Machine,Interface>*Standby_a;
    ISTate<State_Machine,Interface>*Run_a;
    ISTate<State_Machine,Interface>*Safestate_a;

Methoden in der Klasse:
* State_Machine():
    * Initialisiert die, Attribute, die die States halten und erzuegt ein neues Objekt
    * ruft die init_Table() auf
    * Lädt den ersten Zustand PowerUp und führt die enter Methode aus
* ~State_Machine: zerstört die in State_Machine() erzeugten Objekte
* Init_Table(): Weißt die Transitions den Table zu, in dem Fall 6 Zustände
* Transition(Transition tran): besitzt aktuell noch keine Fehlermeldung kann aber noch programmiert werden
* Update(): führt den Hauptteil des jeweiligen Zustandes aus
 
Anmerkung: Klasse besitzt keinen Copy-Konstruktor bzw. Zuweisungsoperator => bitte nur eine Instanz erstellen

**************************************************************************************************************************************/

class State_Machine: public TState_Machine<State_Machine,Interface>
{
public:
    State_Machine();
    ~State_Machine();
    void Transition(Transitions tran);
    Interface getInterface() const { return *interface;  }
    void Update() { TState_Machine<State_Machine,Interface>::Update(this,interface); }

private:
    // Attribute:
    Transition_Table<State_Machine,Interface,Transitions> table[NUM_OF_STATES];
    Interface* interface;
    ISTate<State_Machine,Interface>*Power_Up_a;
    ISTate<State_Machine,Interface>*Pre_Charge_a;
    ISTate<State_Machine,Interface>*Standby_a;
    ISTate<State_Machine,Interface>*Run_a;
    ISTate<State_Machine,Interface>*Safestate_a;

    //private Methode, da keiner die States sehen oder ändern muss
    inline void Init_Table()
    {
        table[0]={Power_Up_a     ,Check_Ok      ,Pre_Charge_a   };
        table[1]={Pre_Charge_a   ,U_Ok          ,Standby_a      };
        table[2]={Standby_a      ,On_Switch     ,Run_a          };
        table[3]={Run_a          ,Off_Switch    ,Standby_a      };
        table[4]={Safestate_a    ,Reset         ,Standby_a      };
        table[5]={Power_Up_a     ,failure       ,Safestate_a    };
        table[6]={Pre_Charge_a   ,failure       ,Safestate_a    };
        table[7]={Standby_a      ,failure       ,Safestate_a    };
        table[8]={Run_a          ,failure       ,Safestate_a    };
    }

    // Friend Deklarationen, um auf Attribute (interface und pOwner) zugreifen zu können
    friend class Power_Up;
    friend class Self_Test;
    friend class Pre_Charge;
    friend class Standby;
    friend class Run;
    friend class Safestate;
};

#endif
