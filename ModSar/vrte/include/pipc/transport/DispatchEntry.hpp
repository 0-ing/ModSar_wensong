/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef TRANSPORT_DISPATCH_ENTRY_HPP
#define TRANSPORT_DISPATCH_ENTRY_HPP

#include <atomic>
#include <cstddef>

namespace pipc
{
namespace transport
{
/**
 * @brief A single entry for a dispatch.
 *
 * A dispatch entry consists of a function pointer with 3 input parameters:
 *
 * Context, which it is called with:
 * The context is something, whose type is only known by the function it is
 * called with. This is done to reduce call complexity from dynamic to static
 * dispatch.
 * In most use cases the context is used as a member pointer to call a member
 * function.
 *
 * Socket, that the message was received from:
 * The socket reveals the sender information.
 *
 * Message:
 * Pointer to the SDU, whose real type only the called function knows.
 *
 * @remark
 * The members of a dispatch entry are set in a certain sequential order
 * to prevent race conditions between setting an entry and calling it.
 *
 * The following ordering is implemented to change entries:
 * - Set: Set the context, then the callback(s)
 * - Reset: Set the callback(s) to null, then the context to null
 *
 * The following ordering is implemented to call entries:
 * - Load the callback and then the context
 * - Invoke if the callback is not nullptr
 *
 * It is extremely unlikely that such a race condition could occur, since
 * normally endpoints are first registered at the dispatcher and then start
 * communication, or vice versa they stop communication and then unregister.
 * But better to be safe than sorry..
 *
 * @todo
 * Needs to be checked again for thread-safety, at best with some test.
 */
struct DispatchEntry
{
    /**
     * @brief Try to reserve a dispatchEntry.
     *
     * Reservation is done by doing a CAS on the context member.
     *
     * @return true Reservation was successful.
     * @return false Reservation was not succesful.
     */
    bool tryReserve()
    {
        void* expected = nullptr;
        return (context.compare_exchange_strong(expected, reinterpret_cast<void*>(1U)));
    }

    /** @brief Set the callback to a member wrapper function. */
    template<typename T, typename U, typename Arg, typename TSocket>
    inline void set(void (*fnc)(T&, TSocket&, Arg*), U& obj)
    {
        static_assert(std::is_base_of<T, U>::value, "Static function must be callable with the given object.");
        context.store(reinterpret_cast<void*>(&obj), std::memory_order_relaxed);
        // Note: Double reinterpret_cast is required to suppress
        // incompatible fnc ptr warning
        callbacks[0].store(reinterpret_cast<void (*)(void*, void*, void*)>(reinterpret_cast<void (*)(void)>(fnc)),
                           std::memory_order_release);
    }

    /** @brief Set the callback to 2 member wrapper functions. */
    template<typename T, typename U, typename V, typename Arg0, typename Arg1, typename TSocket>
    inline void set(void (*fnc0)(T&, TSocket&, Arg0*), void (*fnc1)(U&, TSocket&, Arg1*), V& obj)
    {
        static_assert(std::is_base_of<T, V>::value, "Static function must be callable with the given object.");
        static_assert(std::is_base_of<T, U>::value, "Static function must be callable with the given object.");
        context.store(reinterpret_cast<void*>(&obj), std::memory_order_relaxed);
        // Note: Double reinterpret_cast is required to suppress
        // incompatible fnc ptr warning
        callbacks[0].store(reinterpret_cast<void (*)(void*, void*, void*)>(reinterpret_cast<void (*)(void)>(fnc0)),
                           std::memory_order_release);
        callbacks[1].store(reinterpret_cast<void (*)(void*, void*, void*)>(reinterpret_cast<void (*)(void)>(fnc1)),
                           std::memory_order_release);
    }

    /** @brief Reset the entry. */
    inline void reset()
    {
        callbacks[0].store(nullptr, std::memory_order_relaxed);
        callbacks[1].store(nullptr, std::memory_order_relaxed);
        std::atomic_thread_fence(std::memory_order_release);
        context.store(nullptr, std::memory_order_relaxed);
    }

    /** @brief Check if the entry already contains a dispatch. */
    explicit operator bool() const noexcept
    {
        return callbacks[0] != nullptr;
    }

    /**
     * @brief Call operator.
     *
     * Returns true if a dispatch was invoked, false it not.
     */
    template<typename TSocket>
    inline bool operator()(size_t idx, TSocket& socket, void* msg)
    {
        // Note: Double reinterpret_cast is required to suppress
        // incompatible fnc ptr warning
        auto cbk = reinterpret_cast<void (*)(void*, TSocket&, void*)>(
            reinterpret_cast<void (*)(void)>(callbacks[idx].load(std::memory_order_acquire)));
        auto ctx = context.load(std::memory_order_relaxed);
        if (cbk)
        {
            (*cbk)(ctx, socket, msg);
        }
        return (cbk != nullptr);
    }

    /**
     * @brief Context for the callback function.
     *
     * Can be a pointer to an object or anything with up to sizeof(size_t).
     */
    std::atomic<void*> context{nullptr};

    /**
     * @brief Pointer to the callback functions.
     *
     * Can be any static function.
     */
    std::atomic<void (*)(void*, void*, void*)> callbacks[2]{{nullptr}, {nullptr}};
};

} // namespace transport
} // namespace pipc

#endif // TRANSPORT_DISPATCH_ENTRY_HPP
