#ifndef PIPC_UTIL_REGISTRY_HPP
#define PIPC_UTIL_REGISTRY_HPP

#include <array>
#include <string.h>

namespace pipc
{
namespace utils
{
/**
 * @brief A generic registry container for managing entries.
 *
 * A Registry features a map-like container with static memory allocation.
 * Entries need to provide getKey()/setKey() methods, which define by which UUID to
 * identify the entry and set its key.
 * The get(...) method of the registry returns entries, which correspond to existing entries
 * if the key is already present, or new entries if the key has not been found.
 *
 * Once an entry has been created, it is ensured that its address stays consistent.
 * This means that the returned entry pointers can be saved elsewhere for subsequent
 * accesses.
 * Entries in the registry are searched through sequentially with order O(n), new
 * entries are appended at the end of the list.
 *
 * @todo
 * Entries in the registry are default-initialized due to std::array container.
 *
 * @todo
 * If we have a generic map with static allocation available, we could use that instead.
 * The registry uses a little less memory due to embedded keys at the cost of potentially
 * longer search runtime and entries requiring to provide a key() method.
 */
template<typename TKey, typename TValue, size_t Capacity>
class Registry
{
public:
    /**
     * @brief Default constructor.
     */
    Registry() : entries_(), size_(0)
    {
    }

    /** @brief Iterator support for range-based loops. */
    TValue* begin()
    {
        return &entries_[0];
    }

    /** @brief Iterator support for range-based loops. */
    const TValue* begin() const
    {
        return &entries_[0];
    }

    /** @brief Iterator support for range-based loops. */
    TValue* end()
    {
        return &entries_[size_];
    }

    /** @brief Iterator support for range-based loops. */
    const TValue* end() const
    {
        return &entries_[size_];
    }

    /** @brief Return the capacity of the registry. */
    constexpr size_t capacity()
    {
        return Capacity;
    }

    /**
     * @brief Get an entry with the specified key from the registry.
     *
     * If a new entry has been created, created is set to true.
     *
     * @return
     * A valid ptr if the operation was successful, nullptr otherwise.
     *
     * @todo
     * Change API to return different kinds of errors (provide class similar to ara::core::Result?)
     */
    TValue* get(const TKey& key, bool& created)
    {
        created = false;
        // Check for an existing entry
        for (size_t i = 0; i < size_; i++)
        {
            if (entries_[i].getKey() == key)
            {
                return &entries_[i];
            }
        }
        // If nothing has been found, try to create a new one
        if (size_ < capacity())
        {
            entries_[size_].setKey(key);
            size_++;
            created = true;
            return &entries_[size_ - 1];
        }
        // Registry is full
        return nullptr;
    }

    /**
     * @brief Get an entry with the specified key from the registry without creating the entry if the key is not found.
     */
    TValue* find(const TKey& key)
    {
        for (size_t i = 0; i < size_; i++)
        {
            if (entries_[i].getKey() == key)
            {
                return &entries_[i];
            }
        }
        return nullptr;
    }

    /**
     * @brief Get an entry with the specified key from the registry.
     *
     * Similar to the other get method, but without reporting whether
     * the entry is created newly or not.
     *
     * @return
     * A valid ptr if the operation was successful, nullptr otherwise.
     *
     * @todo
     * Change API to return different kinds of errors (provide class similar to ara::core::Result?)
     */
    TValue* get(const TKey& key)
    {
        bool created;
        return get(key, created);
    }

protected:
    /** @brief List of all processes managed by the registry. */
    std::array<TValue, Capacity> entries_;
    /** @brief Current actual size of the registry. */
    size_t size_;
};

} // namespace utils
} // namespace pipc

#endif // PIPC_UTIL_REGISTRY_HPP
