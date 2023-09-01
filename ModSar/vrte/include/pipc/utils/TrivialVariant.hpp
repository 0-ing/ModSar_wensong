#ifndef PIPC_UTILS_TRIVIAL_VARIANT_HPP
#define PIPC_UTILS_TRIVIAL_VARIANT_HPP

#include "Variadic.hpp"

namespace pipc
{
namespace utils
{
/**
 * @brief A variant, which can hold only trivial types.
 *
 * @remark
 * This is a poor subset of what std::variant would give us, but std::variant is
 * C++17 and the back-ported variant from iox is not a trivial type (so we cannot send it).
 * This class should only be used with simple POD message structs.
 */
template<typename... Types>
class TrivialVariant
{
    using Variadic = utils::Variadic;
    static_assert(Variadic::IsTrivial<Types...>(), "All types must be trivial.");
    static_assert(sizeof...(Types) < 255, "Must be at most 254 Types in the parameter pack.");

public:
    /**
     * @brief Equal operator.
     *
     * Used mainly for testing.
     *
     * @todo
     * We have to extend this with parameter pack unrolling to test the
     * actual contents.
     */
    inline bool operator==(const TrivialVariant& other) const
    {
        bool same = (index() == other.index());
        return same;
    }

    /**
     * @brief Emplace an object of type T into the variant.
     *
     * @remark
     * If a type is already present in the variant, it is not destroyed.
     */
    template<typename T>
    inline T& emplace(const T& val)
    {
        auto& tmp = get<T>();
        tmp       = val;
        idx_      = static_cast<uint8_t>(Variadic::Idx<T, Types...>());
        return tmp;
    }

    /**
     * @brief Emplace an object of type T into the variant (in-place construction).
     *
     * @remark
     * If a type is already present in the variant, it is not destroyed.
     */
    template<typename T, typename... Args>
    inline T& emplace(Args&&... args)
    {
        auto& tmp = get<T>();
        new (&storage_) T(std::forward<Args>(args)...);
        idx_ = static_cast<uint8_t>(Variadic::Idx<T, Types...>());
        return tmp;
    }

    /**
     * @brief Cast the variant to the requested type and return a reference to it.
     *
     * @remark
     * No error checking is done whether the requested type is really currently
     * present, it is the responsibility of the caller to retrieve a valid type.
     */
    template<typename T>
    inline T& get()
    {
        static_assert(Variadic::Idx<T, Types...>() != -1, "T must be included in the variant.");
        return *reinterpret_cast<T*>(&storage_);
    }

    /** @brief Return the index of the type currently held. */
    inline uint8_t index() const
    {
        return idx_;
    }

private:
    /** @brief The storage for the variant. */
    typename std::aligned_storage<Variadic::MaxSize<Types...>(), Variadic::MaxAlign<Types...>()>::type storage_;
    /** @brief The index of the type currently held. */
    uint8_t idx_{0xFF};
};

/** @brief Getter function for variants. */
template<size_t N, typename... Types>
static inline auto& Get(TrivialVariant<Types...>& variant)
{
    return *reinterpret_cast<typename Variadic::Type<N, Types...>::type*>(&variant);
}

} // namespace utils
} // namespace pipc

#endif // PIPC_UTILS_TRIVIAL_VARIANT_HPP
