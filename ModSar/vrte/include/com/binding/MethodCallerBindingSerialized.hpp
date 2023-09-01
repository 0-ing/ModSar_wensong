//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

#ifndef COM_BINDING_METHODCALLERBINDINGSERIALIZED_HPP
#define COM_BINDING_METHODCALLERBINDINGSERIALIZED_HPP

#include "ara/com/IProxyMethod.hpp"
#include "ara/com/IProxyMethodFireForget.hpp"
#include "ara/com/com_error_domain.h"
#include "ara/com/method_settings.hpp"
#include "ara/com/types.h"
#include "ara/core/future.h"
#include "ara/core/promise.h"
#include "e2e/IE2EChecker.hpp"
#include "e2e/IE2EProtector.hpp"
#include "method_transport_binding.hpp"
#include "serializer/ArgumentSerializerCarrier.hpp"
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
template<std::size_t NumArgs>
class MethodCallerBindingSerializedBase
{
public:
    MethodCallerBindingSerializedBase()
    {
    }

    ~MethodCallerBindingSerializedBase()
    {
    }

protected:
    template<std::size_t N, typename... Args>
    class functioncarrier;

    template<std::size_t N, typename T1, typename... Args>
    class functioncarrier<N, T1, Args...>
    { // only needed for partial specialization
      // functions for the size calculation:
    public:
        void calculatesize(uint32_t* sizes,
                           serializer::ArgumentSerializerCarrier<N, T1, Args...>* asc,
                           const T1& arg1,
                           const Args&... args)
        {
            sizes[NumArgs - N] = (asc->serp)->computeSerializedSize(&arg1);
            functioncarrier<N - 1, Args...> fc;
            fc.calculatesize(sizes, asc->next.get(), args...);
        }
        // functions for the actual serialization:
        void serializearguments(uint8_t* targetbuffer,
                                uint32_t offset,
                                uint32_t* sizes,
                                serializer::ArgumentSerializerCarrier<N, T1, Args...>* asc,
                                const T1& arg1,
                                const Args&... args)
        {
            bool ok = (asc->serp)->serialize(targetbuffer + offset, sizes[NumArgs - N], &arg1);
            // TODO: check ok!!
            static_cast<void>(ok);
            functioncarrier<N - 1, Args...> fc;
            fc.serializearguments(targetbuffer, offset + sizes[NumArgs - N], sizes, asc->next.get(), args...);
        }
    };

    template<typename... Args>
    class functioncarrier<0, Args...>
    { // only needed for partial specialization
    public:
        void calculatesize(uint32_t*, serializer::ArgumentSerializerCarrier<sizeof...(Args), Args...>*, Args&... args)
        {
            // do nothing, maybe add some asserts
        }
        void serializearguments(uint8_t*,
                                uint32_t,
                                uint32_t*,
                                serializer::ArgumentSerializerCarrier<sizeof...(Args), Args...>*,
                                Args&... args)
        {
            // do nothing, maybe add some asserts
        }
    };
};
template<typename... TArgs>
class MethodCallerBindingFireForgetSerialized;

