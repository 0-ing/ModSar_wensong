#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#include "sugar/sugar.h"

struct SharedObject  
{
public:
    int a = 0;
    int b = 0;
};

class IHelloworldProto : public sugar::com::IProtocol
{
public:
    declare_event(sugar::com::Event<SharedObject*>, wantToSayEvent);
};

#endif // _PROTOCOL_H