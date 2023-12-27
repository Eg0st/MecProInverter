#ifndef ISTATE_H
#define ISTATE_H

/**************************************************************************************************************************************
Templates in dem Header:
* class T: benutzerdefinierte State Machine Klasse
* typename U: Interface zwischen den Klassen
* typename E: enum type der benutzerdefinierten Transitions
**************************************************************************************************************************************/

/**************************************************************************************************************************************
Interface Klasse (virtuelle Klasse):
* Implementierung einer Abstrakten Klasse (alle abgeleiteten Klassen müssen virtuelle Funktionen umsetzen)
* Interface für die einzelnen Light States für die Transition: soll die Polymorphie umsetzen
* dient der Umsetzung von der Polymorphie
**************************************************************************************************************************************/

template <class T, typename U>
class ISTate
{
public:
    virtual void enter(T* pOwner, U* interface) = 0;
    virtual void Execute(T* pOwner, U* interface) = 0;
    virtual void exit(T* pOwner, U* interface) = 0;
    virtual ~ISTate() {}
};

/**************************************************************************************************************************************
Struktur Table Entry:
* dient der Umsetzung der State Map
* in state_machine.hpp Erzeugung eines Feldes mit dem Datentypen
* current_state_id: Hält den aktuellen Zustand
* transition_id: transition, die notwendig ist um zum nächsten Zustand zu kommen
* next_state_id: Definition des nächsten Zustands, der von der jeweiligen tranistion erreicht wird
**************************************************************************************************************************************/

template <class T,typename U,typename E>
struct Transition_Table
{
    ISTate<T,U>  *current_state_id;
    E transition_id;
    ISTate<T,U>  *next_state_id;
};

#endif // ISTATE_H
