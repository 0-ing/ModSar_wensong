#include "sugar/com/event/logic.h"
#include "sugar/com/event.h"

namespace sugar
{
    namespace com
    {
        void SugarEvent::regEvent()
        {
            this->getProxy()->getEventManger()->imp<event::EventManagerLogic>()->addEvent(this->head.uniqueTag, this);
        }
        void SugarEvent::notifyInSkeletonToProxy(cmd::BinaryStream &in)
        {
            getSkeleton()->checkEventReady();
            getSkeleton()->notifyToProxy(in.content(), in.size());
        }
        namespace event
        {

            bool EventManagerLogic::addEvent(const std::string &name, BasicEvent *method)
            {
                std::lock_guard<std::mutex> mylock(_mutex_events);
                auto it = _events.find(name);
                if (it != _events.end())
                {
                    return false;
                }
                _events[name] = method;
                return true;
            }
            BasicEvent *EventManagerLogic::findEvent(const std::string &name)
            {
                std::lock_guard<std::mutex> mylock(_mutex_events);
                auto it = _events.find(name);
                if (it != _events.end())
                {
                    return it->second;
                }
                return NULL;
            }

            void EventManagerLogic::dispatchOnChange(void *content, int size)
            {
                printbin("=====================================EventManagerLogic::disptachMessageInSkeleton", content, size);
                cmd::BinaryStream instream;
                instream.set(content, size);

                sugar::com::StreamHead head;

                remote::parseStream(head, &instream);
                BasicEvent *event = findEvent(head.uniqueTag);
                if (event)
                {
                    cmd::BinaryStream retStream;
                    event->dispatchOnChange(&instream, &retStream);

                    printbin("EventManagerLogic::disptachMessageInSkeleton", retStream.content(), retStream.size());
                }
                else
                {
                    printf("EventManagerLogic::disptachMessageInSkeleton can't find event(%s) size:%d\n", head.uniqueTag.c_str(), size);
                }
                return;
            }

        } // namespace event

    } // namespace com

} // namespace sugar
