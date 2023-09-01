#ifndef COM_BINDING_METHOD_EXECUTER_BINDING_HPP
#define COM_BINDING_METHOD_EXECUTER_BINDING_HPP

#include "ara/com/ISkeletonMethod.hpp"
#include "ara/com/types.h"
#include "ara/core/future.h"
#include "ara/core/promise.h"
#include "binding/MethodQueue.hpp"
#include "method_transport_binding.hpp"

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
/**
 * \brief MethodExecuterBindingFireForget class specialization of the MethodExecuterType.
 */
template<typename... TArgs>
class MethodExecuterBindingFireForget : public ara::com::ISkeletonMethodFireForget<TArgs...>
{
public:
    /*
     * \brief MethodExecuterBindingFireForget constructor
     *
     * \param Service, Instance, Method. Temporarly SomeIp mapping is added as uint16 values.
     * For the future use, SomeIp mapping should be removed.
     */
    MethodExecuterBindingFireForget(const ServiceIdentifier_& f_service,
                                    const InstanceIdentifier_& f_instance,
                                    const MethodIdentifier_& f_method,
                                    // temporary maping Text to SomeIpValues
                                    const SIpServiceIdentifier_& f_sIpService,
                                    const SIpInstanceIdentifier_& f_sIpInstance,
                                    const SIpMethodIdentifier_& f_sIpMethod,
                                    const std::shared_ptr<MethodQueue>& f_methodQueue)
        : m_transportBind(f_service, f_instance, f_method, f_sIpService, f_sIpInstance, f_sIpMethod, f_methodQueue)
    {
        m_transportBind.RegisterMessageHandler(
            std::bind(&MethodExecuterBindingFireForget::On_MethodCall, this, std::placeholders::_1));
    }

    ~MethodExecuterBindingFireForget()
    {
        // If the instance of this class is destroyed we have to set back the message handlers.
        // The mutex/lock structure to ensure that no handler thread is in the instance while it is destroyed
        // is part of Bind_IPC.
        m_transportBind.unRegisterMessageHandler();
    }

    void On_MethodCall(std::shared_ptr<std::vector<uint8_t>> f_p)
    {
        // m_func_call();

        if (sizeof(m_params) <= f_p->size())
        {
            callerclass<TArgs...> callerc;
            callerc.callerfunction(m_func_call, f_p);
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

    std::tuple<TArgs...> m_params;

    //-------------------------------------------------------------
    // Fast-Fix-Solution, will be replaced

    template<typename... Args>
    class callerclass
    {
    public:
        void callerfunction(std::function<void(const Args...)> m_func, std::shared_ptr<std::vector<uint8_t>> f_p)
        {
            callstackbuilder<sizeof...(Args), true, Args...> cstackbuilder(m_func, 0, f_p);
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
                             uint64_t offset,
                             std::shared_ptr<std::vector<uint8_t>> f_p)
            {
                p_csb->funcin();
            }
        };

        template<typename... Tss>
        class callstackbuilder<0, true, Tss...>
        {
        public:
            callstackbuilder(std::function<void()> m_func, uint64_t offset, std::shared_ptr<std::vector<uint8_t>> f_p)
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
                std::shared_ptr<std::vector<uint8_t>> f_p)
            {
                p_callstackbuilder = p_csb;
                memcpy(&parametervalue, (f_p->data() + offset), sizeof(T1));
                callstackbuilder<N - 1, false, Ts...> cstackbuilder(this, offset + sizeof(T1), f_p);
            }
            T1 parametervalue;
            callstackbuilder<N + 1,
                             ((N + 1) == sizeof...(Args)),
                             typename std::tuple_element<sizeof...(Args) - N - 1, std::tuple<Args...>>::type,
                             T1,
                             Ts...>* p_callstackbuilder;
            void funcin(Ts... param)
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
                             std::shared_ptr<std::vector<uint8_t>> f_p)
            {
                func = m_func;
                memcpy(&parametervalue, (f_p->data() + offset), sizeof(T1));
                callstackbuilder<sizeof...(Args) - 1, false, Ts...> cstackbuilder(this, offset + sizeof(T1), f_p);
            }
            std::function<void(T1, Ts...)> func;
            T1 parametervalue;
            void funcin(Ts... param)
            {
                func(parametervalue, param...);
            }
        };
    };
};

/**
 * \brief MethodExecuteBinding template definition of the MethodExecuterType with
 * one result and variadic number of params.
 */
template<typename... TArgs>
class MethodExecuterBinding;

