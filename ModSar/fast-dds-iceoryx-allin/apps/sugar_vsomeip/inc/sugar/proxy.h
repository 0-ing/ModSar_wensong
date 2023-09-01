#ifndef _SUGAR_COM_PROXY_H
#define _SUGAR_COM_PROXY_H
#include "instance_identifier.h"
#include "sugar/com/common.h"
namespace sugar
{

    class BaiscProxy : public com::IProxy
    {
    public:
        virtual bool FindService() = 0;

        sugar::InstanceIdentifier instance_identifier;
    };

    BaiscProxy *CreateProxyWithProtocol(sugar::com::IProtocol *proto, const sugar::InstanceIdentifier &instance);

    template <typename T>
    T *FindProxy(const sugar::InstanceIdentifier &instance)
    {
        T *obj = new T();
        CreateProxyWithProtocol(obj, instance);
        return obj;
    }

} // namespace sugar

#endif // _SUGAR_COM_PROXY_H
