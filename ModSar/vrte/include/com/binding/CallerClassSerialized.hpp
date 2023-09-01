/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_BINDING_CALLERCLASSSERIALIZED_HPP
#define COM_BINDING_CALLERCLASSSERIALIZED_HPP

#include "SerializedSample.hpp"
#include "serializer/ArgumentDeserializerCarrier.hpp"

#include <functional>

namespace com
{
namespace binding
{
//-------------------------------------------------------------
// Fast-Fix-Solution, will be replaced
template<typename MethodOutput_T, typename... Args>
class CallerClassSerialized
{
public:
    ara::core::Future<MethodOutput_T> callerfunction(
        std::function<ara::core::Future<MethodOutput_T>(const Args...)> m_func,
        uint64_t offset,
        const binding::SerializedSample& serializedSample,
        serializer::ArgumentDeserializerCarrier<sizeof...(Args), Args...>* deserializercarrierp)
    {
        // gets overwritten in the next call, not so nice, will be removed in the next release
        ara::core::Future<MethodOutput_T> result;

        callstackbuilder<sizeof...(Args), true, Args...> cstackbuilder(m_func, offset, result, serializedSample, deserializercarrierp);
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
        callstackbuilder(std::function<ara::core::Future<MethodOutput_T>()> m_func,
                         uint64_t,
                         ara::core::Future<MethodOutput_T>& resref,
                         const binding::SerializedSample&,
                         serializer::ArgumentDeserializerCarrier<0, Tss...>*)
        {
            resref = m_func();
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
                         const binding::SerializedSample& f_p,
                         serializer::ArgumentDeserializerCarrier<N, T1, Ts...>* adcp)
        {
            p_callstackbuilder = p_csb;
            uint32_t readbytes;
            bool ok = (adcp->desp)
                          ->deserialize((f_p.data() + offset),
                                        static_cast<uint32_t>(f_p.size() - offset),
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
                         const binding::SerializedSample& f_p,
                         serializer::ArgumentDeserializerCarrier<sizeof...(Args), T1, Ts...>* adcp)
            : result(resref)
        {
            func = m_func;
            uint32_t readbytes;
            // TODO: Remove type casts once size_t is in the serializer interface
            bool ok = (adcp->desp)
                          ->deserialize((f_p.data() + offset),
                                        static_cast<uint32_t>(f_p.size() - offset),
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

} // namespace binding
} // namespace com

#endif // COM_BINDING_CALLERCLASSSERIALIZED_HPP
