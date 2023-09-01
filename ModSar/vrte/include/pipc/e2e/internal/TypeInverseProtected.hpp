#ifndef E2E_INTERNAL_TYPE_INVERSE_PROTECTED_HPP
#define E2E_INTERNAL_TYPE_INVERSE_PROTECTED_HPP

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <utility>

namespace pipc
{
namespace e2e
{
/**
 * @brief 'Untrusted' Type with redundant inverse storage.
 *
 * The class holds the actual object as well as some storage memory,
 * which contains the inverse bit pattern of the object.
 *
 * @remark
 * Inverse protection of types is limited to classes with a size of
 * a multiple of 8 Byte for simpler handling
 * (because we copy the data in 8 Byte chunks).
 */
template<typename T>
class TypeInverseProtected
{
    static_assert(std::is_trivially_destructible<T>::value, "T must be trivially destructible.");
    static_assert(sizeof(T) % 8 == 0, "Size of T must be a multiple of 8.");
    static_assert(alignof(T) >= 8, "T must be at least aligned to 8 Byte boundaries.");

public:
    constexpr TypeInverseProtected() noexcept
    {
        // In case the alignment is higher than the size, we might
        // run into problems when protecting this type as unknown with only
        // size information. Not sure yet how to tackle this best,
        // but for now we should at least detect it.
        static_assert(offsetof(TypeInverseProtected<T>, inv_) - offsetof(TypeInverseProtected<T>, obj_) == sizeof(T),
                      "Offset between object and inverse must be trivial to calculate.");
    }

    /** @brief copy the object and report whether it's actually valid. */
    inline bool copy(T& obj)
    {
        uint64_t* src = reinterpret_cast<uint64_t*>(&obj_);
        uint64_t* inv = reinterpret_cast<uint64_t*>(&inv_);
        uint64_t* dst = reinterpret_cast<uint64_t*>(&obj);
        bool success  = true;
        for (size_t i = sizeof(T) / 8; i > 0; i--)
        {
            auto tmp = *src++;
            *dst++   = tmp;
            success &= (tmp == ~(*inv++));
        }
        return success;
    }

    /**
     * @brief Construct an object by emplacing it and storing the inverse
     * afterwards.
     *
     * @todo
     * Constructing in-place could not be safe in all cases, how to make sure
     * values are only copied into?
     */
    template<typename... Args>
    inline void construct(Args&&... args) noexcept
    {
        static_assert(std::is_nothrow_constructible<T, Args&&...>::value,
                      "T must be nothrow constructible with Args&&...");
        new (&obj_) T(std::forward<Args>(args)...);
        protect();
    }

    /**
     * @brief Construct an object by copying it and storing the inverse on the fly.
     */
    inline void construct(const T& obj) noexcept
    {
        const uint64_t* src = reinterpret_cast<const uint64_t*>(&obj);
        uint64_t* dst       = reinterpret_cast<uint64_t*>(&obj_);
        uint64_t* inv       = reinterpret_cast<uint64_t*>(&inv_);
        for (size_t i = sizeof(T) / 8; i > 0; i--)
        {
            auto tmp = *src++;
            *dst++   = tmp;
            *inv++   = ~tmp;
        }
    }

    /**
     * @brief Construct an object by copying it and storing the inverse on the fly.
     *
     * @todo
     * Not sure if there might be a nicer way.
     */
    constexpr void construct(T& obj) noexcept
    {
        const T& tmp = obj;
        construct(tmp);
    }

    /** @brief Check if the value is valid. */
    inline bool check()
    {
        uint64_t* obj = reinterpret_cast<uint64_t*>(&obj_);
        uint64_t* inv = reinterpret_cast<uint64_t*>(&inv_);
        bool valid    = true;
        for (size_t i = sizeof(T) / 8; i > 0; i--)
        {
            valid &= (*obj++ == ~(*inv++));
        }
        return valid;
    }

    /** @brief Protect the object by storing the inverse bit pattern. */
    inline void protect()
    {
        uint64_t* obj = reinterpret_cast<uint64_t*>(&obj_);
        uint64_t* inv = reinterpret_cast<uint64_t*>(&inv_);
        for (size_t i = sizeof(T) / 8; i > 0; i--)
        {
            *inv++ = ~(*obj++);
        }
    }

private:
    /** @brief A storage of the actual object. */
    typename std::aligned_storage<sizeof(T), alignof(T)>::type obj_;
    /** @brief A storage with the inverse bit pattern of the actual object. */
    typename std::aligned_storage<sizeof(T), alignof(T)>::type inv_;
};

} // namespace e2e
} // namespace pipc

#endif // E2E_INTERNAL_TYPE_INVERSE_PROTECTED_HPP
