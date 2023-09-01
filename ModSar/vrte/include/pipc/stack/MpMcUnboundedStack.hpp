#ifndef PIPC_MPSC_SINGLE_LIST_HPP
#define PIPC_MPSC_SINGLE_LIST_HPP

#include "pipc/queue/internal/ReturnVal.hpp"

#include <atomic>
#include <iostream>
#include <memory>

namespace pipc
{
/**
 * @brief Multi-Producer Multi-Consumer unbounded stack.
 *
 * Consists of a singly-linked list and no dedicated memory for
 * storing elements. The element storage needs to be provided from outside,
 * by memory pools.
 * Elements pushed shall be pointers to smart pointers, which allow
 * deallocation upon calling their destructor.
 *
 * Useful for stacking up (temporary) data for later processing,
 * if the processing doesn't have to be in FIFO order.
 *
 * @remark
 * We can use this for lock-free subscriber list updates later:
 * For subscription requests, add items to the stack. During send the stack will
 * be detached and processed.
 * Rare case:
 * In case of stopOffer contention, send needs to set a flag
 * for signalling the sending is active. If a send is happening during
 * stopOffer, retry the stopOffer later by pushing a command onto some
 * dispatcher.
 *
 * @todo
 * Think about the right interface to let the linked list handle
 * allocation and deallocation from mempools. Could take a type T and ObjectPool
 * as input, then internally define a node with T, deleter and next item ptr to
 * convert the UniquePtr returned from the ObjectPool.
 *
 * @todo
 * We need a sequence counter for ABA detection (unless we can argument that a
 * mempool with fifo freelist is sufficient).
 */
template<typename T>
class MpMcUnboundedStack
{
    /** @brief Single node of the stack. */
    struct Node
    {
        T value;
        Node* next;
    };

    /**
     * @brief Detached head of a stack.
     *
     * A detached head takes ownership of the managed elements and triggers
     * their deletion, when it's destroyed.
     *
     * TODO:
     * Rename to separate class "linked list" and add iterator support.
     */
    struct Head
    {
        ~Head()
        {
            Node* nxt = first;
            while (nxt)
            {
                auto old = nxt;
                nxt      = nxt->next;
                std::cout << "Deleting..." << std::endl;
                delete old;
            }
        }

        Node* first;
    };

public:
    /** @brief Check whether the stack is empty. */
    bool empty()
    {
        return (head_.load(std::memory_order_relaxed) == nullptr);
    }

    /** @brief Push an item to the stack. */
    ReturnVal try_push(const T& value)
    {
        auto item = new Node{value, nullptr};

        auto oldHead = head_.load(std::memory_order_relaxed);
        do
        {
            item->next = oldHead;
        } while (!head_.compare_exchange_weak(oldHead, item));

        return ReturnVal::kOk;
    }

    /** @brief Pop an item from the stack. */
    ReturnVal try_pop(T& value)
    {
        Node* item;
        auto oldHead = head_.load(std::memory_order_relaxed);

        do
        {
            item = oldHead;
            if (!oldHead)
            {
                return ReturnVal::kQueueEmpty;
            }
        } while (!head_.compare_exchange_weak(oldHead, oldHead->next));

        value = item->value;
        delete item;

        return ReturnVal::kOk;
    }

    /** @brief Detach the head of the stack. */
    Head detach()
    {
        auto head = head_.exchange(nullptr);
        return Head{head};
    }

private:
    std::atomic<Node*> head_{nullptr};
};

} // namespace pipc

#endif // PIPC_MPSC_SINGLE_LIST_HPP