template<typename MethodOutput_T, typename... TArgs>
class MethodExecuterBinding<MethodOutput_T, TArgs...> : public ara::com::ISkeletonMethod<MethodOutput_T, TArgs...>
{
public:
    /*
     * \brief MethodExecuterBinding constructor
     *
     * \param Service, Instance, Method. Temporarly SomeIp mapping is added as uint16 values.
     * For the future use, SomeIp mapping should be removed.
     */
    MethodExecuterBinding(const ServiceIdentifier_& f_service,
                          const InstanceIdentifier_& f_instance,
                          const MethodIdentifier_& f_method,
                          // temporary maping Text to SomeIpValues
                          const SIpServiceIdentifier_& f_sIpService,
                          const SIpInstanceIdentifier_& f_sIpInstance,
                          const SIpMethodIdentifier_& f_sIpMethod,
                          const std::shared_ptr<MethodQueue>& f_methodQueue)
        : m_transportBind(f_service, f_instance, f_method, f_sIpService, f_sIpInstance, f_sIpMethod, f_methodQueue)
    {
        m_transportBind.RegisterMessageHandler(

            std::bind(&MethodExecuterBinding::On_MethodCall, this, std::placeholders::_1));
    }

    ~MethodExecuterBinding()
    {
        // If the instance of this class is destroyed we have to set back the message handlers.
        // The mutex/lock structure to ensure that no handler thread is in the instance while it is destroyed
        // is part of Bind_IPC.
        m_transportBind.unRegisterMessageHandler();
    }

    void On_MethodCall(std::shared_ptr<std::vector<uint8_t>> f_p)
    {
        if (sizeof(m_params) <= f_p->size())
        {
            callerclass<TArgs...> callerc;

            try
            {
                ara::core::Future<MethodOutput_T> f = callerc.callerfunction(m_func_call, f_p);

                ara::core::future_status result = f.wait_for(std::chrono::seconds(60));
                if (result == ara::core::future_status::kReady)
                {
                    MethodOutput_T l_output = f.get();

                    uint8_t* l_ptr = reinterpret_cast<uint8_t*>(&l_output);

                    // reuse the vector with input data as output container
                    f_p->clear();

                    for (int i = 0; i < (int)sizeof(MethodOutput_T); i++)
                    {
                        f_p->push_back(l_ptr[i]);
                    }
                }
            }
            catch (...)
            {
                // temporary solution until serialization available
                MethodOutput_T l_output{};

                f_p->clear();

                uint8_t* l_ptr = reinterpret_cast<uint8_t*>(&l_output);

                for (int i = 0; i < (int)sizeof(MethodOutput_T); i++)
                {
                    f_p->push_back(l_ptr[i]);
                }
            }
        }
    }

    void RegisterProcessingFunction(std::function<ara::core::Future<MethodOutput_T>(const TArgs...)>&& f_func) override
    {
        m_func_call = f_func;
    }

private:
    MethodExecuteTransportBinding m_transportBind;
    std::function<ara::core::Future<MethodOutput_T>(const TArgs...)> m_func_call;
    std::tuple<TArgs...> m_params;

    //-------------------------------------------------------------
    // Fast-Fix-Solution, will be replaced

    template<typename... Args>
    class callerclass
    {
    public:
        ara::core::Future<MethodOutput_T> callerfunction(
            std::function<ara::core::Future<MethodOutput_T>(const Args...)> m_func,
            std::shared_ptr<std::vector<uint8_t>> f_p)
        {
            // gets overwritten in the next call, not so nice, will be removed in the next release
            ara::core::Future<MethodOutput_T> result;

            callstackbuilder<sizeof...(Args), true, Args...> cstackbuilder(m_func, 0, result, f_p);
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
                             uint64_t offset,
                             std::shared_ptr<std::vector<uint8_t>> f_p)
            {
                p_csb->funcin();
            }
        };

        template<typename... Tss>
        class callstackbuilder<0, true, Tss...>
        {
        public:
            callstackbuilder(std::function<ara::core::Future<MethodOutput_T>()> m_func,
                             uint64_t offset,
                             ara::core::Future<MethodOutput_T>& resref,
                             std::shared_ptr<std::vector<uint8_t>> f_p)
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
                std::shared_ptr<std::vector<uint8_t>> f_p)
            {
                p_callstackbuilder = p_csb;
                memcpy(&parametervalue, (f_p->data() + offset), sizeof(T1));
                callstackbuilder<N - 1, false, Ts...> cstackbuilder(this, offset + sizeof(T1), f_p);
            }
            T1 parametervalue;
            callstackbuilder<N + 1,
                             ((N + 1) == sizeof...(Args)),
                             typename std::tuple_element<sizeof...(Args) - N - 1, std::tuple<Args...>>::type,
                             T1,
                             Ts...>* p_callstackbuilder;
            void funcin(Ts... param)
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
                             std::shared_ptr<std::vector<uint8_t>> f_p)
                : result(resref)
            {
                func = m_func;
                memcpy(&parametervalue, (f_p->data() + offset), sizeof(T1));
                callstackbuilder<sizeof...(Args) - 1, false, Ts...> cstackbuilder(this, offset + sizeof(T1), f_p);
            }
            std::function<ara::core::Future<MethodOutput_T>(T1, Ts...)> func;
            T1 parametervalue;
            ara::core::Future<MethodOutput_T>& result;
            void funcin(Ts... param)
            {
                result = func(parametervalue, param...);
            }
        };
    };
};

} // namespace binding
} // namespace com

#endif // COM_BINDING_METHOD_EXECUTER_BINDING_HPP
