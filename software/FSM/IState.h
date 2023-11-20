#ifndef ISTATE_H
#define ISTATE_H

// Interface für die einzelnen Light States für die Transition
#include <iostream>

template <class T>
class ISTate
{
public:
    virtual void enter(T* pOwner) = 0;
    virtual void Execute(T* pOwner) = 0;
    virtual void exit(T* pOwner) = 0;
    virtual ~ISTate() {}
};

template <class T,typename E>
struct Table_Entry
{
    ISTate<T>  *current_state_id;
    E transition_id;
    ISTate<T>  *next_state_id;
};

#endif // ISTATE_H
