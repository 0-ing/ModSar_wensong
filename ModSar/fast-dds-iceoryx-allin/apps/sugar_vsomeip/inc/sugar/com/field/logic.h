#ifndef _SUGAR_COM_FIELD_LOGIC_H
#define _SUGAR_COM_FIELD_LOGIC_H
#include "sugar/com/common.h"
#include "sugar/com/any.h"
namespace sugar
{
    namespace com
    {
        namespace field
        {
            class FieldManagerLogic : public IHandlerManager
            {
            public:

                bool addField(const std::string &name, BasicField *method);
                BasicField *findField(const std::string &name);
            public:
                int disptachMessageInSkeletonWithCallback(int field_op_type,void* content,int size,const std::function<void(void*,int)> &callback);
            private:
                std::map<std::string, BasicField *> _fields;
                std::mutex _mutex_fields;
            };
        } // namespace field

    } // namespace com

} // namespace sugar

#endif // _SUGAR_COM_FIELD_LOGIC_H