template<typename... TArgs>
class MethodCallerBindingFireForgetSerialized : public ara::com::IProxyMethodFireForget<TArgs...>,
                                                public MethodCallerBindingSerializedBase<sizeof...(TArgs)>
{
public:
    /** \brief Declarations for readability and forwarding to derived classes */
    template<typename T>
    using UniquePtr               = ara::com::UniquePtr<T>;
    using ComErrc                 = ara::com::ComErrc;
    using MethodCfgSomeIp         = ::com::config::MethodCfgSomeIp;
    using DeploymentContextSomeIp = ::com::config::DeploymentContextSomeIp;
    using MethodCfgIpc            = ::com::config::MethodCfgIpc;
    using DeploymentContextIpc    = ::com::config::DeploymentContextIpc;
    using IE2EProtector           = ::com::e2e::IE2EProtector;
    using Logger                  = com::someip::Logger;

    /** \brief Constructor for a IPC deployment configuration */
    MethodCallerBindingFireForgetSerialized(
        const MethodCfgIpc& config,
        const DeploymentContextIpc& context,
        UniquePtr<serializer::ArgumentSerializerCarrier<sizeof...(TArgs), TArgs...>>&& asc,
        UniquePtr<IE2EProtector>&& protector)
        : MethodCallerBindingSerializedBase<sizeof...(TArgs)>(),
          m_impl(config, context),
          serializercarrierp(std::move(asc)),
          m_protector(std::move(protector))
    {
        // Handler registration also registers method at GW so it is even needed when we do not expect a reply
        m_impl.RegisterMessageHandler(std::bind(&MethodCallerBindingFireForgetSerialized::On_Callback, this), true);
    }

    /** \brief Constructor for a SOME/IP deployment configuration */
    MethodCallerBindingFireForgetSerialized(
        const MethodCfgSomeIp& config,
        const DeploymentContextSomeIp& context,
        UniquePtr<serializer::ArgumentSerializerCarrier<sizeof...(TArgs), TArgs...>>&& asc,
        UniquePtr<IE2EProtector>&& protector)
        : MethodCallerBindingSerializedBase<sizeof...(TArgs)>(),
          m_impl(config, context),
          serializercarrierp(std::move(asc)),
          m_protector(std::move(protector))
    {
        // Handler registration also registers method at GW so it is even needed when we do not expect a reply
        m_impl.RegisterMessageHandler(std::bind(&MethodCallerBindingFireForgetSerialized::On_Callback, this), true);
    }

    ~MethodCallerBindingFireForgetSerialized()
    {
        // If the instance of this class is destroyed we have to set back the message handlers.
        // The mutex/lock structure to ensure that no handler thread is in the instance while it is destroyed
        //  is part of Bind_IPC.
        m_impl.unRegisterMessageHandler();
    }

    void operator()(const TArgs... args)
    {
        // calculate the serialized size of the arguments:
        uint32_t argumentsizes[sizeof...(TArgs)];
        typename MethodCallerBindingSerializedBase<sizeof...(TArgs)>::template functioncarrier<sizeof...(TArgs), TArgs...>
            fc;
        fc.calculatesize(argumentsizes, serializercarrierp.get(), args...);

        uint32_t serializeStart = static_cast<uint32_t>(m_protector->getE2EHeaderLength());
        uint32_t totalsize      = serializeStart;
        for (uint32_t i = 0; i < (sizeof...(TArgs)); i++)
            totalsize += argumentsizes[i];

        // TODO: shared pointer here seems to be useless
        std::shared_ptr<std::vector<uint8_t>> vec = std::make_shared<std::vector<uint8_t>>(totalsize);

        fc.serializearguments((vec->data() + serializeStart), 0, argumentsizes, serializercarrierp.get(), args...);

        // we have to cut longer messages (this usually corrupts the message), and print an error out for this
        if (totalsize > (APP_Q_MSG_SIZE_PAYLOAD))
        {
            vec->resize(APP_Q_MSG_SIZE_PAYLOAD);
            std::cout << "Method-Message too long, cut to " << APP_Q_MSG_SIZE_PAYLOAD
                      << " bytes (we cannot handle more)!\n";
            std::cout << "This usually corrupts the message!\n";
        }

        // The method will be sent only if protect function worked ok or if there is no profile configuration
        uint32_t e2eCounter{0};
        e2e::ProtectStatus protectStatus = m_protector->protect(e2e::MessageType::kRequest,
                                                                e2e::MessageResult::kOk,
                                                                e2eCounter,
                                                                vec->data(),
                                                                vec->size());
        if (protectStatus == e2e::ProtectStatus::kOk || protectStatus == e2e::ProtectStatus::kProtectDisabled)
        {
            m_impl.DoMethodCall(vec->data(), vec->size(), (uint16_t)0);
            // no session handling here, so sessionID is set to 0
        }
        else
        {
            Logger::GetInstance().LogError() << "Protect function for method fire and forget failed (protectStatus :"
                                             << static_cast<uint8_t>(protectStatus) << ")";
        }
    }

    void On_Callback(void)
    {
    }

private:
    MethodCallTransportBinding m_impl;
    UniquePtr<serializer::ArgumentSerializerCarrier<sizeof...(TArgs), TArgs...>> serializercarrierp;
    UniquePtr<IE2EProtector> m_protector;
};

