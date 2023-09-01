#ifndef _SUGAR_SHARED_OBJECT_H
#define _SUGAR_SHARED_OBJECT_H
#include <string>
#include <functional>
#include "mts/MTSLogic.h"
namespace sugar
{
    class ISharedObjectPublisher
    {
    public:
        virtual void *loan(size_t size) = 0;
        virtual void publish(void *obj) = 0;
    };
    class ISharedObjectSubscribler
    {
    public:
        virtual void GetSample(const std::function<void(void *)> &callback) = 0;
        virtual void SetReceiveHandler(const std::function<void()> &callback) = 0;
        virtual void UnsetReceiveHandler() = 0;
    };

    ISharedObjectPublisher *createSharedObjectPublish(ExecEnvironment *exec,const std::string &name);
    ISharedObjectSubscribler *createSharedObjectSubscrible(ExecEnvironment *exec,const std::string &name);
} // namespace sugar

#endif // _SUGAR_SHARED_OBJECT_H