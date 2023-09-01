#ifndef _SUGAR_COM_COMMON_H
#define _SUGAR_COM_COMMON_H

#include <string>
#include "mts/MTSLogic.h"
#include <mutex>
#include <functional>

namespace sugar
{
    namespace com
    {
        int println(const char *fmt, ...);
        void printbin(const char *xxx, void *content, int size);
        /***
         * 单例
         */
        template <typename T>
        class Singleton
        {
        public:
            static T &getInstance()
            {
                static T t;
                return t;
            }
        };
        /**
         * proxy to skeleton stream with head information
         * uniqueTag the unique findable name for field or event or method
         * the syncUniqueId with sync invoke solution
         */
        class StreamHead : public CmdObject
        {
        public:
            std::string uniqueTag;
            int syncUniqueId = 0;
            CMD_SERIALIZE()
            {
                println("CMD_SERIALIZE begin uniqueTag:%s syncUniqueId:%d", uniqueTag.c_str(), syncUniqueId);
                BIND_MSG(uniqueTag);
                BIND_MSG(syncUniqueId);
                println("CMD_SERIALIZE end uniqueTag:%s syncUniqueId:%d", uniqueTag.c_str(), syncUniqueId);
            }
        };

        /***
         * 获取主线程stub
         */
        IStub *getMainStub();

        class IHandlerManager
        {
        public:
            template <typename T>
            T *imp()
            {
                return (T *)this;
            }
        };

        class IProxy
        {
        public:
            using BinaryCallback = std::function<void(int method_type, void *, int)>;
            virtual void invokeToSkeleton(int type, void *content, int size){};
            virtual void invokeToSkeletonWithCallback(int type, void *content, int size, const std::function<void(void *, int)> &callback) {}
            virtual void onMessageCallback(const BinaryCallback &callback)
            {
                this->messageCallback = callback;
            }

            BinaryCallback messageCallback;
            virtual IHandlerManager *getEventManger() = 0;
        };

        class IResponse
        {
        public:
            virtual void responseToProxy(int type, void *content, int size) = 0;
        };

        class ISkeleton
        {
        public:
            using BinaryCallback = std::function<void(int method_type, IResponse *response, void *, int)>;

            virtual void onMessageCallback(const BinaryCallback &callback)
            {
                this->messageCallback = callback;
            }
            virtual void notifyToProxy(void *content, int size) = 0;
            BinaryCallback messageCallback;
            virtual bool checkEventReady() = 0;
            virtual IHandlerManager *getMethodManger() = 0;
            virtual IHandlerManager *getFieldManger() = 0;
        };

        class IProtocol
        {
        public:
            ISkeleton *skeleton = NULL;
            IProxy *proxy = NULL;
        };

        class BasicObject
        {
        public:
            StreamHead head;
            BasicObject(const std::string &file, int line, IProtocol *proto);
            virtual ISkeleton *getSkeleton();
            virtual IProxy *getProxy();
            virtual void setProtocol(IProtocol *proto);
            virtual IProtocol *getProtocol();
            void bindSkeleton(ISkeleton *skeleton)
            {
                println("BasicField::bindSkeleton skeleton:%p", skeleton);
                this->getProtocol()->skeleton = skeleton;
            }

        private:
            IProtocol *_proto = NULL;
        };

        class BasicMethod : public BasicObject
        {
        public:
            virtual void handleInSkeleton(cmd::Stream *in, cmd::Stream *out) = 0;

            BasicMethod(const std::string &file, int line, IProtocol *proto);
        };

        class BasicEvent : public BasicObject
        {
        public:
            virtual void notify() = 0;
            virtual void subscrible(const std::function<void()> &func)
            {
                regEvent();
                this->onChangeCallback = func;
            };
            // virtual void on
            virtual void regEvent() = 0;

            BasicEvent(const std::string &file, int line, IProtocol *proto);

            virtual void dispatchOnChange(cmd::Stream *in, cmd::Stream *out) = 0;

            void onChange(const std::function<void()> &onChangeCallback)
            {
                regEvent();
                this->onChangeCallback = onChangeCallback;
            }
            std::function<void()> onChangeCallback;
        };
        class BasicField : public BasicEvent
        {
        public:
            enum Type
            {
                GET = 0,
                SET = 1
            };

            void onSet(const std::function<void()> &onSetCallback)
            {
                regField();
                this->onSetCallback = onSetCallback;
            }

            void onGet(const std::function<void()> &onGetCallback)
            {
                regField();
                this->onGetCallback = onGetCallback;
            }

            virtual void set() = 0;
            virtual void get() = 0;

            std::function<void()> onGetCallback;
            std::function<void()> onSetCallback;

            virtual void dispatchInSkeleton(int type, cmd::Stream *in, cmd::Stream *out) = 0;
            BasicField(const std::string &file, int line, IProtocol *proto);

        protected:
            virtual void regField() {}
        };

        enum SomeipProxyMethod
        {
            SOMEIP_METHOD_INVALID = -1,
            SOMEIP_METHOD = 0,
            SOMEIP_GET_FIELD,
            SOMEIP_SET_FIELD,
            SOMEIP_EVENT_NOTIFY,
        };

    } // namespace com
} // namespace sugar

#endif // _SUGAR_COM_COMMON_H
