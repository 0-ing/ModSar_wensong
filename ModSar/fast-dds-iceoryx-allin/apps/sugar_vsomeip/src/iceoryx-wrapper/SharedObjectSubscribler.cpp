#include "iceoryx_dust/posix_wrapper/signal_watcher.hpp"
#include "iceoryx_posh/popo/untyped_subscriber.hpp"
#include "iceoryx_posh/runtime/posh_runtime.hpp"
#include "iceoryx_posh/popo/listener.hpp"
#include "sugar/com/common.h"
#include "sugar/shared_object.h"
class SharedObjectSubscribler : public sugar::ISharedObjectSubscribler
{
public:
  SharedObjectSubscribler(const char *name) : subscriber({"name1", "name2", "name"})
  {
    m_listener
        .attachEvent(subscriber,
                     iox::popo::SubscriberEvent::DATA_RECEIVED,
                     iox::popo::createNotificationCallback(onSampleReceivedCallback, *this))
        .or_else([](auto)
                 {
                std::cerr << "unable to attach subscriberRight" << std::endl;
                std::exit(EXIT_FAILURE); });
  }
  void GetSample(const std::function<void(void *)> &callback)
  {
    subscriber
        .take()
        //! [chunk happy path]
        .and_then([&](const void *userPayload)
                  {
                    //! [chunk received]
                    //  auto object = static_cast<const RadarObject *>(userPayload);
                    //  std::cout << APP_NAME << " got value: " << object->x << std::endl;
                    //! [chunk received]
                        callback((void*)userPayload);
                          //! [release]
                          // note that we explicitly have to release the sample
                          // and afterwards the pointer access is undefined behavior
                          subscriber.release(userPayload);
                        //! [release]
                  })
        //! [chunk happy path]
        .or_else([](auto &result)
                 {
                if (result != iox::popo::ChunkReceiveResult::NO_CHUNK_AVAILABLE)
                {
                    std::cout << "Error receiving chunk." << std::endl;
                } });
  }

  static void onSampleReceivedCallback(iox::popo::UntypedSubscriber *subscriber, SharedObjectSubscribler *self)
  {
    if (self->hasCallback)
    {
      self->ReceiveHandlerCallback();
    }
  }
  void SetReceiveHandler(const std::function<void()> &callback)
  {
    ReceiveHandlerCallback = callback;
    hasCallback = true;
  }
  void UnsetReceiveHandler()
  {
    hasCallback = false;
  }

  iox::popo::UntypedSubscriber subscriber;
  iox::popo::Listener m_listener;

  std::function<void()> ReceiveHandlerCallback;
  bool hasCallback = false;
};

namespace sugar
{
  ISharedObjectSubscribler *createSharedObjectSubscrible(ExecEnvironment *exec, const std::string &name)
  {
    return exec->addComponent<SharedObjectSubscribler>("subscribler",
                                                       [=](char *mem) -> SharedObjectSubscribler *
                                                       {
                                                         return new (mem) SharedObjectSubscribler(name.c_str());
                                                       });
  }
  namespace proxy {
    namespace iceoryx{
      void init(){
          constexpr char APP_NAME[] = "iox-cpp-subscriber-untyped";
          iox::runtime::PoshRuntime::initRuntime(APP_NAME);
      }
    }
  }
} // namespace sugar
