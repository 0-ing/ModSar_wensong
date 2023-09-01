/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_BINDING_CALLERCLASSFIREFORGETSERIALIZED_HPP
#define COM_BINDING_CALLERCLASSFIREFORGETSERIALIZED_HPP

#include "SerializedSample.hpp"
#include "serializer/ArgumentDeserializerCarrier.hpp"

#include <functional>
#include <iostream>

namespace com
{
namespace binding
{
/**
 * @brief Helper class for deserialization & apply within a FF method.
 *
 * @todo
 * Replace with DeserialierRefPack & Apply pattern later.
 */
template<typename... Args>
class CallerClassFireForgetSerialized
{
public:
    void callerfunction(std::function<void(const Args...)> m_func,
                        uint64_t offset,
                        const binding::SerializedSample& serializedSample,
                        serializer::ArgumentDeserializerCarrier<sizeof...(Args), Args...>* deserializercarrierp)
    {
        callstackbuilder<sizeof...(Args), true, Args...> cstackbuilder(m_func,
                                                                       offset,
                                                                       serializedSample,
                                                                       deserializercarrierp);
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
                         const binding::SerializedSample&,
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
                         const binding::SerializedSample&,
                         serializer::ArgumentDeserializerCarrier<0, Tss...>*)
        {
            m_func();
        }
    };

    template<size_t N, typename T1, typename... Ts>
    class callstackbuilder<N, false, T1, Ts...>
    {
    public:
        callstackbuilder(callstackbuilder<N + 1,
                                          ((N + 1) == sizeof...(Args)),
                                          typename std::tuple_element<sizeof...(Args) - N - 1, std::tuple<Args...>>::type,
                                          T1,
                                          Ts...>* p_csb,
                         uint64_t offset,
                         const binding::SerializedSample& serializedSample,
                         serializer::ArgumentDeserializerCarrier<N, T1, Ts...>* adcp)
        {
            p_callstackbuilder = p_csb;
            uint32_t readbytes;
            // TODO: Remove type casts once the interface has size_t
            bool ok = (adcp->desp)
                          ->deserialize((serializedSample.data() + offset),
                                        static_cast<uint32_t>(serializedSample.size() - offset),
                                        &parametervalue,
                                        &readbytes);
            if (ok)
                callstackbuilder<N - 1, false, Ts...> cstackbuilder(this,
                                                                    offset + readbytes,
                                                                    serializedSample,
                                                                    adcp->next.get());
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
                         const binding::SerializedSample& serializedSample,
                         serializer::ArgumentDeserializerCarrier<sizeof...(Args), T1, Ts...>* adcp)
        {
            func = m_func;
            uint32_t readbytes;
            // TODO: Remove type casts once the interface has size_t
            bool ok = (adcp->desp)
                          ->deserialize((serializedSample.data() + offset),
                                        static_cast<uint32_t>(serializedSample.size() - offset),
                                        &parametervalue,
                                        &readbytes);
            if (ok)
                callstackbuilder<sizeof...(Args) - 1, false, Ts...> cstackbuilder(this,
                                                                                  offset + readbytes,
                                                                                  serializedSample,
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

} // namespace binding
} // namespace com

#endif // COM_BINDING_CALLERCLASSFIREFORGETSERIALIZED_HPP
