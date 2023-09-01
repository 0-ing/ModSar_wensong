#ifndef E2E_TYPE_UNPROTECTED_HPP
#define E2E_TYPE_UNPROTECTED_HPP

#include <cstdint>
#include <type_traits>
#include <utility>

namespace pipc
{
namespace e2e
{
/**
 * @brief 'Trusted' Type without protection.
 *
 * The class holds only the actual object.
 */
template<typename T>
class TypeUnprotected
{
public:
    constexpr TypeUnprotected() noexcept
    {
    }

    /** @brief Copy the object and report whether it's actually valid. */
    inline bool copy(T& obj)
    {
        obj = *get();
        return true;
    }

    /**
     * @brief Get a pointer to the object in-place.
     *
     * Can be used for direct access without copying first,
     * if reducing copies is desired.
     */
    inline T* get()
    {
        return reinterpret_cast<T*>(&obj_);
    }

    /**
     * @brief Construct an object by emplacing it.
     */
    template<typename... Args>
    inline void construct(Args&&... args) noexcept
    {
        static_assert(std::is_nothrow_constructible<T, Args&&...>::value,
                      "T must be nothrow constructible with Args&&...");
        new (&obj_) T(std::forward<Args>(args)...);
    }

    /** @brief Check if the value is valid. */
    constexpr bool check()
    {
        return true;
    }

private:
    /** @brief A storage of the actual object. */
    typename std::aligned_storage<sizeof(T), alignof(T)>::type obj_;

    static_assert(std::is_trivially_destructible<T>::value, "T must be trivially destructible.");
};

} // namespace e2e
} // namespace pipc

#endif // E2E_TYPE_UNPROTECTED_HPP
