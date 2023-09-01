#ifndef PIPC_PROTOCOL_MESSAGE_HPP
#define PIPC_PROTOCOL_MESSAGE_HPP

#include "pipc/utils/Placeholder.hpp"
#include "pipc/utils/Variadic.hpp"

// #include <iostream>

namespace pipc
{
namespace protocol
{
/** @brief Empty placeholder. */
using Placeholder = utils::Placeholder;

namespace internal
{
/** @brief Forward declarations for all MsgAlign helplets. */
template<typename T>
static constexpr void MsgAlign_(size_t& align);
template<typename TPayload, size_t ILayer, size_t NLayers, typename TLayer, typename... TLayers>
static constexpr typename std::enable_if<(ILayer <= NLayers), void>::type MsgAlign_(size_t& align);
template<typename TPayload, size_t ILayer, size_t NLayers, typename... TLayers>
static constexpr typename std::enable_if<(ILayer == NLayers + 1), void>::type MsgAlign_(size_t align);

/**
 * @brief Return the alignment of the message.
 */
template<typename TPayload, size_t NLayer, typename... TLayers>
static constexpr size_t MsgAlign()
{
    // HINT: Minimum alignment is 8 due to the PIMP queue's E2E protection
    size_t align = 8;
    MsgAlign_<TPayload, 0, NLayer, TLayers...>(align);
    return align;
}
/** @brief Unrolling of the parameter pack. */
template<typename TPayload, size_t ILayer, size_t NLayers, typename TLayer, typename... TLayers>
static constexpr typename std::enable_if<(ILayer <= NLayers), void>::type MsgAlign_(size_t& align)
{
    MsgAlign_<typename TLayer::Header>(align);
    MsgAlign_<TPayload, ILayer + 1, NLayers, TLayers...>(align);
}
/** @brief Unrolling of the parameter. */
template<typename TPayload, size_t ILayer, size_t NLayers, typename... TLayers>
static constexpr typename std::enable_if<(ILayer == NLayers + 1), void>::type MsgAlign_(size_t align)
{
    MsgAlign_<TPayload>(align);
}
/**
 * @brief Take T and compare its alignment requirements.
 *
 * @remark
 * Empty structs are considered as placeholders and not considered.
 */
template<typename T>
static constexpr void MsgAlign_(size_t& align)
{
    align = (align <= alignof(T)) ? alignof(T) : align;
}

/** @brief Forward declarations for all MsgSize helplets. */
template<typename T>
static constexpr void MsgSize_(size_t& size);
template<typename TPayload, size_t ILayer, size_t NLayers, typename TLayer, typename... TLayers>
static constexpr typename std::enable_if<(ILayer <= NLayers), void>::type MsgSize_(size_t& size);
template<typename TPayload, size_t ILayer, size_t NLayers, typename... TLayers>
static constexpr typename std::enable_if<(ILayer == NLayers + 1), void>::type MsgSize_(size_t& size);

/**
 * @brief Return the size of the message.
 */
template<typename TPayload, size_t NLayer, typename... TLayers>
static constexpr size_t MsgSize()
{
    size_t size = 0;
    MsgSize_<TPayload, 0, NLayer, TLayers...>(size);
    // Check the total size against the required alignment
    size_t maxAlign = MsgAlign<TPayload, NLayer, TLayers...>();
    size_t padding  = 0;
    size_t offset   = (size % maxAlign);
    if (offset)
    {
        padding = maxAlign - offset;
    }
    return size + padding;
}
/** @brief Unrolling of the parameter pack as if adding struct members. */
template<typename TPayload, size_t ILayer, size_t NLayers, typename TLayer, typename... TLayers>
static constexpr typename std::enable_if<(ILayer <= NLayers), void>::type MsgSize_(size_t& size)
{
    MsgSize_<typename TLayer::Header>(size);
    MsgSize_<TPayload, ILayer + 1, NLayers, TLayers...>(size);
}
/** @brief Unrolling of the parameter pack as if adding struct members. */
template<typename TPayload, size_t ILayer, size_t NLayers, typename... TLayers>
static constexpr typename std::enable_if<(ILayer == NLayers + 1), void>::type MsgSize_(size_t& size)
{
    MsgSize_<TPayload>(size);
}
/**
 * @brief Take T and add it to size as if it were the next struct member.
 *
 * @remark
 * Empty structs are considered as placeholders and not added.
 */
template<typename T>
static constexpr void MsgSize_(size_t& size)
{
    if (!std::is_empty<T>::value)
    {
        // We might need to add padding bytes, depending on the previous type
        size_t padding = 0;
        size_t offset  = (size % alignof(T));
        if (offset)
        {
            padding = alignof(T) - offset;
        }
        size += sizeof(T) + padding;
    }
}

/** @brief Forward declarations for all LayerOffset helplets. */
template<typename TPayload, size_t ILayer, size_t NLayer, typename TLayer, typename... TLayers>
static constexpr typename std::enable_if<(ILayer < NLayer), void>::type LayerOffset_(size_t& offset);
template<typename TPayload, size_t ILayer, size_t NLayer, typename TLayer, typename... TLayers>
static constexpr typename std::enable_if<(ILayer == NLayer), void>::type LayerOffset_(size_t& offset);

/**
 * @brief Return the offset of the N-th layer of the message (N+1 being the
 * payload). */
template<typename TPayload, size_t NLayer, typename... TLayers>
static constexpr size_t LayerOffset()
{
    size_t offset = 0;
    LayerOffset_<TPayload, 0, NLayer, TLayers...>(offset);
    return offset;
}
/** @brief Unrolling of the layers' headers. */
template<typename TPayload, size_t ILayer, size_t NLayer, typename TLayer, typename... TLayers>
static constexpr typename std::enable_if<(ILayer < NLayer), void>::type LayerOffset_(size_t& offset)
{
    MsgSize_<typename TLayer::Header>(offset);
    LayerOffset_<TPayload, ILayer + 1, NLayer, TLayers...>(offset);
}

/** @brief Specialization for the end of parameter pack unrolling. */
template<typename TPayload, size_t ILayer, size_t NLayer, typename TLayer, typename... TLayers>
static constexpr typename std::enable_if<(ILayer == NLayer), void>::type LayerOffset_(size_t& offset)
{
    // Check if we need some final padding
    size_t tmp = offset % alignof(typename TLayer::Header);
    if (tmp)
    {
        offset += (alignof(typename TLayer::Header) - tmp);
    }
}

} // namespace internal

/**
 * @brief A Message with multiple protocol stack headers.
 *
 * The headers are layed out left to right as if they were members of
 * a struct. Empty structs are considered as placeholders and not taken into
 * account.
 * While all layers are mentioned in the message, only their headers up
 * to NLayer are considered for space allocation.
 *
 * @param TPayload   The type of the payload.
 * @param NLayer     Defines the active layer of the message.
 * @param TLayers... A list of all layers.
 *
 */
template<typename TPayload, size_t NLayer, typename... TLayers>
class Message
{
    static_assert(NLayer < sizeof...(TLayers), "NLayer must be within range of the no. of layers.");
    // TODO: static_assert(all types must be trivial)
public:
    /** @brief The type of the N-th header. */
    template<size_t N>
    using Header = typename utils::Variadic::Type<N, TLayers...>::type::Header;

