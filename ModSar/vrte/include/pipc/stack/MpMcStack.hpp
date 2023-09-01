#ifndef PIPC_MPMC_STACK_HPP
#define PIPC_MPMC_STACK_HPP

#include "pipc/queue/internal/ReturnVal.hpp"
#include "pipc/utils/CacheLineSize.hpp"

#include <array>
#include <atomic>
#include <memory>

namespace pipc
{
/**
 * @brief Multi-Producer Multi-Consumer stack.
 *
 * This stack contains two singly-linked lists for used and free stack nodes.
 *
 * The memory for the stack nodes is embedded into this class, nodes are
 * accessed via their index.
 * Push and pop operations require two CAS operations each:
 * One for manipulationg the used nodes, the other for manipulating the free
 * nodes.
 *
 * @todo
 * We need a sequence counter for ABA detection.
 */
template<typename T, size_t N, bool CacheAligned = true>
class MpMcStack
{
    /**
     * @brief Type used for indices.
     *
     * A signed type is used to signal -1 for no index.
     * With 16-bit we can cover sufficient stack sizes.
     */
    using Index = int16_t;

    /** @brief One stack node. */
    struct Node
    {
        /** @brief Value. */
        alignas(utils::GetAlignment<T, CacheAligned>()) T value;
        /** @brief Index to next node. */
        Index next;
    };

public:
    /** @brief Default constructor. */
    constexpr MpMcStack() noexcept : nodes_(), headUsed_(-1), headFree_(0)
    {
        Index last = static_cast<Index>(N - 1);
        for (Index i = 0; i < last; i++)
        {
            nodes_[i].next = static_cast<Index>(i + 1);
        }
        nodes_[N - 1].next = -1;
    }

    /** @brief Wrapper for calling a push on an object. */
    static ReturnVal Try_push(MpMcStack* obj, T v)
    {
        return obj->try_push(v);
    }

    /** @brief Check if the stack is empty. */
    inline bool empty()
    {
        return (headUsed_.load(std::memory_order_relaxed) == -1);
    }

    /** @brief Check if teh stack is full. */
    inline bool full()
    {
        return (headFree_.load(std::memory_order_relaxed) == -1);
    }

    /**
     * @brief Check the size of the stack.
     *
     * @remark
     * Only used in benchmark code currently. Checking the size
     * of a lock-free linked list is not really a good idea for
     * productive code..
     */
    inline size_t size()
    {
        size_t size = 0;
        Node* node  = &nodes_[headUsed_.load(std::memory_order_relaxed)];
        while (node->next != -1)
        {
            size++;
            node = &nodes_[node->next];
        }
        return size;
    }

    /** @brief Try to push a value onto the stack. */
    inline ReturnVal try_push(const T& value)
    {
        // Reserve a free node first
        auto newHeadUsed = headFree_.load(std::memory_order_relaxed);
        do
        {
            if (newHeadUsed < 0)
            {
                return ReturnVal::kQueueFull;
            }
        } while (!headFree_.compare_exchange_weak(newHeadUsed, nodes_[newHeadUsed].next));

        // Now set the value and replace the used head
        auto& node = nodes_[newHeadUsed];
        node.value = value;

        auto oldHeadUsed = headUsed_.load(std::memory_order_relaxed);
        do
        {
            node.next = oldHeadUsed;
        } while (!headUsed_.compare_exchange_weak(oldHeadUsed, newHeadUsed));

        return ReturnVal::kOk;
    }

    /** @brief Try to pop a value from the stack. */
    inline ReturnVal try_pop(T& value)
    {
        // Reserve a used node first
        auto oldHeadUsed = headUsed_.load(std::memory_order_relaxed);
        do
        {
            if (oldHeadUsed < 0)
            {
                return ReturnVal::kQueueEmpty;
            }
        } while (!headUsed_.compare_exchange_weak(oldHeadUsed, nodes_[oldHeadUsed].next));

        // Now retrieve the value and replace the free head
        auto& node = nodes_[oldHeadUsed];
        value      = node.value;

        auto oldHeadFree = headFree_.load(std::memory_order_relaxed);
        do
        {
            node.next = oldHeadFree;
        } while (!headFree_.compare_exchange_weak(oldHeadFree, oldHeadUsed));

        return ReturnVal::kOk;
    }

private:
    /** @brief All available stack nodes. */
    std::array<Node, N> nodes_;
    /** @brief The head index of the used nodes. */
    alignas(utils::GetAlignment<Index, CacheAligned>()) std::atomic<Index> headUsed_;
    /** @brief The head index of the free nodes. */
    alignas(utils::GetAlignment<Index, CacheAligned>()) std::atomic<Index> headFree_;
};

} // namespace pipc

#endif // PIPC_MPMC_STACK_HPP
