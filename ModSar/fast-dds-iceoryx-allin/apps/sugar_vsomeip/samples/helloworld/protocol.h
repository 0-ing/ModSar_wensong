#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#include "sugar/sugar.h"

class RetObject : public CmdObject
{
public:
    std::string hello;
    int v = 0;
    CMD_SERIALIZE()
    {
        BIND_MSG(hello);
        BIND_MSG(v);
    }
};

class IHelloworldProto : public sugar::com::IProtocol
{
public:
    declare_method(sugar::com::Function<int(int)>, testMethod);
    declare_method(sugar::com::Function<RetObject(int)>, testMethodRetObj);

    declare_field(sugar::com::Field<std::string>, testField);
    declare_event(sugar::com::Event<int>, wantToSayEvent);
};

#endif // _PROTOCOL_H
