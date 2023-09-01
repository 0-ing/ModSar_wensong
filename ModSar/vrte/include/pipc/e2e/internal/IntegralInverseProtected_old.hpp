#ifndef E2E_INTERNAL_INTEGRAL_INVERSE_PROTECTED_HPP
#define E2E_INTERNAL_INTEGRAL_INVERSE_PROTECTED_HPP

#include <cstddef>
#include <type_traits>

/**
 *
 * @brief Integral value and matching inverse for untrusted value storage.
 *
 * @remark
 * Old, struct-based version.
 * On x64: Same performance as the newer version.
 */
template<typename T>
class IntegralInverseProtected
{
public:
    static_assert(std::is_integral<T>::value, "Integral required.");

    constexpr IntegralInverseProtected() noexcept : val_(0), inv_(~0)
    {
    }

    inline IntegralInverseProtected(size_t init) noexcept : val_(init), inv_(~init)
    {
    }

    /** @brief Get without checking. */
    inline T get()
    {
        return val_;
    }

    /** @brief Add without checking. */
    inline void add(size_t value)
    {
        val_ += value;
        inv_ -= value;
    };

    /** @brief Subtract without checking. */
    inline void sub(size_t value)
    {
        val_ -= value;
        inv_ += value;
    }

    /** @brief Check if the value is valid. */
    inline bool check()
    {
        return (val_ == static_cast<T>(~inv_));
    }

private:
    T val_;
    T inv_;
};

#endif // E2E_INTERNAL_INTEGRAL_INVERSE_PROTECTED_HPP
