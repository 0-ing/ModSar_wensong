#ifndef PIPC_UTILS_TUPLE_HPP
#define PIPC_UTILS_TUPLE_HPP

#include "Variadic.hpp"

#include <iostream>

namespace pipc
{
namespace utils
{
namespace internal
{
/** @brief Forward declarations for all SizeAsStruct helplets. */
template<typename T>
static constexpr void SizeAsStruct_(size_t& size);
template<typename T, typename... Types>
static constexpr typename std::enable_if<(sizeof...(Types) > 0), void>::type SizeAsStruct_(size_t& size);

/** @brief Return the size of the parameter pack as if it were a struct. */
template<typename... Types>
static constexpr size_t SizeAsStruct()
{
    size_t size = 0;
    SizeAsStruct_<Types...>(size);
    // Check the total size against the required alignment
    size_t maxAlign = Variadic::MaxAlign<Types...>();
    size_t padding  = 0;
    size_t offset   = (size % maxAlign);
    if (offset)
    {
        padding = maxAlign - offset;
    }
    return size + padding;
}
/** @brief Unrolling of the parameter pack as if adding struct members. */
template<typename T, typename... Types>
static constexpr typename std::enable_if<(sizeof...(Types) > 0), void>::type SizeAsStruct_(size_t& size)
{
    SizeAsStruct_<T>(size);
    SizeAsStruct_<Types...>(size);
}
/**
 * @brief Take T and add it to size as if it were the next struct member.
 *
 * @remark
 * Empty structs are considered as placeholders and not added.
 */
template<typename T>
static constexpr void SizeAsStruct_(size_t& size)
{
    if (!std::is_empty<T>::value)
    {
        size_t padding = 0;
        size_t offset  = (size % alignof(T));
        if (offset)
        {
            padding = alignof(T) - offset;
        }
        size += sizeof(T) + padding;
    }
}

/** @brief Forward declarations for all OffsetAsStruct helplets. */
template<size_t I, size_t N, typename T, typename... Types>
static constexpr typename std::enable_if<(I < N), void>::type OffsetAsStruct_(size_t& offset);
template<size_t I, size_t N, typename T, typename... Types>
static constexpr typename std::enable_if<(I == N), void>::type OffsetAsStruct_(size_t& offset);

/**
 * @brief Return the offset of the N-th element of the parameter pack as if it
 * were a struct. */
template<size_t N, typename... Types>
static constexpr size_t OffsetAsStruct()
{
    size_t offset = 0;
    OffsetAsStruct_<0, N, Types...>(offset);
    return offset;
}
/** @brief Unrolling of the parameter pack as if adding struct members. */
template<size_t I, size_t N, typename T, typename... Types>
static constexpr typename std::enable_if<(I < N), void>::type OffsetAsStruct_(size_t& offset)
{
    SizeAsStruct_<T>(offset);
    OffsetAsStruct_<I + 1, N, Types...>(offset);
}
/** @brief Specialization for the end of parameter pack unrolling. */
template<size_t I, size_t N, typename T, typename... Types>
static constexpr typename std::enable_if<(I == N), void>::type OffsetAsStruct_(size_t& offset)
{
    // Check if we need some final padding
    size_t tmp = offset % alignof(T);
    if (tmp)
    {
        offset += (alignof(T) - tmp);
    }
}

} // namespace internal

/**
 * @brief A Tuple with guaranteed memory layout.
 *
 * The Types are layed out left to right as if they were sequential members of a
 * struct. Empty structs are considered as placeholders and not taken into
 * account.
 *
 * @remark
 * Only implemented for trivial types for now, can be extended if needed.
 */
template<typename... Types>
class Tuple
{
    template<size_t N>
    using ElementType = typename Variadic::Type<N, Types...>::type;
    // TODO: static_assert(all types must be trivial)

public:
    // Tuple() = default;

    /** @brief Return a reference to the N-th element of the tuple. */
    template<size_t N>
    constexpr ElementType<N>& get() const
    {
        size_t addr = reinterpret_cast<size_t>(&storage_) + internal::OffsetAsStruct<N, Types...>();
        return *reinterpret_cast<ElementType<N>*>(addr);
    }

    /** @brief Equal operator (used mainly for testing). */
    inline bool operator==(const Tuple& other) const
    {
        // Getting tired of parameter pack unrolling...
        static_assert(sizeof...(Types) <= 5, "Extend this function to support more types.");
        bool same = true;
        same &= (check<0>(other));
        // std::cout << "Same 0 : " << same << std::endl;
        same &= (check<1>(other));
        // std::cout << "Same 1 : " << same << std::endl;
        same &= (check<2>(other));
        // std::cout << "Same 2 : " << same << std::endl;
        same &= (check<3>(other));
        // std::cout << "Same 3 : " << same << std::endl;
        same &= (check<4>(other));
        // std::cout << "Same 4 : " << same << std::endl;
        return same;
    }

    /** @brief Unequal operator (used mainly for testing). */
    inline bool operator!=(const Tuple& other) const
    {
        return !operator==(other);
    }

private:
    /** @brief Check the N-th element for operator==. */
    template<size_t N>
        inline typename std::enable_if < N<sizeof...(Types), bool>::type check(const Tuple& other) const
    {
        return (get<N>() == other.get<N>());
    }
    template<size_t N>
    inline typename std::enable_if<(N >= sizeof...(Types)), bool>::type check(const Tuple&) const
    {
        return true;
    }

    /** @brief The storage for the tuple. */
    std::aligned_storage_t<internal::SizeAsStruct<Types...>(), Variadic::MaxAlign<Types...>()> storage_;
};

/** @brief Getter function for tuples. */
template<size_t N, typename... Types>
static constexpr auto& Get(Tuple<Types...>& tuple)
{
    size_t addr = reinterpret_cast<size_t>(&tuple) + internal::OffsetAsStruct<N, Types...>();
    return *reinterpret_cast<typename Variadic::Type<N, Types...>::type*>(addr);
}

/** @brief Adapter for std::tuple. */
template<size_t N, typename... Types>
static constexpr auto& Get(std::tuple<Types...>& tuple)
{
    return std::get<N>(tuple);
}

} // namespace utils
} // namespace pipc

#endif // PIPC_UTILS_TUPLE_HPP
