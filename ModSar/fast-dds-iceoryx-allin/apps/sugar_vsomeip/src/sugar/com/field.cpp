
#include "sugar/com/field.h"
#include "sugar/com/sync.h"
#include "sugar/com/field/logic.h"
#include "sugar/com/event/logic.h"
#include "mts/MTSLogic.h"
#include "sugar/com/any.h"
#include "sugar/runtime.h"
namespace sugar
{
    namespace com
    {
        bool SugarField::invokeInProxyToSkeletonWithInOut(int type, cmd::BinaryStream &in, cmd::BinaryStream &out)
        {
            int method_type = com::SOMEIP_METHOD_INVALID;
            if (type == sugar::com::BasicField::GET)
                method_type = com::SOMEIP_GET_FIELD;
            if (type == sugar::com::BasicField::SET)
                method_type = com::SOMEIP_SET_FIELD;

            printbin("FieldManagerLogic::invokeSkeletonMethodInProxyWithCallback", in.content(), in.size());
            std::promise<void> promise;
            auto futher = promise.get_future();
            this->getProxy()->invokeToSkeletonWithCallback(
                method_type,
                in.content(),
                in.size(),
                [&](void *content, int size)
                {
                    out.set(content,size);
                    promise.set_value(); });
            futher.wait();
            return true;
        }
        void SugarField::regEvent()
        {
            this->getProxy()->getEventManger()->imp<event::EventManagerLogic>()->addEvent(this->head.uniqueTag, this);
        }
        void SugarField::notifyInSkeletonToProxy(cmd::BinaryStream &in)
        {
            getSkeleton()->notifyToProxy(in.content(), in.size());
        }
        namespace field
        {
            int FieldManagerLogic::disptachMessageInSkeletonWithCallback(int field_op_type, void *content, int size, const std::function<void(void *, int)> &callback)
            {
                printbin("====FieldManagerLogic::disptachMessageInSkeletonWithCallback", content, size);
                cmd::BinaryStream instream;
                instream.set(content, size);

                sugar::com::StreamHead head;

                remote::parseStream(head, &instream);
                BasicField *field = findField(head.uniqueTag);
                if (field)
                {
                    cmd::BinaryStream retStream;
                    field->dispatchInSkeleton(field_op_type, &instream, &retStream);

                    callback(retStream.content(), retStream.size());

                    if (field_op_type == sugar::com::BasicField::SET)
                    {
                        field->notify();
                    }
                    printbin("FieldManagerLogic::disptachMessageInSkeletonWithCallback end", retStream.content(), retStream.size());
                }
                else
                {
                    printf("FieldManagerLogic::disptachMessageInSkeletonWithCallback can't find method(%s) size:%d\n", head.uniqueTag.c_str(), size);
                }
                return 0;
            }

            bool FieldManagerLogic::addField(const std::string &name, BasicField *method)
            {
                std::lock_guard<std::mutex> mylock(_mutex_fields);
                auto it = _fields.find(name);
                if (it != _fields.end())
                {
                    return false;
                }
                _fields[name] = method;
                return true;
            }
            BasicField *FieldManagerLogic::findField(const std::string &name)
            {
                std::lock_guard<std::mutex> mylock(_mutex_fields);
                auto it = _fields.find(name);
                if (it != _fields.end())
                {
                    return it->second;
                }
                return NULL;
            }

        } // namespace method

    } // namespace com

}
