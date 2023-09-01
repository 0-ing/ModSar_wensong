#include "fastdds-wrapper/SugarFastDDSSubscriber.h"

namespace sugar
{
    namespace com
    {
        void DDSEvent::publish(void *content, int size)
        {
            getDDSPubliser()->publish(content,size);
        }

        int DDSEvent::getNewSamples(const std::function<void(void *msg, int size)> &callback)
        {
            return getDDSSubscriber()->getNewSamples(callback);
        }

        void DDSEvent::SubScribler(int size)
        {
            getDDSSubscriber()->setMaxSamples(size);
        } // 构建发布对象 绑定到DDS Event 上
        IDDSSubscriber* DDSEvent::getDDSSubscriber()
        {
            if (!subscriber) {
                subscriber = new SugarFastDDSSubscriber(this->getUnqiueTag());
                subscriber->init();
            }
            return subscriber;
        }
        void DDSEvent::UnsetReceiveHandler(){
            getDDSSubscriber()->unsetReceiveHandler();
        }

        IDDSPublisher * DDSEvent::getDDSPubliser()
        {
            return NULL;
        }
        const char *DDSEvent::getUnqiueTag()
        {
            return "";
        }
    } // namespace com

} // namespace sugar
