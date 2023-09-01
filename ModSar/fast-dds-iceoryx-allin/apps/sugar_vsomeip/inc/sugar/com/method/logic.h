#ifndef _SUGAR_COM_METHOD_LOGIC_H
#define _SUGAR_COM_METHOD_LOGIC_H
#include "sugar/com/common.h"
#include "sugar/com/any.h"
namespace sugar
{
    namespace com
    {
        namespace method
        {
            
            class MethodManagerLogic : public IHandlerManager
            {
            public:

                bool addMethod(const std::string &name, BasicMethod *method);
                BasicMethod *findMethod(const std::string &name);
                
            public:
                int disptachMessageInSkeletonWithCallback(int method_type,void* content,int size,const std::function<void(void*,int)> &callback);
                
            private:
                std::map<std::string, BasicMethod *> _methods;
                std::mutex _mutex_methods;
            };
        } // namespace method

    } // namespace com

} // namespace sugar

#endif // _SUGAR_COM_METHOD_LOGIC_H