template<typename... TArgs>
class MethodCallerBindingSerialized;

template<typename MethodOutput_T, typename... TArgs>
class MethodCallerBindingSerialized<MethodOutput_T, TArgs...>
    : public ara::com::IProxyMethod<MethodOutput_T, TArgs...>,
      public MethodCallerBindingSerializedBase<sizeof...(TArgs)>
{
public:
    template<typename T>
    struct SessionInfo
    {
        ara::core::Promise<T> promise;
        uint32_t e2e_counter;
    };

    /** \brief Declarations for readability and forwarding to derived classes */
    template<typename T>
    using UniquePtr               = ara::com::UniquePtr<T>;
    using ComErrc                 = ara::com::ComErrc;
    using MethodCfgSomeIp         = ::com::config::MethodCfgSomeIp;
    using DeploymentContextSomeIp = ::com::config::DeploymentContextSomeIp;
    using MethodCfgIpc            = ::com::config::MethodCfgIpc;
    using DeploymentContextIpc    = ::com::config::DeploymentContextIpc;
    using IE2EChecker             = ::com::e2e::IE2EChecker;
    using IE2EProtector           = ::com::e2e::IE2EProtector;
    using e2eResult               = ara::com::e2e::Result;
    using E2ESMState              = ara::com::e2e::SMState;
    using E2EProfileCheckStatus   = ara::com::e2e::ProfileCheckStatus;
    using E2EErrc                 = ara::com::e2e::E2EErrc;
    using Logger                  = com::someip::Logger;

    /** \brief Constructor for a IPC deployment configuration */
    MethodCallerBindingSerialized(const MethodCfgIpc& config,
                                  const DeploymentContextIpc& context,
                                  UniquePtr<serializer::ArgumentSerializerCarrier<sizeof...(TArgs), TArgs...>>&& asc,
                                  UniquePtr<::com::serializer::IDeserializer<MethodOutput_T>>&& od,
                                  UniquePtr<IE2EProtector>&& protector,
                                  UniquePtr<IE2EChecker>&& checker)
        : MethodCallerBindingSerializedBase<sizeof...(TArgs)>(),
          m_impl(config, context),
          serializercarrierp(std::move(asc)),
          outputdeserializerp(std::move(od)),
          m_protector(std::move(protector)),
          m_checker(std::move(checker)),
          session_id(0U)
    {
        m_impl.RegisterMessageHandler(std::bind(&MethodCallerBindingSerialized::On_Callback,
                                                this,
                                                std::placeholders::_1,
                                                std::placeholders::_2),
                                      false);
        if (m_checker->getE2EHeaderLength() == 0U)
        {
            m_smState = E2ESMState::kStateMDisabled;
        }
    }

    /** \brief Constructor for a SOME/IP deployment configuration */
    MethodCallerBindingSerialized(const MethodCfgSomeIp& config,
                                  const DeploymentContextSomeIp& context,
                                  UniquePtr<serializer::ArgumentSerializerCarrier<sizeof...(TArgs), TArgs...>>&& asc,
                                  UniquePtr<::com::serializer::IDeserializer<MethodOutput_T>>&& od,
                                  UniquePtr<IE2EProtector>&& protector,
                                  UniquePtr<IE2EChecker>&& checker)
        : MethodCallerBindingSerializedBase<sizeof...(TArgs)>(),
          m_impl(config, context),
          serializercarrierp(std::move(asc)),
          outputdeserializerp(std::move(od)),
          m_protector(std::move(protector)),
          m_checker(std::move(checker)),
          session_id(0U)
    {
        m_impl.RegisterMessageHandler(std::bind(&MethodCallerBindingSerialized::On_Callback,
                                                this,
                                                std::placeholders::_1,
                                                std::placeholders::_2),
                                      false);
        if (m_checker->getE2EHeaderLength() == 0U)
        {
            m_smState = E2ESMState::kStateMDisabled;
        }
    }

    ~MethodCallerBindingSerialized()
    {
        // If the instance of this class is destroyed we have to set back the message handlers.
        // The mutex/lock structure to ensure that no handler thread is in the instance while it is destroyed
        //  is part of Bind_IPC.
        m_impl.unRegisterMessageHandler();
    }

    void On_Callback(std::shared_ptr<std::vector<uint8_t>> f_p, uint16_t f_session)
    {
        static_assert(!std::is_polymorphic<MethodOutput_T>::value, "Polymorphic MethodOutput types not supported");
        // gcc 4.8 still does not implement it
        // static_assert(std::is_trivially_copyable<MethodInput>::value, "MethodInput must be trivially copyable");

        MethodOutput_T l_output{};

        bool is_pair_found = false;

        std::unique_lock<std::mutex> lk(m_session_map_mutex);
        auto found_pair = m_session_map.find(f_session);
        if (m_session_map.end() != found_pair)
        {
            is_pair_found = true;
        }
        lk.unlock();

        if (is_pair_found)
        {
            uint32_t serializeStart = static_cast<uint32_t>(m_checker->getE2EHeaderLength());
            e2eResult checkResult   = m_checker->check(e2e::MessageType::kResponse,
                                                     e2e::MessageResult::kOk,
                                                     found_pair->second.e2e_counter,
                                                     f_p->data(),
                                                     f_p->size());

            m_smState = checkResult.smStatus;

            switch (checkResult.checkStatus)
            {
            case E2EProfileCheckStatus::kOk:
            case E2EProfileCheckStatus::kCheckDisabled:
                uint32_t readbytes;
                // TODO: Remove typecast once interface is clean
                if (outputdeserializerp->deserialize((f_p->data() + serializeStart),
                                                     (static_cast<uint32_t>(f_p->size()) - serializeStart),
                                                     &l_output,
                                                     &readbytes))
                {
                    found_pair->second.promise.set_value(l_output);
                }
                break;

            case E2EProfileCheckStatus::kRepeated:
            case E2EProfileCheckStatus::kWrongSequence:
                // [SWS_CM_10465] discarded without any further processing
                break;

            case E2EProfileCheckStatus::kError:
                found_pair->second.promise.SetError(E2EErrc::kError);
                break;
            case E2EProfileCheckStatus::kNotAvailable:
                found_pair->second.promise.SetError(E2EErrc::kNotAvailable);
                break;
            case E2EProfileCheckStatus::kNoNewData:
                found_pair->second.promise.SetError(E2EErrc::kNoNewData);
                break;

            default:
                // not reach here
                break;
            }
        }
        else
        {
            // INFO_PRINTF("On_Callback did not found session: %d\n", f_session);
        }

        if (is_pair_found)
        {
            lk.lock();
            m_session_map.erase(found_pair);
            lk.unlock();
        }
    }

    ara::core::Future<MethodOutput_T> operator()(const TArgs... args)
    {
        // this method must not be called in parallel, the protection of the session map is only done
        //  to protect it from concurrent access by the caller and the callback
        // TODO: check this and enable parallel calls (check also behind the bind_interface)

        SessionInfo<MethodOutput_T> session_info;

        ara::core::Future<MethodOutput_T> f = session_info.promise.get_future();

        // calculate the serialized size of the arguments:
        uint32_t argumentsizes[sizeof...(TArgs)];
        typename MethodCallerBindingSerializedBase<sizeof...(TArgs)>::template functioncarrier<sizeof...(TArgs), TArgs...>
            fc;
        fc.calculatesize(argumentsizes, serializercarrierp.get(), args...);

        uint32_t serializeStart = static_cast<uint32_t>(m_protector->getE2EHeaderLength());
        uint32_t totalsize      = serializeStart;
        for (uint32_t i = 0; i < (sizeof...(TArgs)); i++)
            totalsize += argumentsizes[i];

        // TODO: shared pointer here seems to be useless
        std::shared_ptr<std::vector<uint8_t>> vec = std::make_shared<std::vector<uint8_t>>(totalsize);

        fc.serializearguments((vec->data() + serializeStart), 0, argumentsizes, serializercarrierp.get(), args...);

        // we have to cut longer messages (this usually corrupts the message), and print an error out for this
        if (totalsize > (APP_Q_MSG_SIZE_PAYLOAD))
        {
            vec->resize(APP_Q_MSG_SIZE_PAYLOAD);
            std::cout << "Method-Message too long, cut to " << APP_Q_MSG_SIZE_PAYLOAD
                      << " bytes (we cannot handle more)!\n";
            std::cout << "This usually corrupts the message!\n";
        }

        // The method will be sent only if protect function worked ok or if there is no profile configuration
        e2e::ProtectStatus protectStatus = m_protector->protect(e2e::MessageType::kRequest,
                                                                e2e::MessageResult::kOk,
                                                                session_info.e2e_counter,
                                                                vec->data(),
                                                                vec->size());
        if (protectStatus == e2e::ProtectStatus::kOk || protectStatus == e2e::ProtectStatus::kProtectDisabled)
        {
            uint16_t l_session = getNextSessionId();
            {
                std::unique_lock<std::mutex> lk(m_session_map_mutex);
                m_session_map.insert(std::make_pair(l_session, std::move(session_info)));
            }

            uint16_t send_success = m_impl.DoMethodCall(vec->data(), vec->size(), l_session);
            // the return value is 0 in case the data could not be sent and a positive number (sessionID) otherwise

            {
                // TODO check that unique_lock is RAII
                std::unique_lock<std::mutex> lk(m_session_map_mutex);
                if (send_success == 0)
                {
                    auto found_session = m_session_map.find(l_session);
                    if (m_session_map.end() != found_session)
                    {
                        // no transmission has occured, set Output to 0-default
                        found_session->second.promise.set_value(MethodOutput_T{});
                        m_session_map.erase(found_session);
                    }
                }
            }
        }
        else
        {
            Logger::GetInstance().LogError()
                << "Protect function for method request failed (protectStatus :" << static_cast<uint8_t>(protectStatus)
                << ")";
            session_info.promise.SetError(ComErrc::kCommunicationStackError);
        }

        return f;
    }

    E2ESMState GetSMState() const noexcept override
    {
        return m_smState;
    }

private:
    // we do not use session 0 because we get the sessionID back from DoMethodCall
    //  also due to specification the sessionID cannot be 0 in this case
    uint16_t getNextSessionId()
    {
        std::unique_lock<std::mutex> lk(session_mutex);
        session_id++;
        // Overflow handling
        if (session_id == 0U)
        {
            session_id++;
        }

        return session_id;
    }
    MethodCallTransportBinding m_impl;
    UniquePtr<serializer::ArgumentSerializerCarrier<sizeof...(TArgs), TArgs...>> serializercarrierp;
    UniquePtr<::com::serializer::IDeserializer<MethodOutput_T>> outputdeserializerp;
    UniquePtr<IE2EProtector> m_protector;
    UniquePtr<IE2EChecker> m_checker;

    std::map<uint16_t, SessionInfo<MethodOutput_T>> m_session_map; // value are Promise and E2E counter
    std::mutex m_session_map_mutex;                                // used to protect the session map
    uint16_t session_id;
    std::mutex session_mutex; // protect the session id calculation
    E2ESMState m_smState{E2ESMState::kNoData};
};

} // namespace binding
} // namespace com

#endif // COM_BINDING_METHODCALLERBINDINGSERIALIZED_HPP
