
#include "sugar/com/method.h"
#include "sugar/com/sync.h"
#include "sugar/com/method/logic.h"
#include "mts/MTSLogic.h"
#include "sugar/com/any.h"
#include "sugar/runtime.h"
namespace sugar
{
    namespace com
    {
        bool SugarMethod::invokeInProxyToSkeletonWithInOut(cmd::BinaryStream &in,cmd::BinaryStream &out)
        {
             
            printbin("MethodManagerLogic::invokeSkeletonMethodInProxyWithCallback", in.content(), in.size());
                std::promise<void> promise;
                auto futher = promise.get_future();
                this->getProxy()->invokeToSkeletonWithCallback(SomeipProxyMethod::SOMEIP_METHOD, in.content(), in.size(),[&](void*content,int size){
                    out.set(content,size);
                    printbin("invokeInProxyToSkeleton",&out.contents[0],out.contents.size());      
                    promise.set_value();
                });
                futher.wait();
            return true;
        }
        namespace method
        {
            int MethodManagerLogic::disptachMessageInSkeletonWithCallback(int method_type,void* content,int size,const std::function<void(void*,int)> &callback)
            {
                printbin("MethodManagerLogic::disptachMessageInSkeletonWithCallback",content,size);
                cmd::BinaryStream instream;
                instream.set(content,size);
       
                sugar::com::StreamHead head;
            
                remote::parseStream(head,&instream);
                BasicMethod *method = findMethod(head.uniqueTag);
                if (method)
                {
                    cmd::BinaryStream retStream;
                    method->handleInSkeleton(&instream, &retStream);
                    callback(retStream.content(),retStream.size());
                    printbin("MethodManagerLogic::disptachMessageInSkeletonWithRet",retStream.content(),retStream.size());
                }
                else {
                    printf("MethodManagerLogic::disptachMessageInSkeleton can't find method(%s) size:%d\n",head.uniqueTag.c_str(),size);
                }
                return 0;
            }

            bool MethodManagerLogic::addMethod(const std::string &name, BasicMethod *method)
            {
                std::lock_guard<std::mutex> mylock(_mutex_methods);
                auto it = _methods.find(name);
                if (it != _methods.end())
                {
                    return false;
                }
                _methods[name] = method;
                return true;
            }
            BasicMethod *MethodManagerLogic::findMethod(const std::string &name)
            {
                std::lock_guard<std::mutex> mylock(_mutex_methods);
                auto it = _methods.find(name);
                if (it != _methods.end())
                {
                    return it->second;
                }
                return NULL;
            }
        } // namespace method

    } // namespace com

}
