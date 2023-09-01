//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      memory.hpp
/// @brief     Templated helper classes related to memory management
/// @copyright Robert Bosch GmbH 2020
/// @author    crg2fe

#ifndef QNX_EXM_DELIVERABLES_SRC_UTILS_INC_UTILS_MEMORY_HPP_
#define QNX_EXM_DELIVERABLES_SRC_UTILS_INC_UTILS_MEMORY_HPP_

#include "utils/type_traits.hpp"
#include <new>

namespace exm
{
namespace utils
{

/// @brief placed_ptr allows the reservation of memory for an object of a concrete or abstract class and
///  initialization of it during runtime, with placement new under the hood. 
///  This allows an embedded version of RAII and we don't need to handle
///  new and delete operations manually. The class includes static assertions for correct size and alignment.
template<typename T, size_t Len=sizeof(T), size_t Align=alignof(T)>
class placed_ptr
{
    public:
        /// @brief Default constructor marks the object as not yet initialized
        placed_ptr() : init(false), storage() {}

        /// @brief Constructor with arguments marks the object as initialized and constructs the specified object
        template<typename ...Args>
        placed_ptr(Args&&... args) : init(true), storage()
        {
            (void) new(&storage) T(static_cast<Args&&>(args)...); // Not covered: GCC inserts unreachable code for placement new nullptr check
        }

        /// @brief placed_ptr is neither copyable nor movable
        placed_ptr(const placed_ptr& other) = delete;
        placed_ptr(placed_ptr&& other) = delete;
        placed_ptr& operator=(const placed_ptr& other) = delete;
        placed_ptr& operator=(placed_ptr&& other) = delete;

        /// @brief Destruct associated object, if it was created
        ~placed_ptr()
        {
            if(init)
            {
                getRaw()->~T();
            }
        }

        /// @brief Dereference pointer
        T* operator->() const
        {
            return get();
        }

        /// @brief Dereference pointer
        T& operator*() const
        {
            return *get();
        }

        /// @brief Boolean check reflects init state of the associated object
        explicit operator bool() const
        {
            return init;
        }

        /// @brief Return the pointer to the object if it was initialized, nullptr if not
        T* get() const
        {
            return (init ? getRaw() : nullptr);
        }

        /// @brief Return the pointer to the object without additional checks
        T* getRaw() const
        {
            return reinterpret_cast<T*>(&storage);
        }

        /// @brief Reset method for a (derived) class to (re-)construct the object
        template<typename D=T, typename ...Args>
        void reset(Args&&... args)
        {
            if (init)
            {
                (void)getRaw()->~T();
            }
            (void) new(&storage) D(static_cast<Args&&>(args)...); // Not covered: GCC inserts unreachable code for placement new nullptr check
            (void)storage; // Storage is an output parameter, but doesn't need to be checked after a new operation
            init = true;

            D* tmp=nullptr; (void)static_cast<T*>(tmp); // 'Static' assertion to check whether the classes are compatible
            static_assert(sizeof(storage) >= sizeof(D), "The object container is not big enough to store the object.");
            static_assert(Align >= alignof(D), "The object container doesn't meet the alignment requirements of the object.");
        }

        /// @brief Destroy method to call the destructor of the associated object
        void destroy()
        {
            if (init)
            {
                getRaw()->~T();
                init = false;
            }
        }

        /// @brief Expose the address of the init handle for this object
        /// HINT: Use with caution, this API should only be used by superordinate allocation mechanisms
        bool* getResourceHandle()
        {
            return &init;
        }

    private:
        bool init;    ///< flag to check whether the object is already initialized
        mutable utils::AlignedStorage_t<Len, Align> storage;    ///< Static storage for the object, mutable to allow reinterpret_casts also in a const relationship
};


} // namespace exm

} // namespace utils

#endif // QNX_EXM_DELIVERABLES_SRC_UTILS_INC_UTILS_MEMORY_HPP_

