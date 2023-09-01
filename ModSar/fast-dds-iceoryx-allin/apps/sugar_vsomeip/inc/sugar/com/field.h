#ifndef _SUGAR_COM_FIELD_H
#define _SUGAR_COM_FIELD_H
#include "sugar/com/common.h"
#include "sugar/com/any.h"
#include "sugar/com/sync.h"
#include "sugar/com/field/logic.h"
namespace sugar
{
    namespace com
    {
        class SugarField : public BasicField
        {
        public:
            SugarField(const std::string &file, int line, IProtocol *proto) : BasicField(file, line, proto) {}
            virtual void prepareStreamInProxy(cmd::BinaryStream &ss)
            {
                // 加解析头
                remote::toStream(head, &ss);
            }

            template <typename RET>
            RET invokeInProxyToSkeleton(int type, RET &ret, cmd::BinaryStream &ss)
            {
                cmd::BinaryStream out;
                invokeInProxyToSkeletonWithInOut(type, ss, out);
                remote::parseStream(ret, &out);

                return ret;
            }

            bool invokeInProxyToSkeletonWithInOut(int type, cmd::BinaryStream &in, cmd::BinaryStream &out);

            virtual void regField() {}

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
        class FieldManagerLogic
        {
        public:
            int addField(const std::string &name, BasicField *field);
            BasicMethod *findField(const std::string &name);

        private:
            std::map<std::string, BasicField *> _fields;
        };
        // support 5 args
        template <typename T1, typename T2 = void, typename T3 = void, typename T4 = void, typename T5 = void>
        class Field : public SugarField, public CmdObject
        {
        public:
            Field(const std::string &file, int line,IProtocol *proto) : SugarField(file, line, proto) {}
            T1 one;
            T2 two;
            T3 three;
            T4 four;
            T5 five;
            void dispatchInSkeleton(int type, cmd::Stream *in, cmd::Stream *out)
            {
                if (type == SET)
                {
                    // 解析int
                    remote::parseStream(one, in);
                    remote::parseStream(two, in);
                    remote::parseStream(three, in);
                    remote::parseStream(four, in);
                    remote::parseStream(five, in);

                    onSetCallback();
                    int ret = 0;
                    remote::toStream(ret, out);
                }
                if (type == GET)
                {

                    onGetCallback();

                    auto &ret = *this;
                    // 构建返回
                    remote::toStream(ret, out);
                }
            }
            void dispatchOnChange(cmd::Stream *in, cmd::Stream *out)
            {
                remote::parseStream(one, in);
                remote::parseStream(two, in);
                remote::parseStream(three, in);
                remote::parseStream(four, in);
                remote::parseStream(five, in);
                this->onChangeCallback();
            }
            void regField()
            {
                this->getSkeleton()->getFieldManger()->imp<field::FieldManagerLogic>()->addField(this->head.uniqueTag, this);
            }
            void operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
            {
                this->one = t1;
                this->two = t2;
                this->three = t3;
                this->four = t4;
                this->five = t5;
                set();
            }
            virtual void notify()
            {
                cmd::BinaryStream ss;
                SugarField::prepareStreamInProxy(ss);
                remote::toStream(one, &ss);
                remote::toStream(two, &ss);
                remote::toStream(three, &ss);
                remote::toStream(four, &ss);
                remote::toStream(five, &ss);
                notifyInSkeletonToProxy(ss);
            }
            virtual void set()
            {
                cmd::BinaryStream ss;
                SugarField::prepareStreamInProxy(ss);
                remote::toStream(one, &ss);
                remote::toStream(two, &ss);
                remote::toStream(three, &ss);
                remote::toStream(four, &ss);
                remote::toStream(five, &ss);

                int ret;
                invokeInProxyToSkeleton<int>(SET, ret, ss);
            }
            virtual void get()
            {
                cmd::BinaryStream ss;
                SugarField::prepareStreamInProxy(ss);
                auto &ret = *this;
                invokeInProxyToSkeleton<decltype(*this)>(GET, ret, ss);
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
        class Field<T1> : public SugarField, public CmdObject
        {
        public:
            T1 one;
            Field(const std::string &file, int line,IProtocol *proto) : SugarField(file, line, proto) {}
            void dispatchInSkeleton(int type, cmd::Stream *in, cmd::Stream *out)
            {
                println("Field<T1>::dispatchInSkeleton type:%d", type);
                if (type == SET)
                {
                    // 解析int
                    remote::parseStream(one, in);
                    onSetCallback();
                    int ret = 0;
                    remote::toStream(ret, out);
                }
                if (type == GET)
                {

                    onGetCallback();

                    auto &ret = *this;
                    // 构建返回
                    remote::toStream(ret, out);
                }
            }
            void regField()
            {
                this->getSkeleton()->getFieldManger()->imp<field::FieldManagerLogic>()->addField(this->head.uniqueTag, this);
            }
            void notify()
            {
                cmd::BinaryStream ss;
                SugarField::prepareStreamInProxy(ss);
                remote::toStream(one, &ss);
                notifyInSkeletonToProxy(ss);
            }
            void operator()(T1 t1)
            {
                this->one = t1;
                set();
            }
            virtual void set()
            {
                cmd::BinaryStream ss;
                SugarField::prepareStreamInProxy(ss);
                remote::toStream(one, &ss);
                int ret = 0;
                invokeInProxyToSkeleton<int>(SET, ret, ss);
            }
            virtual void get()
            {
                cmd::BinaryStream ss;
                SugarField::prepareStreamInProxy(ss);
                auto &ret = *this;
                invokeInProxyToSkeleton<decltype(*this)>(GET, ret, ss);
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

#define declare_field(field, name) \
    field name = {__FILE__, __LINE__, this}

#define register_field(name) \
     name.bindSkeleton(this->getSkeleton());

#endif // _SUGAR_COM_FIELD_H
