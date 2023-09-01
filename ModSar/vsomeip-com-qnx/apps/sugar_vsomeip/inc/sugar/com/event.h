#ifndef _SUGAR_COM_EVENT1_H
#define _SUGAR_COM_EVENT1_H
#include "sugar/com/common.h"
#include "sugar/com/any.h"
#include "sugar/com/sync.h"
namespace sugar
{
    namespace com
    {
        class SugarEvent : public BasicEvent
        {
        public:
            SugarEvent(const std::string &file, int line, IProtocol *proto) : BasicEvent(file, line, proto) {}
            virtual void prepareStreamInProxy(cmd::BinaryStream &ss)
            {
                // 加解析头
                remote::toStream(head, &ss);
            }

            void notifyInSkeletonToProxy(cmd::BinaryStream &in);

            virtual void notify()
            {
            }
            // virtual void on
            virtual void regEvent();

            void dispatchOnChange(cmd::Stream *in, cmd::Stream *out)
            {

            }
        };
       
        // support 5 args
        template <typename T1, typename T2 = void, typename T3 = void, typename T4 = void, typename T5 = void>
        class Event : public SugarEvent, public CmdObject
        {
        public:
            Event(const std::string &file, int line,IProtocol *proto) : SugarEvent(file, line, proto) {}
            T1 one;
            T2 two;
            T3 three;
            T4 four;
            T5 five;
            void dispatchOnChange(cmd::Stream *in, cmd::Stream *out)
            {
                remote::parseStream(one, in);
                remote::parseStream(two, in);
                remote::parseStream(three, in);
                remote::parseStream(four, in);
                remote::parseStream(five, in);
                this->onChangeCallback();
            }
         
            void operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
            {
                this->one = t1;
                this->two = t2;
                this->three = t3;
                this->four = t4;
                this->five = t5;
            }
            virtual void notify()
            {
                cmd::BinaryStream ss;
                SugarEvent::prepareStreamInProxy(ss);
                remote::toStream(one, &ss);
                remote::toStream(two, &ss);
                remote::toStream(three, &ss);
                remote::toStream(four, &ss);
                remote::toStream(five, &ss);
                notifyInSkeletonToProxy(ss);
            }
     
            CMD_SERIALIZE()
            {
                BIND_MSG(one);
                BIND_MSG(two);
                BIND_MSG(three);
                BIND_MSG(four);
                BIND_MSG(five);
            }
        };

        template <typename T1>
        class Event<T1> : public SugarEvent, public CmdObject
        {
        public:
            T1 one;
            Event(const std::string &file, int line,IProtocol *proto) : SugarEvent(file, line, proto) {}

      
            void notify()
            {
                cmd::BinaryStream ss;
                SugarEvent::prepareStreamInProxy(ss);
                remote::toStream(one, &ss);
                notifyInSkeletonToProxy(ss);
            }
            void operator()(T1 t1)
            {
                this->one = t1;
            }
    
            CMD_SERIALIZE()
            {
                BIND_MSG(one);
            }
             void dispatchOnChange(cmd::Stream *in, cmd::Stream *out)
            {
                remote::parseStream(one, in);
       
                this->onChangeCallback();
            }
        };

    } // namespace name

} // namespace sugar

#define declare_event(field, name) \
    field name = {__FILE__, __LINE__, this}

#define register_event(name) \
     name.bindSkeleton(this->getSkeleton());

#endif // _SUGAR_COM_EVENT1_H
