#ifndef _SUGAR_COM_DDS_EVENT_H
#define _SUGAR_COM_DDS_EVENT_H
#include <functional>
#include "mts/MTSLogic.h"
namespace sugar
{
    namespace com
    {
        class IDDSSubscriber
        {
        public:
            virtual void setReceiveHandler(const std::function<void()> &callback) = 0;
            virtual int getNewSamples(const std::function<void(void *msg, int size)> &callback);
            virtual void setMaxSamples(int size) = 0;
            virtual bool init() = 0;
            virtual void unsetReceiveHandler() = 0;
        };

        class IDDSPublisher
        {
        public:
            virtual bool publish(void *content, int size) = 0;
        };

        class DDSEvent
        {
        public:
            DDSEvent()
            {
                // 延迟创建 如果是Subsrible 的化 则构建具体的对象 并传入回调
            }
            template <typename T>
            void Publish()
            {
                cmd::BinaryStream out;
                T *msg = (T *)this;
                msg->serializeToStream(out);
                publish(out.content(), out.size());
            }
            virtual void publish(void *content, int size);
            /**
             * 每次去轮询
             * \return int 数量
             **/
            template <typename T>
            int GetNewSamples(const std::function<void(T *msg)> &callback)
            {
                return getNewSamples([&](void *msg, int size)
                                     {
                    T* obj = (T*) this;
                    obj->deserializeWithBinary(msg,size);
                    callback(obj); });
            }
            int getNewSamples(const std::function<void(void *msg, int size)> &callback);

            virtual void SubScribler(int size); // 构建发布对象 绑定到DDS Event 上

            void SetReceiveHandler(const std::function<void()> &callback)
            {
                getDDSSubscriber()->setReceiveHandler(callback);
            }
            void UnsetReceiveHandler();

            virtual IDDSSubscriber *getDDSSubscriber();
            virtual IDDSPublisher *getDDSPubliser();

            const char *getUnqiueTag();

        private:
            IDDSSubscriber *subscriber = nullptr;
            IDDSPublisher *publisher = nullptr;
        };
    } // namespace com

} // namespace sugar

#endif // _SUGAR_COM_DDS_EVENT_H
