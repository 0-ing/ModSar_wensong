#include "sugar/shared_object.h"

#include "iceoryx_dust/posix_wrapper/signal_watcher.hpp"
#include "iceoryx_posh/popo/untyped_publisher.hpp"
#include "iceoryx_posh/runtime/posh_runtime.hpp"

class SharedOjectPublisher : public sugar::ISharedObjectPublisher
{
public:
    SharedOjectPublisher(const char *name) : publisher({"name1", "name2", "name"})
    {
    }
    void *loan(size_t size)
    {
        void *p = NULL;
        publisher.loan(size)
            .and_then([&](auto &userPayload)
                      { p = userPayload; })
            .or_else([&](auto &error)
                     {
                         //! [print error]
                         std::cerr << "Unable to loan sample, error code: " << error << std::endl;
                         //! [print error]
                     });
        return p;
    }
    void publish(void *data)
    {
        publisher.publish(data);
    }

public:
    iox::popo::UntypedPublisher publisher;
};

namespace sugar
{
    ISharedObjectPublisher *createSharedObjectPublish(ExecEnvironment *exec, const std::string &name)
    {
        return exec->addComponent<SharedOjectPublisher>("publisher",
                                                        [=](char *mem) -> SharedOjectPublisher *
                                                        {
                                                            return new (mem) SharedOjectPublisher(name.c_str());
                                                        });
    }
    namespace skeleton
    {
        namespace iceoryx
        {
            void init()
            {
                //! [runtime initialization]
                constexpr char APP_NAME[] = "iox-cpp-publisher-untyped";
                iox::runtime::PoshRuntime::initRuntime(APP_NAME);
            }
        }
    }

} // namespace sugar
