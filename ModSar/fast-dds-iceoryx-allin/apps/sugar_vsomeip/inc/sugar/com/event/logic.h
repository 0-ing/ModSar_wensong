#ifndef _SUGAR_COM_EVENT_LOGIC_H
#define _SUGAR_COM_EVENT_LOGIC_H
#include "sugar/com/common.h"
#include "sugar/com/any.h"
namespace sugar
{
    namespace com
    {
        namespace event
        {
            
            class EventManagerLogic : public IHandlerManager
            {
            public:

                bool addEvent(const std::string &name, BasicEvent *method);
                BasicEvent *findEvent(const std::string &name);
                
                void dispatchOnChange(void *content,int size);
            private:
                std::map<std::string, BasicEvent *> _events;
                std::mutex _mutex_events;
            };
        } // namespace field

    } // namespace com

} // namespace sugar

#endif // _SUGAR_COM_EVENT_LOGIC_H