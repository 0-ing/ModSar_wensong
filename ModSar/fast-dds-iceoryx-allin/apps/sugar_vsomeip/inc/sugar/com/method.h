#ifndef _SUGAR_COM_METHOD_H
#define _SUGAR_COM_METHOD_H

#include <functional>
#include <stdio.h>
#include <string>
#include "sugar/com/common.h"
#include "method/logic.h"
namespace sugar
{
    namespace com
    {
        template <typename T>
        using Function = std::function<T>;

        class SugarMethod : public BasicMethod
        {
        public:
            SugarMethod(const std::string &file, int line, IProtocol *proto) : BasicMethod(file, line, proto) {}
            virtual void prepareStreamInProxy(cmd::BinaryStream &ss)
            {
                // 加解析头
                remote::toStream(head, &ss);
            }

            template <typename RET>
            RET invokeInProxyToSkeleton(RET &ret, cmd::BinaryStream &ss)
            {
                cmd::BinaryStream out;
                invokeInProxyToSkeletonWithInOut(ss, out);
                remote::parseStream(ret, &out);

                return ret;
            }

            bool invokeInProxyToSkeletonWithInOut(cmd::BinaryStream &in, cmd::BinaryStream &out);
        };

        // support 10 args
        template <typename RET, typename T1 = void, typename T2 = void, typename T3 = void, typename T4 = void, typename T5 = void,
                  typename T6 = void, typename T7 = void, typename T8 = void, typename T9 = void, typename T10 = void>
        class Method : public SugarMethod
        {
        public:
            std::function<RET(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)> func;
            void handleInSkeleton(cmd::Stream *in, cmd::Stream *out)
            {
                T1 t1;
                T2 t2;
                T3 t3;
                T4 t4;
                T5 t5;
                T6 t6;
                T7 t7;
                T8 t8;
                T9 t9;
                T10 t10;
                remote::parseStream(t1, in);
                remote::parseStream(t2, in);
                remote::parseStream(t3, in);
                remote::parseStream(t4, in);
                remote::parseStream(t5, in);
                remote::parseStream(t6, in);
                remote::parseStream(t7, in);
                remote::parseStream(t8, in);
                remote::parseStream(t9, in);
                remote::parseStream(t10, in);
                RET ret = func(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10);
                // 构建返回
                toStream(ret, out);
            }
            Method(std::function<RET(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)> func) : func(func)
            {
            }
            void bindSkeleton(sugar::com::ISkeleton *skeleton,const std::function<RET(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)> &func)
            {
                this->func = func;
                this->_proto->skeleton = skeleton;
                skeleton->getMethodManger()->imp<method::MethodManagerLogic>()->addMethod(this->_unqiueTag, this);
            }
            Method() {}
            Method(const std::string &file, int line, IProtocol *proto) : SugarMethod(file, line, proto) {}

            RET operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9, T10 t10)
            {
                cmd::BinaryStream ss;
                SugarMethod::prepareStreamInProxy(ss);
                remote::toStream(t1, &ss);
                remote::toStream(t2, &ss);
                remote::toStream(t3, &ss);
                remote::toStream(t4, &ss);
                remote::toStream(t5, &ss);
                remote::toStream(t6, &ss);
                remote::toStream(t7, &ss);
                remote::toStream(t8, &ss);
                remote::toStream(t9, &ss);
                remote::toStream(t10, &ss);
                RET ret;
                return invokeInProxyToSkeleton<RET>(ret, ss);
            }
        };

        template <typename RET, typename T1>
        class Method<RET, T1> : public SugarMethod
        {
        public:
            std::function<RET(T1)> func;
            // skeleton 调用
            void handleInSkeleton(cmd::Stream *in, cmd::Stream *out)
            {
                T1 t1;
                remote::parseStream(t1, in);
                RET ret = func(t1);
                // 构建返回
                remote::toStream(ret, out);
            }
            Method(std::function<RET(T1)> func) : func(func)
            {
            }
            void bindSkeleton(sugar::com::ISkeleton *skeleton,const std::function<RET(T1)> &func)
            {
                this->func = func;
                this->getProtocol()->skeleton = skeleton;
                skeleton->getMethodManger()->imp<method::MethodManagerLogic>()->addMethod(this->head.uniqueTag, this);
            }
            Method() {}
            Method(const std::string &file, int line, IProtocol *proto) : SugarMethod(file, line, proto) {}
            RET operator()(T1 t1)
            {
                cmd::BinaryStream ss;
                SugarMethod::prepareStreamInProxy(ss);
                remote::toStream(t1, &ss);
                RET ret;
                return invokeInProxyToSkeleton<RET>(ret, ss);
            }
        };
        template <typename RET>
        class Method<RET> : public SugarMethod
        {
        public:
            std::function<RET()> func;
            void handleInSkeleton(cmd::QuickBinaryStream &in, cmd::QuickBinaryStream &out)
            {
                RET ret = func();
                toStream(ret, &out);
            }
            Method(std::function<RET()> func) : func(func)
            {
            }
            void bindSkeleton(sugar::com::ISkeleton *skeleton, const std::function<RET()> &func)
            {
                this->func = func;
                this->_proto->skeleton = skeleton;
                skeleton->getMethodManger()->imp<method::MethodManagerLogic>()->addMethod(this->_unqiueTag, this);
            }
            Method() {}
            Method(const std::string &file, int line, IProtocol *proto) : SugarMethod(file, line, proto) {}
            RET operator()()
            {
                cmd::BinaryStream ss;
                prepareStreamInProxy(ss);
                RET ret;
                return invokeInProxyToSkeleton<RET>(ret, ss);
            }
        };
    } // namespace method

} // namespace sugar

template <typename RET, typename T1>
sugar::com::Method<RET, T1> decfunc(const std::function<RET(T1)> &m)
{
    sugar::com::Method<RET, T1> m1;
    return m1;
}

template <typename RET>
sugar::com::Method<RET> decfunc(const std::function<RET()> &m)
{
    sugar::com::Method<RET> m1;
    return m1;
}

#define declare_method(func, name) \
    static func name##_##__LINE__; \
    decltype(decfunc(name##_##__LINE__)) name = {__FILE__, __LINE__, this}

#define register_method(name, func) \
    name.bindSkeleton(this->getSkeleton(), func);
#endif // _SUGAR_COM_METHOD_H
