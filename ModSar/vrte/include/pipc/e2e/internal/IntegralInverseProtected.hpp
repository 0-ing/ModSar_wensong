#ifndef E2E_INTERNAL_INTEGRAL_INVERSE_PROTECTED_HPP
#define E2E_INTERNAL_INTEGRAL_INVERSE_PROTECTED_HPP

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace pipc
{
namespace e2e
{
namespace internal
{
/** @brief A type which provides twice the storage width of the type which is
 * actually used. */
template<typename T, typename T2 = void>
struct StorageType;

template<>
struct StorageType<uint8_t>
{
    typedef uint16_t type;
    static constexpr size_t bits()
    {
        return 8;
    };
    static constexpr size_t bitmask()
    {
        return 0xFF;
    }
};

template<>
struct StorageType<uint16_t>
{
    typedef uint32_t type;
    static constexpr size_t bits()
    {
        return 16;
    };
    static constexpr size_t bitmask()
    {
        return 0xFFFF;
    }
};

template<>
struct StorageType<uint32_t>
{
    typedef uint64_t type;
    static constexpr size_t bits()
    {
        return 32;
    };
    static constexpr size_t bitmask()
    {
        return 0xFFFFFFFF;
    }
};

} // namespace internal

/**
 * @brief Untrusted Integral with redundant inverse storage.
 *
 * The class holds a storage with double the size of the required value to have
 * an inverse value right next to it.
 *
 * Examples for 16-bit values:
 * - Init: FFFF0000
 * - Increment: FFFF0001
 * - Before overflow: 0000FFFF
 * - After overflow: 0
 *
 * TODO:
 * - Introduce incr() and decr() functions with optimized overflow handling
 * - Introduce incr_no_ov() and decr_no_ov() functions without overflow handling
 *
 *
 * @remark
 * The implementation is optimized to work on a single register.
 * It packs value + inverse into one value of twice of T's size.
 */
template<typename T>
class IntegralInverseProtected
{
public:
    using StorageType = internal::StorageType<T>;

    constexpr IntegralInverseProtected() noexcept : storage_(calcStorage(0))
    {
    }

    inline IntegralInverseProtected(T init) noexcept : storage_(calcStorage(init))
    {
    }

    /** @brief Get the variable and report whether it's actually valid. */
    inline bool get(T& value)
    {
        value = get();
        return check();
    }

    /** @brief Get without checking. */
    inline T get()
    {
        return static_cast<T>(storage_ & StorageType::bitmask());
    }

    /** @brief Reset the variable. */
    inline void reset(T value)
    {
        storage_ = calcStorage(value);
    }

    /**
     * @brief Add without checking.
     */
    inline void add(T value)
    {
        storage_ = calcStorage(storage_ + value);
    };

    /**
     * @brief Subtract without checking.
     */
    inline void sub(T value)
    {
        storage_ = calcStorage(storage_ - value);
    }

    /** @brief Check if the value is valid. */
    inline bool check()
    {
        typename StorageType::type tmp = static_cast<typename StorageType::type>(~storage_);
        // Hint: A decent compiler should be able to translate this to a rotation.
        typename StorageType::type tmpRev = static_cast<typename StorageType::type>(
            (storage_ << StorageType::bits()) | (storage_ >> StorageType::bits()));
        return (tmp == tmpRev);
    }

private:
    /**
     * @brief Calculate the associated storage to a given value.
     *
     * @remark
     * Value is of type size_t to prevent early truncation, this enables
     * bit field insert instructions when available.
     */
    static inline typename StorageType::type calcStorage(size_t value)
    {
        return static_cast<typename StorageType::type>((value & StorageType::bitmask())
                                                       | (~value << StorageType::bits()));
    }

    /**
     * @brief The stored value.
     *
     * The value in storage is double the size of the handled variable,
     * since it needs to contain its inverse.
     */
    typename StorageType::type storage_;

    static_assert(std::is_integral<T>::value, "Integral required.");
    static_assert(2 * sizeof(T) == sizeof(typename StorageType::type), "Storage must be twice as big as T.");
};

} // namespace e2e
} // namespace pipc

#endif // E2E_INTERNAL_INTEGRAL_INVERSE_PROTECTED_HPP
