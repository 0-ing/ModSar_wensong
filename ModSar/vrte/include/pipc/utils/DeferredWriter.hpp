#ifndef UTILS_DEFERRED_WRITER_HPP
#define UTILS_DEFERRED_WRITER_HPP

#include "pipc/queue/SpScOvQueue.hpp"

namespace pipc
{
namespace utils
{
/**
 * @brief Class for an object with deferred writing of type T.
 *
 * Useful building block for single writer single reader scenarios:
 * The variable is kept consistent by deferring write operations to the context
 * of the reader. It will be updated the next time the reader uses it.
 *
 * @todo
 * When we have an arena allocator in place, use a pointer instead of an
 * in-place buffer. The buffer is usually not required and just takes up
 * unnecessary space.
 */
template<typename T>
class DeferredWriter
{
public:
    /**
     * @brief Read the variable.
     *
     * Executes a pending write, if there is one, and then returns a reference
     * to the updated value.
     */
    inline const T& read()
    {
        if (EXPECT_LIKELY(buffer_.empty()))
        {
            return value_;
        }

        // HINT: Not checking for an empty queue, because this means the queue is used in
        // a multi consumer context, which would be UB for this class.
        T tmp;
        static_cast<void>(buffer_.try_pop(tmp));
        value_ = std::move(tmp);
        return value_;
    }

    /**
     * @brief Copy assignment operator.
     */
    inline DeferredWriter<T>& operator=(const T& value)
    {
        write(value);
        return *this;
    }

    /**
     * @brief Move assignment operator.
     */
    inline DeferredWriter<T>& operator=(T&& value)
    {
        write(std::move(value));
        return *this;
    }

    /**
     * @brief Write to the variable.
     *
     * Places a new value into the write buffer.
     */
    template<typename... Args>
    void write(Args&&... args)
    {
        buffer_.try_emplace(std::forward<Args>(args)...);
    }

private:
    /** @brief The value. */
    T value_;
    /** @brief The write buffer. */
    SpScOvQueue<T, 1U, false> buffer_;
};

} // namespace utils
} // namespace pipc

#endif // UTILS_DEFERRED_WRITER_HPP
