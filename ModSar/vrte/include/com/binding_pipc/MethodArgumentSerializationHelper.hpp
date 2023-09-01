/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_BINDING_PIPC_METHOD_ARGUMENT_SERIALIZATION_HELPER_HPP
#define COM_BINDING_PIPC_METHOD_ARGUMENT_SERIALIZATION_HELPER_HPP

#include "serializer/ArgumentSerializerCarrier.hpp"
#include "serializer/IDeserializer.hpp"
#include "serializer/ISerializer.hpp"

namespace com
{
namespace binding_pipc
{
template<std::size_t NArgs, std::size_t N, typename... Args>
class MethodArgumentSerializationHelper;

template<std::size_t NArgs, std::size_t N, typename T1, typename... Args>
class MethodArgumentSerializationHelper<NArgs, N, T1, Args...>
{
public:
    static inline uint32_t calculateSize(uint32_t* sizes,
                                         serializer::ArgumentSerializerCarrier<N, T1, Args...>* asc,
                                         const T1& arg1,
                                         const Args&... args)
    {
        uint32_t localsize = (asc->serp)->computeSerializedSize(&arg1);
        sizes[NArgs - N]   = localsize;

        MethodArgumentSerializationHelper<NArgs, N - 1, Args...> fc;
        localsize += fc.calculateSize(sizes, asc->next.get(), args...);
        return localsize;
    }
    // functions for the actual serialization:
    static bool serializeArguments(uint8_t* targetbuffer,
                                   uint32_t offset,
                                   uint32_t* sizes,
                                   serializer::ArgumentSerializerCarrier<N, T1, Args...>* asc,
                                   const T1& arg1,
                                   const Args&... args)
    {
        bool ok = (asc->serp)->serialize(targetbuffer + offset, sizes[NArgs - N], &arg1);
        if (!ok)
        {
            return false;
        }
        MethodArgumentSerializationHelper<NArgs, N - 1, Args...> fc;
        return fc.serializeArguments(targetbuffer, offset + sizes[NArgs - N], sizes, asc->next.get(), args...);
    }
};

template<std::size_t NArgs, typename... Args>
class MethodArgumentSerializationHelper<NArgs, 0, Args...>
{ // only needed for partial specialization
public:
    static uint32_t inline calculateSize(uint32_t*,
                                         serializer::ArgumentSerializerCarrier<sizeof...(Args), Args...>*,
                                         Args&... args)
    {
        return 0;
    }
    static bool serializeArguments(uint8_t*,
                                   uint32_t,
                                   uint32_t*,
                                   serializer::ArgumentSerializerCarrier<sizeof...(Args), Args...>*,
                                   Args&... args)
    {
        // do nothing, maybe add some asserts
        return true;
    }
};

} // namespace binding_pipc
} // namespace com

#endif // COM_BINDING_PIPC_METHOD_ARGUMENT_SERIALIZATION_HELPER_HPP
