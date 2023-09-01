#ifndef _SUGAR_COM_EVENT1_H
#define _SUGAR_COM_EVENT1_H
#include "sugar/com/common.h"
#include "sugar/com/any.h"
#include "sugar/com/sync.h"
#include "sugar/shared_object.h"
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

            // virtual void on
            virtual void regEvent();

            void dispatchOnChange(cmd::Stream *in, cmd::Stream *out)
            {
                deserializeBody(in);
                this->onChangeCallback();
            }
            void deserializeWithBinary(void *content, int size)
            {
                cmd::BinaryStream instream;
                instream.set(content, size);

                sugar::com::StreamHead head;

                remote::parseStream(head, &instream);

                deserializeBody(&instream);
            }
            virtual void deserializeBody(cmd::Stream *in) = 0;
            virtual void serializeToStream(cmd::Stream *out)
            {
                prepareStreamInProxy(*(cmd::BinaryStream*)out);
                serializeBody(out);
            }
            virtual void serializeBody(cmd::Stream *out) = 0;

            virtual void notify()
            {
                cmd::BinaryStream ss;
                serializeToStream(&ss);
                notifyInSkeletonToProxy(ss);
            }

        };

        // support 5 args
        template <typename T1, typename T2 = void, typename T3 = void, typename T4 = void, typename T5 = void>
        class Event : public SugarEvent, public CmdObject
        {
        public:
            Event(const std::string &file, int line, IProtocol *proto) : SugarEvent(file, line, proto) {}
            T1 one;
            T2 two;
            T3 three;
            T4 four;
            T5 five;
            void deserializeBody(cmd::Stream *in)
            {
                remote::parseStream(one, in);
                remote::parseStream(two, in);
                remote::parseStream(three, in);
                remote::parseStream(four, in);
                remote::parseStream(five, in);
            }

            void operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
            {
                this->one = t1;
                this->two = t2;
                this->three = t3;
                this->four = t4;
                this->five = t5;
            }

            void serializeBody(cmd::Stream *out)
            {
                remote::toStream(one, out);
                remote::toStream(two, out);
                remote::toStream(three, out);
                remote::toStream(four, out);
                remote::toStream(five, out);
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
            Event(const std::string &file, int line, IProtocol *proto) : SugarEvent(file, line, proto) {}

            void operator()(T1 t1)
            {
                this->one = t1;
            }
            
            void deserializeBody(cmd::Stream *in)
            {
                remote::parseStream(one, in);
            }
            void serializeBody(cmd::Stream *out)
            {
                remote::toStream(one, out);
            }

            CMD_SERIALIZE()
            {
                BIND_MSG(one);
            }
        };

        /***
         * 零拷贝方案 
         */
        template<typename T1>
        class Event<T1*>  : public SugarEvent , public ExecEnvironment {
        public:
            T1* one = NULL;
            Event(const std::string &file, int line, IProtocol *proto) : SugarEvent(file, line, proto) {}
            T1* operator->(){
                if (one) return one;
                if (!publish) {
                    publish = createSharedObjectPublish(this,this->head.uniqueTag);
                    one = (T1*)publish->loan(sizeof(T1));
                }
                return one;
            }
         
            void Subscrible(int size) {
                if (!subscrible) {
                    subscrible = createSharedObjectSubscrible(this,this->head.uniqueTag);
                }
            }
            void Publish() {
                if (publish) publish->publish(one);
            }
            void GetOneSample(const std::function<void(T1*)> &callback) {
                subscrible->GetSample([=](void*obj){
                    T1* t1 = (T1*) obj;
                    callback(t1);
                });
                return;
            }
            void SetReceiveHandler(const std::function<void()> &callback)
            {
                subscrible->SetReceiveHandler(callback);
            }
            void UnsetReceiveHandler()
            {
                subscrible->UnsetReceiveHandler();
            }
            ISharedObjectPublisher *publish = NULL;
            ISharedObjectSubscribler *subscrible = NULL;


            void deserializeBody(cmd::Stream *in) {}
            void serializeBody(cmd::Stream *out) {}

        };

    } // namespace name

} // namespace sugar

#define declare_event(field, name) \
    field name = {__FILE__, __LINE__, this}

#define register_event(name) \
    name.bindSkeleton(this->getSkeleton());

#endif // _SUGAR_COM_EVENT1_H
