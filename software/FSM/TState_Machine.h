#ifndef TSTATE_MACHINE_H
#define TSTATE_MACHINE_H

#include "IState.h"


template <class T>
class TState_Machine
{
    T*m_pOwner;
    ISTate<T> *currentState;
    bool m_firstRun=true;

    public:

    inline void Init(T*pOwner, ISTate<T>*initialState)
    {
        currentState=initialState;
        m_pOwner=pOwner;
    }
    inline void ChangeState(ISTate<T>*newState)
    {
        currentState->exit(m_pOwner);
        currentState=newState;
        currentState->enter(m_pOwner);
    }
    inline ISTate<T>* getState() const
    {
        return currentState;
    }
    inline void Update(T*pOwner)
    {
        getState()->Execute(pOwner);
    }
};

#endif // TSTATE_MACHINE_H
