#ifndef E2E_INTEGRAL_UNPROTECTED_HPP
#define E2E_INTEGRAL_UNPROTECTED_HPP

#include <cstddef>
#include <type_traits>

namespace pipc
{
namespace e2e
{
/** @brief Integral value for with unprotected value storage. */
template<typename T>
class IntegralUnprotected
{
public:
    static_assert(std::is_integral<T>::value, "Integral required.");

    constexpr IntegralUnprotected() noexcept : val_(0)
    {
    }

    inline IntegralUnprotected(T init) noexcept : val_(init)
    {
    }

    /** @brief Get the variable and report whether it's actually valid. */
    inline bool get(T& value)
    {
        value = get();
        return true;
    }

    /** @brief Get without checking. */
    inline T get()
    {
        return val_;
    }

    /** @brief Reset the variable. */
    inline void reset(T value)
    {
        val_ = value;
    }

    /** @brief Add without checking. */
    inline void add(T value)
    {
        val_ = static_cast<T>(val_ + value);
    };

    /** @brief Subtract without checking. */
    inline void sub(T value)
    {
        val_ = static_cast<T>(val_ - value);
    }

    /** @brief Check if the value is valid. */
    constexpr bool check()
    {
        return true;
    }

private:
    T val_;
};

} // namespace e2e
} // namespace pipc

#endif // E2E_INTEGRAL_UNPROTECTED_HPP
