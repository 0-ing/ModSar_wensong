//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

#ifndef COM_BINDING_METHOD_EXECUTER_BINDING_SERIALIZED_HPP
#define COM_BINDING_METHOD_EXECUTER_BINDING_SERIALIZED_HPP

#include "ara/com/ISkeletonMethod.hpp"
#include "ara/com/e2e/types.h"
#include "ara/com/method_settings.hpp"
#include "ara/com/types.h"
#include "ara/core/future.h"
#include "ara/core/promise.h"
#include "binding/MethodQueue.hpp"
#include "e2e/IE2EChecker.hpp"
#include "e2e/IE2EProtector.hpp"
#include "method_transport_binding.hpp"
#include "serializer/ArgumentDeserializerCarrier.hpp"
#include "serializer/IDeserializer.hpp"
#include "serializer/ISerializer.hpp"
#include "someip/logger/someip_log.hpp"

#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <type_traits>
#include <vector>

namespace com
{
namespace binding
{
template<typename... TArgs>

class MethodExecuterBindingFireForgetSerialized : public ara::com::ISkeletonMethodFireForget<TArgs...>
{
public:
    /** \brief Declarations for readability and forwarding to derived classes */
    template<typename T>
    using UniquePtr               = ara::com::UniquePtr<T>;
    using MethodCfgSomeIp         = ::com::config::MethodCfgSomeIp;
    using DeploymentContextSomeIp = ::com::config::DeploymentContextSomeIp;
    using MethodCfgIpc            = ::com::config::MethodCfgIpc;
    using DeploymentContextIpc    = ::com::config::DeploymentContextIpc;
    using IE2EChecker             = ::com::e2e::IE2EChecker;
    using E2EResult               = ara::com::e2e::Result;
    using E2EProfileCheckStatus   = ara::com::e2e::ProfileCheckStatus;

    /** \brief Constructor for a IPC configuration */
    MethodExecuterBindingFireForgetSerialized(
        const MethodCfgIpc& config,
        const DeploymentContextIpc& context,
        ara::com::UniquePtr<serializer::ArgumentDeserializerCarrier<sizeof...(TArgs), TArgs...>> adc,
        UniquePtr<IE2EChecker>&& checker,
        const std::shared_ptr<MethodQueue>& f_methodQueue)
        : m_transportBind(config, context, f_methodQueue),
          deserializercarrierp(std::move(adc)),
          m_checker(std::move(checker)),
          m_methodQueue(f_methodQueue)
    {
        m_transportBind.RegisterMessageHandler(
            std::bind(&MethodExecuterBindingFireForgetSerialized::On_MethodCall, this, std::placeholders::_1));
    }

    /** \brief Constructor for a SOME/IP deployment configuration */
    MethodExecuterBindingFireForgetSerialized(
        const MethodCfgSomeIp& config,
        const DeploymentContextSomeIp& context,
        ara::com::UniquePtr<serializer::ArgumentDeserializerCarrier<sizeof...(TArgs), TArgs...>> adc,
        UniquePtr<IE2EChecker>&& checker,
        const std::shared_ptr<MethodQueue>& f_methodQueue)
        : m_transportBind(config, context, f_methodQueue),
          deserializercarrierp(std::move(adc)),
          m_checker(std::move(checker)),
          m_methodQueue(f_methodQueue)
    {
        m_transportBind.RegisterMessageHandler(
            std::bind(&MethodExecuterBindingFireForgetSerialized::On_MethodCall, this, std::placeholders::_1));
    }

    ~MethodExecuterBindingFireForgetSerialized()
    {
        // If the instance of this class is destroyed we have to set back the message handlers.
        // The mutex/lock structure to ensure that no handler thread is in the instance while it is destroyed
        // is part of Bind_IPC.
        m_transportBind.unRegisterMessageHandler();
    }

    void On_MethodCall(std::shared_ptr<std::vector<uint8_t>> f_p)
    {
        // m_func_call();

        uint32_t deserializeStart = static_cast<uint32_t>(m_checker->getE2EHeaderLength());
        uint32_t dataId{0};
        uint32_t sourceId{0};
        uint32_t message_counter{0};
        E2EResult checkResult = m_checker->check(e2e::MessageType::kRequest,
                                                 e2e::MessageResult::kOk,
                                                 dataId,
                                                 sourceId,
                                                 message_counter,
                                                 f_p->data(),
                                                 f_p->size());
        if (checkResult.checkStatus != E2EProfileCheckStatus::kOk
            && checkResult.checkStatus != E2EProfileCheckStatus::kCheckDisabled)
        {
            m_methodQueue->invokeE2EErrorHandler(checkResult.checkStatus, dataId, message_counter);
            f_p->clear();
            return;
        }

        if (true)
        {
            callerclass<TArgs...> callerc;
            callerc.callerfunction(m_func_call, deserializeStart, f_p, deserializercarrierp.get());
        }

        // reset vector content
        f_p->clear();
    }

