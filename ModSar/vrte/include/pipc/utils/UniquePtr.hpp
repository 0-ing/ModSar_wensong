#ifndef UTILS_UNIQUE_PTR_HPP
#define UTILS_UNIQUE_PTR_HPP

#include "Command.hpp"

#include <cstddef>

namespace pipc
{
namespace utils
{
namespace internal
{
/**
 * @brief Base class for a generic Unique Pointer.
 *
 * Acts as a base class for common functionality of unique pointers.
 * The Deleter is a functor, which is stored together with the pointer.
 * It is not yet defined what happens upon destruction of the object,
 * so the decision how the deleter is exactly used can be flexible.
 */
template<typename T, typename TDeleter>
class UniquePtrBase
{
public:
    /** @brief Default constructor with a nullptr. */
    constexpr UniquePtrBase() noexcept : ptr_(nullptr), deleter_()
    {
    }

    /** @brief Semantically equivalent to default constructor. */
    constexpr UniquePtrBase(std::nullptr_t) noexcept : ptr_(nullptr), deleter_()
    {
    }

    /** @brief Constructor forwarding of remaining arguments to the deleter. */
    template<typename... Args>
    UniquePtrBase(T* ptr, Args&&... args) noexcept : ptr_(ptr), deleter_(std::forward<Args>(args)...)
    {
    }

    /** @brief No copy operations. */
    UniquePtrBase(const UniquePtrBase&) = delete;
    UniquePtrBase& operator=(const UniquePtrBase&) = delete;

    /** @brief Move operations are allowed. */
    UniquePtrBase(UniquePtrBase&& other) noexcept : ptr_(other.release()), deleter_(std::move(other.deleter_))
    {
    }

    /** @brief Destructor. */
    ~UniquePtrBase() noexcept = default;

    /** @brief Move assignment operator. */
    UniquePtrBase& operator=(UniquePtrBase&& other) noexcept
    {
        if (this != &other)
        {
            ptr_     = other.release();
            deleter_ = std::move(other.deleter_);
        }
        return *this;
    }

    /** @brief Dereference the stored pointer. */
    T& operator*() const noexcept
    {
        return *ptr_;
    }
    T* operator->() const noexcept
    {
        return ptr_;
    }

    /** @brief Check if the stored pointer is null. */
    explicit operator bool() const noexcept
    {
        return ptr_ != nullptr;
    }

    /** @brief Swap the managed object. */
    void swap(UniquePtrBase& other) noexcept
    {
        std::swap(*this, other);
    }

    /** @brief Return the stored object. */
    T* get() const noexcept
    {
        return ptr_;
    }

private:
    /** @brief Return the pointer and invalidate this object. */
    T* release()
    {
        T* retVal = ptr_;
        ptr_      = nullptr;
        return retVal;
    }

protected:
    /** @brief Raw pointer to the object. */
    T* ptr_;
    /** @brief Generic deleter functor. */
    TDeleter deleter_;
};

} // namespace internal

/**
 * @brief Unique Ptr with default behavior.
 *
 * When this object is destroyed, it calls the deconstructor of the held object
 * and additionally calls the deleter function.
 * When no custom TDeleter is specified, a Command with a member function pointer with
 * the pointers address as argument is expected.
 */
template<typename T, typename TDeleter = utils::Command_1<void*, void, void*>>
class UniquePtr : public internal::UniquePtrBase<T, TDeleter>
{
    using BaseClass = internal::UniquePtrBase<T, TDeleter>;

public:
    using Deleter = TDeleter;

    /** @brief Same constructors as the base class. */
    using BaseClass::UniquePtrBase;

    /** @brief Reset upon destruction. */
    ~UniquePtr()
    {
        reset(nullptr);
    }

    /** @brief Move operations are allowed. */
    UniquePtr(UniquePtr&& other) noexcept : BaseClass::UniquePtrBase(std::move(other))
    {
    }

    /** @brief Move assignment operator. */
    UniquePtr& operator=(UniquePtr&& other) noexcept
    {
        BaseClass::operator=(std::move(other));
        return *this;
    }

    /** @brief Assignment of nullptr_t. */
    UniquePtr& operator=(std::nullptr_t) noexcept
    {
        reset(nullptr);
        return *this;
    }

    /** @brief Replace the managed object. */
    void reset(std::nullptr_t) noexcept
    {
        if (this->ptr_ != nullptr)
        {
            this->ptr_->~T();
            this->deleter_(this->ptr_);
            this->ptr_ = nullptr;
        }
    }
};

} // namespace utils
} // namespace pipc

#endif // UTILS_UNIQUE_PTR_HPP
