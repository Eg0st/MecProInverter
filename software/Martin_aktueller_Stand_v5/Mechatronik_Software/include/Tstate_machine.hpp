#ifndef TSTATE_MACHINE_HPP
#define TSTATE_MACHINE_HPP

#include "Istate.hpp"

/**************************************************************************************************************************************
Templates in dem Header:
* class T: benutzerdefinierte State Machine Klasse
* typename U: Interface zwischen den Klassen, eine Struktur, die Objekte halten kann um sie zwischen den States zu transportieren
**************************************************************************************************************************************/

/**************************************************************************************************************************************
* Template Klasse einer State Machine:
* gibt Methoden die in einer State Machine benötigt werden

* Attribute:
* m_pOwner: hält die eigene Klasseninstanz in Form eines this Zeigers (benötigt um Funktionen den State Methoden zu zuordnen)
* currentState: hält den aktuellen Status
* m_firstrun: Start_Flag

* Init(pOwner, initialState): übergibt die eigene Instanz und den InitialZustand
* ChangeState(newState,interface: neuer Zustand und ein Interface (hält Variablen/Objekte für Austausch zwischen Klassen)
*   Tauscht die Zustaende ruft die exit Methode des aktuellen Zustands auf => macht den neuen zu aktuellen Zustand 
        => führt enter Methode des neuen Zustand aus
* getState(): gibt altuellen Zustand zurück
* update(): führt von dem aktuellen zustand die Execute Methode (Hauptmethode des Zustands) aus
**************************************************************************************************************************************/

template <class T,typename U>
class TState_Machine
{
    T*m_pOwner;
    ISTate<T,U> *currentState;
    bool m_firstRun=true;

    public:
    inline void Init(T*pOwner, ISTate<T,U>*initialState,U*interface)
    {
        currentState=initialState;
        m_pOwner=pOwner;
        currentState->enter(pOwner,interface);
    }
    inline void ChangeState(ISTate<T,U>*newState,U*interface)
    {
        currentState->exit(m_pOwner,interface);
        currentState=newState;
        currentState->enter(m_pOwner,interface);
    }
    inline ISTate<T,U>* getState() const
    {
        return currentState;
    }
    inline void Update(T*pOwner,U*interface)
    {
        getState()->Execute(pOwner,interface);
    }
};

#endif // TSTATE_MACHINE_H