    void RegisterProcessingFunction(std::function<void(const TArgs...)>&& f_func) override
    {
        m_func_call = f_func;
    }

private:
    std::function<void(const TArgs...)> m_func_call;
    MethodExecuteTransportBinding m_transportBind;
    ara::com::UniquePtr<serializer::ArgumentDeserializerCarrier<sizeof...(TArgs), TArgs...>> deserializercarrierp;
    UniquePtr<IE2EChecker> m_checker;
    std::shared_ptr<MethodQueue> m_methodQueue;

    //-------------------------------------------------------------
    // Fast-Fix-Solution, will be replaced
    template<typename... Args>
    class callerclass
    {
    public:
        void callerfunction(std::function<void(const Args...)> m_func,
                            uint64_t offset,
                            std::shared_ptr<std::vector<uint8_t>> f_p,
                            serializer::ArgumentDeserializerCarrier<sizeof...(Args), Args...>* deserializercarrierp)
        {
            callstackbuilder<sizeof...(Args), true, Args...> cstackbuilder(m_func, offset, f_p, deserializercarrierp);
        }

    private:
        template<size_t N, bool calllevel, typename... Tss>
        class callstackbuilder;

        template<typename... Tss>
        class callstackbuilder<0, false, Tss...>
        {
        public:
            callstackbuilder(callstackbuilder<1,
                                              (1 == sizeof...(Args)),
                                              typename std::tuple_element<sizeof...(Args) - 1, std::tuple<Args...>>::type,
                                              Tss...>* p_csb,
                             uint64_t,
                             std::shared_ptr<std::vector<uint8_t>>,
                             serializer::ArgumentDeserializerCarrier<0, Tss...>*)
            {
                p_csb->funcin();
            }
        };

        template<typename... Tss>
        class callstackbuilder<0, true, Tss...>
        {
        public:
            callstackbuilder(std::function<void()> m_func,
                             uint64_t,
                             std::shared_ptr<std::vector<uint8_t>>,
                             serializer::ArgumentDeserializerCarrier<0, Tss...>*)
            {
                m_func();
            }
        };

        template<size_t N, typename T1, typename... Ts>
        class callstackbuilder<N, false, T1, Ts...>
        {
        public:
            callstackbuilder(
                callstackbuilder<N + 1,
                                 ((N + 1) == sizeof...(Args)),
                                 typename std::tuple_element<sizeof...(Args) - N - 1, std::tuple<Args...>>::type,
                                 T1,
                                 Ts...>* p_csb,
                uint64_t offset,
                std::shared_ptr<std::vector<uint8_t>> f_p,
                serializer::ArgumentDeserializerCarrier<N, T1, Ts...>* adcp)
            {
                p_callstackbuilder = p_csb;
                uint32_t readbytes;
                // TODO: Remove type casts once the interface has size_t
                bool ok = (adcp->desp)
                              ->deserialize((f_p->data() + offset),
                                            static_cast<uint32_t>(f_p->size() - offset),
                                            &parametervalue,
                                            &readbytes);
                if (ok)
                    callstackbuilder<N - 1, false, Ts...> cstackbuilder(this, offset + readbytes, f_p, adcp->next.get());
                else
                    std::cout << "Deserialization-Error: Method not called!\n";
            }
            T1 parametervalue;
            callstackbuilder<N + 1,
                             ((N + 1) == sizeof...(Args)),
                             typename std::tuple_element<sizeof...(Args) - N - 1, std::tuple<Args...>>::type,
                             T1,
                             Ts...>* p_callstackbuilder;
            void funcin(Ts&... param)
            {
                p_callstackbuilder->funcin(parametervalue, param...);
            }
        };

