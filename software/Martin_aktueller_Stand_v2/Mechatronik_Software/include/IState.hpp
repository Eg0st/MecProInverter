#ifndef ISTATE_H
#define ISTATE_H

// Interface für die einzelnen Light States für die Transition

template <class T, typename U>
class ISTate
{
public:
    virtual void enter(T* pOwner, U* interface) = 0;
    virtual void Execute(T* pOwner, U* interface) = 0;
    virtual void exit(T* pOwner, U* interface) = 0;
    virtual ~ISTate() {}
};

template <class T,typename U,typename E>
struct Table_Entry
{
    ISTate<T,U>  *current_state_id;
    E transition_id;
    ISTate<T,U>  *next_state_id;
};

#endif // ISTATE_H