    /** @brief Get a reference to the layer's header. */
    constexpr Header<NLayer>& header() const
    {
        return getHeader<NLayer>();
    }

    /** @brief Get a reference to the layer's payload. */
    constexpr TPayload& payload() const
    {
        // size_t addr = reinterpret_cast<size_t>(&storage_) +
        //               internal::LayerOffset<TPayload, NLayer + 1, TLayers...>();
        size_t offset = internal::LayerOffset<TPayload, NLayer, TLayers...>();
        // Add the size of the last header and check for final padding
        internal::MsgSize_<typename utils::Variadic::Type<NLayer, TLayers...>::type::Header>(offset);
        size_t tmp = offset % alignof(TPayload);
        if (tmp)
        {
            offset += (alignof(TPayload) - tmp);
        }
        return *reinterpret_cast<TPayload*>(reinterpret_cast<size_t>(&storage_) + offset);
    }

    /** @brief Equal operator (used mainly for testing). */
    inline bool operator==(const Message& other) const
    {
        // Getting tired of parameter pack unrolling...
        static_assert(NLayer < 4, "Extend this function to support more layers.");
        bool same = true;
        same &= checkHeader<0>(other);
        // std::cout << "Same 0 : " << same << std::endl;
        same &= checkHeader<1>(other);
        // std::cout << "Same 1: " << same << std::endl;
        same &= checkHeader<2>(other);
        // std::cout << "Same 2: " << same << std::endl;
        same &= checkHeader<3>(other);
        // std::cout << "Same 3: " << same << std::endl;
        same &= payload() == other.payload();
        // std::cout << "Same payload: " << same << std::endl;
        return same;
    }

    /** @brief Implicit conversion to a different message. */
    template<typename TOtherPayload, size_t NOtherLayer>
    constexpr operator Message<TOtherPayload, NOtherLayer, TLayers...>&()
    {
        return *reinterpret_cast<Message<TOtherPayload, NOtherLayer, TLayers...>*>(this);
    }

    /** @brief Implicit conversion to a different message. */
    template<typename TOtherPayload, size_t NOtherLayer>
    constexpr operator const Message<TOtherPayload, NOtherLayer, TLayers...>&() const
    {
        return *reinterpret_cast<const Message<TOtherPayload, NOtherLayer, TLayers...>*>(this);
    }

    // template<size_t N>
    // friend constexpr Header<N>& Get(Message<TPayload, NLayer, TLayers...>& msg);

    /**
     * @brief Return a reference to the header of the N-th layer.
     */
    template<size_t N>
    constexpr Header<N>& getHeader() const
    {
        size_t addr = reinterpret_cast<size_t>(&storage_) + internal::LayerOffset<TPayload, N, TLayers...>();
        return *reinterpret_cast<Header<N>*>(addr);
    }

private:
    /** @brief Check the N-th header for operator==. */
    template<size_t N>
    inline typename std::enable_if<N <= NLayer, bool>::type checkHeader(const Message& other) const
    {
        return (getHeader<N>() == other.getHeader<N>());
    }
    template<size_t N>
    inline typename std::enable_if<(N > NLayer), bool>::type checkHeader(const Message&) const
    {
        return true;
    }

    /** @brief To adhere to ISO C++, we use a storage size of 1 if the MsgSize is 0. */
    static constexpr size_t Size()
    {
        size_t size = internal::MsgSize<TPayload, NLayer, TLayers...>();
        return size ? size : 1U;
    }

    /** @brief The storage for the message. */
    std::aligned_storage_t<Size(), internal::MsgAlign<TPayload, NLayer, TLayers...>()> storage_;
};

/**
 * @brief Getter function for message layers.
 */
// template<size_t N, typename TPayload, size_t NLayer, typename... TLayers>
// constexpr typename Message<TPayload, NLayer, TLayers...>::template Header<N>& Get(
//     Message<TPayload, NLayer, TLayers...>& msg)
// {
//     return msg.template getHeader<N>();
// }

} // namespace protocol
} // namespace pipc

#endif // PIPC_PROTOCOL_MESSAGE_HPP
