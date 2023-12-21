#ifndef TSTATE_MACHINE_H
#define TSTATE_MACHINE_H

#include "IState.hpp"


template <class T,typename U,typename E>
class TState_Machine
{
    T*m_pOwner;
    ISTate<T,U> *currentState;
    bool m_firstRun=true;

    public:
    inline void Init(T*pOwner, ISTate<T,U>*initialState)
    {
        currentState=initialState;
        m_pOwner=pOwner;
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
