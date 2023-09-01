#ifndef PIPC_UTILS_OPTIONAL_HPP
#define PIPC_UTILS_OPTIONAL_HPP

#include <memory>

namespace pipc
{
namespace utils
{
/**
 * @brief Optional class with API similar to C++17's std::optional.
 *
 * @tparam T The type to be wrapped into the Optional.
 *
 * @todo
 * Test this class properly with non-trivial types if needed.
 *
 * @todo
 * This class does not take the correct choices when doing assignments.
 * It always resets and then emplaces instead of calling assignment operators.
 * If the value does not provide a fitting constructor, we will get a compile error.
 * If we want to fix this properly, we should take care of edge cases like they are
 * described in the cpp reference.
 *
 * @todo
 * Find a safe nothrow emplacement extension, because classes like Segment
 * could fail to construct properly (e.g. due to a posix error in the open call).
 * We would need something like emplace with error reporting, whether the construction was successful.
 *
 * Initial idea:
 * We provide the same API as std::optional, but additionally something like bool try_emplace(...).
 * This method calls a method try_construct(...) that the class needs to provide.
 * This way we can report succesful construction if we need it and use the normal std::optional semantics
 * for classes, which cannot fail to construct.
 */
template<typename T>
class Optional
{
    using TStorage = typename std::aligned_storage<sizeof(T), alignof(T)>::type;

public:
    /** @brief Default constructor. */
    constexpr Optional() noexcept : storage_(), init_(false)
    {
    }

    /** @brief Destructor. */
    ~Optional()
    {
        reset();
    }

    /**
     * @brief Copy constructor.
     */
    inline Optional(const Optional& other) noexcept
    {
        if (other.hasValue())
        {
            emplace(other.value());
        }
    }

    /**
     * @brief Copy assignment.
     */
    inline Optional& operator=(const Optional& other) noexcept
    {
        reset();
        if (other.hasValue())
        {
            emplace(other.value());
        }
        return *this;
    }

    /** @brief Move constructor. */
    Optional(Optional&& other) noexcept
    {
        if (other.hasValue())
        {
            emplace(std::move(other.value()));
        }
    }

    /** @brief Move assignment. */
    Optional& operator=(Optional&& other) noexcept
    {
        reset();
        if (other.hasValue())
        {
            emplace(std::move(other.value()));
        }
        return *this;
    }

    /**
     * @brief Constructor with a value.
     */
    inline Optional(const T& val) noexcept
    {
        emplace(val);
    }

    /**
     * @brief Copy assignment with a value.
     */
    inline Optional& operator=(const T& val) noexcept
    {
        emplace(val);
        return *this;
    }

    /** @brief Move assignment with a value. */
    inline Optional& operator=(T&& val) noexcept
    {
        emplace(std::move(val));
        return *this;
    }

    /** @brief Dereference the stored value. */
    T& operator*() noexcept
    {
        return value();
    }

    /** @brief Dereference the stored value. */
    T* operator->() noexcept
    {
        return &value();
    }

    /** @brief Check if the Optional contains a value. */
    explicit operator bool() const noexcept
    {
        return (init_ == true);
    }

    /** @brief Equal operator. */
    inline bool operator==(const Optional& other) const noexcept
    {
        bool same = (init_ == other.init_);
        if (same && init_)
        {
            same &= (value() == other.value());
        }
        return same;
    }

    /** @brief Unequal operator. */
    inline bool operator!=(const Optional& other) const noexcept
    {
        return !operator==(other);
    }

    /** @brief Emplace something into the Optional. */
    template<typename... Args>
    inline void emplace(Args&&... args) noexcept
    {
        reset();
        new (&storage_) T(std::forward<Args>(args)...);
        init_ = true;
    }

    /** @brief Check if the Optional contains a value. */
    inline bool hasValue() const noexcept
    {
        return (init_ == true);
    }

    inline void reset() noexcept
    {
        if (hasValue())
        {
            value().~T();
            init_ = false;
        }
    }

    /**
     * @brief Return the stored object.
     *
     * @remark
     * Unike the STL API, this one does NOT check whether the value really exists.
     */
    inline T& value() const noexcept
    {
        return *reinterpret_cast<T*>(const_cast<TStorage*>(&storage_));
    }

private:
    /** @brief Storage for the value. */
    TStorage storage_;
    /** @brief Flag whether the Optional contains a value. */
    bool init_{false};
};

/**
 * @brief Optional class with API similar to C++17's std::optional.
 *
 * Template specialization for an Optional without a value.
 */
template<>
class Optional<void>
{
public:
    /** @brief Constructor with optional initial state. */
    constexpr Optional(bool value = false) : init_(value)
    {
    }

    /** @brief Check if the Optional contains a value. */
    explicit operator bool() const noexcept
    {
        return hasValue();
    }

    /** @brief Equal operator. */
    inline bool operator==(const Optional& other) const
    {
        bool same = (init_ == other.init_);
        return same;
    }

    /** @brief Unequal operator. */
    inline bool operator!=(const Optional& other) const noexcept
    {
        return !operator==(other);
    }

    /** @brief Emplace something into the Optional. */
    inline void emplace(bool value = true) noexcept
    {
        init_ = value;
    }

    /** @brief Check if the Optional contains a value. */
    inline bool hasValue() const noexcept
    {
        return (init_ == true);
    }

    inline void reset() noexcept
    {
        init_ = false;
    }

private:
    /** @brief Flag whether the Optional contains a value. */
    bool init_{false};
};

} // namespace utils
} // namespace pipc

#endif // PIPC_UTILS_OPTIONAL_HPP