        template<typename T1, typename... Ts>
        class callstackbuilder<sizeof...(Args), true, T1, Ts...>
        {
        public:
            callstackbuilder(std::function<void(const T1, const Ts...)> m_func,
                             uint64_t offset,
                             std::shared_ptr<std::vector<uint8_t>> f_p,
                             serializer::ArgumentDeserializerCarrier<sizeof...(Args), T1, Ts...>* adcp)
            {
                func = m_func;
                uint32_t readbytes;
                // TODO: Remove type casts once the interface has size_t
                bool ok = (adcp->desp)
                              ->deserialize((f_p->data() + offset),
                                            static_cast<uint32_t>(f_p->size() - offset),
                                            &parametervalue,
                                            &readbytes);
                if (ok)
                    callstackbuilder<sizeof...(Args) - 1, false, Ts...> cstackbuilder(this,
                                                                                      offset + readbytes,
                                                                                      f_p,
                                                                                      adcp->next.get());
                else
                    std::cout << "Deserialization-Error: Method not called!\n";
            }
            std::function<void(T1, Ts...)> func;
            T1 parametervalue;
            void funcin(Ts&... param)
            {
                func(parametervalue, param...);
            }
        };
    };
};

template<typename... TArgs>
class MethodExecuterBindingSerialized;

template<typename MethodOutput_T, typename... TArgs>
class MethodExecuterBindingSerialized<MethodOutput_T, TArgs...>
    : public ara::com::ISkeletonMethod<MethodOutput_T, TArgs...>
{
public:
    /** \brief Declarations for readability and forwarding to derived classes */
    template<typename T>
    using UniquePtr               = ara::com::UniquePtr<T>;
    using MethodCfgSomeIp         = ::com::config::MethodCfgSomeIp;
    using DeploymentContextSomeIp = ::com::config::DeploymentContextSomeIp;
    using MethodCfgIpc            = ::com::config::MethodCfgIpc;
    using DeploymentContextIpc    = ::com::config::DeploymentContextIpc;
    using IE2EChecker             = ::com::e2e::IE2EChecker;
    using IE2EProtector           = ::com::e2e::IE2EProtector;
    using E2EResult               = ara::com::e2e::Result;
    using E2EProfileCheckStatus   = ara::com::e2e::ProfileCheckStatus;
    using Logger                  = com::someip::Logger;

    /** \brief Constructor for a IPC deployment configuration */
    MethodExecuterBindingSerialized(
        const MethodCfgIpc& config,
        const DeploymentContextIpc& context,
        ara::com::UniquePtr<serializer::ArgumentDeserializerCarrier<sizeof...(TArgs), TArgs...>> adc,
        ara::com::UniquePtr<serializer::ISerializer<MethodOutput_T>> os,
        UniquePtr<IE2EChecker>&& checker,
        UniquePtr<IE2EProtector>&& protector,
        const std::shared_ptr<MethodQueue>& f_methodQueue)
        : m_transportBind(config, context, f_methodQueue),
          deserializercarrierp(std::move(adc)),
          outputserializerp(std::move(os)),
          m_checker(std::move(checker)),
          m_protector(std::move(protector)),
          m_methodQueue(f_methodQueue)
    {
        m_transportBind.RegisterMessageHandler(
            std::bind(&MethodExecuterBindingSerialized::On_MethodCall, this, std::placeholders::_1));
    }

    /** \brief Constructor for a SOME/IP deployment configuration */
    MethodExecuterBindingSerialized(
        const MethodCfgSomeIp& config,
        const DeploymentContextSomeIp& context,
        ara::com::UniquePtr<serializer::ArgumentDeserializerCarrier<sizeof...(TArgs), TArgs...>> adc,
        ara::com::UniquePtr<serializer::ISerializer<MethodOutput_T>> os,
        UniquePtr<IE2EChecker>&& checker,
        UniquePtr<IE2EProtector>&& protector,
        const std::shared_ptr<MethodQueue>& f_methodQueue)
        : m_transportBind(config, context, f_methodQueue),
          deserializercarrierp(std::move(adc)),
          outputserializerp(std::move(os)),
          m_checker(std::move(checker)),
          m_protector(std::move(protector)),
          m_methodQueue(f_methodQueue)
    {
        m_transportBind.RegisterMessageHandler(
            std::bind(&MethodExecuterBindingSerialized::On_MethodCall, this, std::placeholders::_1));
    }

    ~MethodExecuterBindingSerialized()
    {
        // If the instance of this class is destroyed we have to set back the message handlers.
        // The mutex/lock structure to ensure that no handler thread is in the instance while it is destroyed
        // is part of Bind_IPC.
        m_transportBind.unRegisterMessageHandler();
    }

    void On_MethodCall(std::shared_ptr<std::vector<uint8_t>> f_p)
    {
        uint32_t serializeStart   = static_cast<uint32_t>(m_protector->getE2EHeaderLength());
        uint32_t deserializeStart = static_cast<uint32_t>(m_checker->getE2EHeaderLength());
        uint32_t dataId{0};
        uint32_t sourceId{0};
        uint32_t message_counter{0};
        E2EResult checkResult = m_checker->check(e2e::MessageType::kRequest,
                                                 e2e::MessageResult::kOk,
                                                 dataId,
                                                 sourceId,
                                                 message_counter,
                                                 f_p->data(),
                                                 f_p->size());

        if (checkResult.checkStatus != E2EProfileCheckStatus::kOk
            && checkResult.checkStatus != E2EProfileCheckStatus::kCheckDisabled)
        {
            m_methodQueue->invokeE2EErrorHandler(checkResult.checkStatus, dataId, message_counter);
            // TODO: serialize and protect the E2E error response
            f_p->resize(0);
            return;
        }

        if (true)
        {
            callerclass<TArgs...> callerc;

            try
            {
                ara::core::Future<MethodOutput_T> f = callerc.callerfunction(m_func_call,
                                                                             deserializeStart,
                                                                             f_p,
                                                                             deserializercarrierp.get());

                ara::core::future_status result = f.wait_for(std::chrono::seconds(60));
                if (result == ara::core::future_status::kReady)
                {
                    MethodOutput_T l_output = f.get();

                    // reuse the vector with input data as output container
                    uint32_t outputsize = outputserializerp->computeSerializedSize(&l_output);
                    f_p->resize(outputsize + serializeStart);
                    bool ok = outputserializerp->serialize((f_p->data() + serializeStart), outputsize, &l_output);
                    static_cast<void>(ok);
                    // TODO: check ok!
                }
                else
                    std::cout << "Warning: Method-Result not ready, reply the input!\n";
            }
            catch (...)
            {
                // temporary solution until serialization available
                // TODO: what to change here?
                MethodOutput_T l_output{};

                // reuse the vector with input data as output container
                uint32_t outputsize = outputserializerp->computeSerializedSize(&l_output);
                f_p->resize(outputsize + serializeStart);
                bool ok = outputserializerp->serialize((f_p->data() + serializeStart), outputsize, &l_output);
                static_cast<void>(ok);
                // TODO: check ok!
            }
        }

        // we have to cut longer messages (this usually corrupts the message), and print an error out for this
        if (f_p->size() > (APP_Q_MSG_SIZE_PAYLOAD))
        {
            f_p->resize(APP_Q_MSG_SIZE_PAYLOAD);
            std::cout << "Method-Message-Reply too long, cut to " << APP_Q_MSG_SIZE_PAYLOAD
                      << " bytes (we cannot handle more)!\n";
            std::cout << "This usually corrupts the message!\n";
        }

        e2e::ProtectStatus protectStatus = m_protector->protect(e2e::MessageType::kResponse,
                                                                e2e::MessageResult::kOk,
                                                                sourceId,
                                                                message_counter,
                                                                f_p->data(),
                                                                f_p->size());
        if (protectStatus != e2e::ProtectStatus::kOk && protectStatus != e2e::ProtectStatus::kProtectDisabled)
        {
            Logger::GetInstance().LogError()
                << "Protect function for method response failed (protectStatus :" << static_cast<uint8_t>(protectStatus)
                << ")";
            f_p->resize(0);
            return;
        }
    }

    void RegisterProcessingFunction(std::function<ara::core::Future<MethodOutput_T>(const TArgs...)>&& f_func) override
    {
        m_func_call = f_func;
    }

private:
    MethodExecuteTransportBinding m_transportBind;
    std::function<ara::core::Future<MethodOutput_T>(const TArgs...)> m_func_call;
    ara::com::UniquePtr<serializer::ArgumentDeserializerCarrier<sizeof...(TArgs), TArgs...>> deserializercarrierp;
    ara::com::UniquePtr<serializer::ISerializer<MethodOutput_T>> outputserializerp;
    UniquePtr<IE2EChecker> m_checker;
    UniquePtr<IE2EProtector> m_protector;
    std::shared_ptr<MethodQueue> m_methodQueue;

    //-------------------------------------------------------------
    // Fast-Fix-Solution, will be replaced
    template<typename... Args>
    class callerclass
    {
    public:
        ara::core::Future<MethodOutput_T> callerfunction(
            std::function<ara::core::Future<MethodOutput_T>(const Args...)> m_func,
            uint64_t offset,
            std::shared_ptr<std::vector<uint8_t>> f_p,
            serializer::ArgumentDeserializerCarrier<sizeof...(Args), Args...>* deserializercarrierp)
        {
            // gets overwritten in the next call, not so nice, will be removed in the next release
            ara::core::Future<MethodOutput_T> result;

            callstackbuilder<sizeof...(Args), true, Args...> cstackbuilder(m_func,
                                                                           offset,
                                                                           result,
                                                                           f_p,
                                                                           deserializercarrierp);
            return result;
        }

    private:
        template<size_t N, bool calllevel, typename... Tss>
        class callstackbuilder;

        template<typename... Tss>
        class callstackbuilder<0, false, Tss...>
        {
        public:
            callstackbuilder(callstackbuilder<1,
                                              (1 == sizeof...(Args)),
                                              typename std::tuple_element<sizeof...(Args) - 1, std::tuple<Args...>>::type,
                                              Tss...>* p_csb,
                             uint64_t,
                             std::shared_ptr<std::vector<uint8_t>>,
                             serializer::ArgumentDeserializerCarrier<0, Tss...>*)
            {
                p_csb->funcin();
            }
        };

        template<typename... Tss>
        class callstackbuilder<0, true, Tss...>
        {
        public:
            callstackbuilder(std::function<ara::core::Future<MethodOutput_T>()> m_func,
                             uint64_t,
                             ara::core::Future<MethodOutput_T>& resref,
                             std::shared_ptr<std::vector<uint8_t>>,
                             serializer::ArgumentDeserializerCarrier<0, Tss...>*)
            {
                resref = m_func();
            }
        };

        template<size_t N, typename T1, typename... Ts>
        class callstackbuilder<N, false, T1, Ts...>
        {
        public:
            callstackbuilder(
                callstackbuilder<N + 1,
                                 ((N + 1) == sizeof...(Args)),
                                 typename std::tuple_element<sizeof...(Args) - N - 1, std::tuple<Args...>>::type,
                                 T1,
                                 Ts...>* p_csb,
                uint64_t offset,
                std::shared_ptr<std::vector<uint8_t>> f_p,
                serializer::ArgumentDeserializerCarrier<N, T1, Ts...>* adcp)
            {
                p_callstackbuilder = p_csb;
                uint32_t readbytes;
                bool ok = (adcp->desp)
                              ->deserialize((f_p->data() + offset),
                                            static_cast<uint32_t>(f_p->size() - offset),
                                            &parametervalue,
                                            &readbytes);
                if (ok)
                    callstackbuilder<N - 1, false, Ts...> cstackbuilder(this, offset + readbytes, f_p, adcp->next.get());
                else
                    std::cout << "Deserialization-Error: Method not called!\n";
            }
            T1 parametervalue;
            callstackbuilder<N + 1,
                             ((N + 1) == sizeof...(Args)),
                             typename std::tuple_element<sizeof...(Args) - N - 1, std::tuple<Args...>>::type,
                             T1,
                             Ts...>* p_callstackbuilder;
            void funcin(Ts&... param)
            {
                p_callstackbuilder->funcin(parametervalue, param...);
            }
        };

        template<typename T1, typename... Ts>
        class callstackbuilder<sizeof...(Args), true, T1, Ts...>
        {
        public:
            callstackbuilder(std::function<ara::core::Future<MethodOutput_T>(const T1, const Ts...)> m_func,
                             uint64_t offset,
                             ara::core::Future<MethodOutput_T>& resref,
                             std::shared_ptr<std::vector<uint8_t>> f_p,
                             serializer::ArgumentDeserializerCarrier<sizeof...(Args), T1, Ts...>* adcp)
                : result(resref)
            {
                func = m_func;
                uint32_t readbytes;
                // TODO: Remove type casts once size_t is in the serializer interface
                bool ok = (adcp->desp)
                              ->deserialize((f_p->data() + offset),
                                            static_cast<uint32_t>(f_p->size() - offset),
                                            &parametervalue,
                                            &readbytes);
                if (ok)
                    callstackbuilder<sizeof...(Args) - 1, false, Ts...> cstackbuilder(this,
                                                                                      offset + readbytes,
                                                                                      f_p,
                                                                                      adcp->next.get());
                else
                    std::cout << "Deserialization-Error: Method not called!\n";
            }
            std::function<ara::core::Future<MethodOutput_T>(T1, Ts...)> func;
            T1 parametervalue;
            ara::core::Future<MethodOutput_T>& result;
            void funcin(Ts&... param)
            {
                result = func(parametervalue, param...);
            }
        };
    };
};

} // namespace binding
} // namespace com

#endif // COM_BINDING_METHOD_EXECUTER_BINDING_SERIALIZED_HPP
