#ifndef PIPC_UTILS_VARIADIC_HPP
#define PIPC_UTILS_VARIADIC_HPP
#include <stddef.h>
#include <stdint.h>
#include <utility>

namespace pipc
{
namespace utils
{
/**
 * @brief Helper methods for variadic templates.
 */
class Variadic
{
private:
    /** @Forward declarations for variadic structs. */
    template<size_t N, size_t Index, typename T, typename... Types>
    struct Type_;

public:
    /**
     * @brief Return the biggest size of the types in the parameter pack.
     */
    template<typename... Types>
    static constexpr size_t MaxSize()
    {
        return MaxSize_<Types...>();
    }

    /**
     * @brief Return the biggest alignment of types in the parameter pack.
     */
    template<typename... Types>
    static constexpr size_t MaxAlign()
    {
        return maxAlign_<Types...>();
    }

    /**
     * @brief Return the index of T in the parameter pack.
     *
     * Returns the index if it was found, or -1 if not.
     * If T is included multiple times, returns the first finding.
     */
    template<typename T, typename... Types>
    static constexpr size_t Idx()
    {
        return Idx_<T, Types...>();
    }

    /** @brief Return the type of the parameter pack at Index. */
    template<size_t Index, typename... Types>
    struct Type
    {
        static_assert(Index < sizeof...(Types), "Index must be within parameter pack.");
        using type = typename Type_<0, Index, Types...>::type;
    };

    /**
     * @brief Check whether all types in the paramter pack are trivial.
     */
    template<typename... Types>
    static constexpr bool IsTrivial()
    {
        return IsTrivial_<Types...>();
    }

private:
    /** @brief Return sizeof(T) if it's bigger than val, otherwise val.*/
    template<typename T>
    static constexpr size_t MaxSize_(size_t val = 0)
    {
        val = (val <= sizeof(T)) ? sizeof(T) : val;
        return val;
    }

    /** @brief Return the biggest size of types {T, ...Types}.*/
    template<typename T, typename... Types>
    static constexpr typename std::enable_if<(sizeof...(Types) > 0), size_t>::type MaxSize_(size_t val = 0)
    {
        return MaxSize_<Types...>(MaxSize_<T>(val));
    }

    /** @brief Return alignof(T) if it's bigger than val, otherwise val.*/
    template<typename T>
    static constexpr size_t maxAlign_(size_t val = 0)
    {
        val = (val <= alignof(T)) ? alignof(T) : val;
        return val;
    }

    /** @brief Return the biggest alignment of types {T, ...Types}.*/
    template<typename T, typename... Types>
    static constexpr typename std::enable_if<(sizeof...(Types) > 0), size_t>::type maxAlign_(size_t val = 0)
    {
        return maxAlign_<Types...>(maxAlign_<T>(val));
    }

    /** @brief Return the given idx if T & U are the same, -1 if not. */
    template<typename T, typename U>
    static constexpr size_t Idx_(size_t idx = 0)
    {
        idx = (std::is_same<T, U>::value) ? idx : -1;
        return idx;
    }

    /** @brief Return the index of T in the parameter pack. */
    template<typename T, typename U, typename... Types>
    static constexpr typename std::enable_if<(sizeof...(Types) > 0), size_t>::type Idx_(size_t idx = 0)
    {
        if (std::is_same<T, U>::value)
        {
            return idx;
        }
        else
        {
            return Idx_<T, Types...>(++idx);
        }
    }

    /** @brief Slicer for Type selector. */
    template<size_t N, size_t Index, typename T, typename... Types>
    struct Type_
    {
        using type = typename Type_<N + 1, Index, Types...>::type;
    };

    /** @brief Match for Type selector. */
    template<size_t N, typename T, typename... Types>
    struct Type_<N, N, T, Types...>
    {
        using type = T;
    };

    /** @brief Return whether T is trivial.*/
    template<typename T>
    static constexpr bool IsTrivial_()
    {
        return std::is_trivial<T>::value;
    }

    /** @brief Return whether all of {T, ...Types} are trivial.*/
    template<typename T, typename... Types>
    static constexpr typename std::enable_if<(sizeof...(Types) > 0), bool>::type IsTrivial_()
    {
        return IsTrivial_<T>() && IsTrivial_<Types...>();
    }
};

} // namespace utils
} // namespace pipc

#endif // VARIADIC_HPP
