//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      Allocator.hpp
/// @brief     Allocator classes for dynstatic memory allocation
/// @copyright Robert Bosch GmbH 2020
/// @author    crg2fe

#ifndef QNX_EXM_DELIVERABLES_SRC_UTILS_INC_UTILS_ALLOCATOR_HPP_
#define QNX_EXM_DELIVERABLES_SRC_UTILS_INC_UTILS_ALLOCATOR_HPP_


#include "utils/memory.hpp"
#include "utils/Mutex.hpp"


namespace exm
{
namespace utils
{


/// @brief Pointer to an allocated object
template<typename T>
class AllocObjPtr
{
    public:
        /// @brief Constructor for a default, invalid ObjPtr
        AllocObjPtr(StdReturnType objState=StdReturnType::INVALID_STATE) :  objectState(objState), obj(nullptr), resourceValid(nullptr)  { }

        /// @brief Constructor for a valid ObjPtr
        AllocObjPtr(T* object, bool* valid) : objectState(StdReturnType::OK), obj(object), resourceValid(valid) { }

        /// @brief Move constructor
        AllocObjPtr(AllocObjPtr&& other)
        {
            obj = other.obj;
            resourceValid = other.resourceValid;
            objectState = other.objectState;
            other.obj = nullptr;
            other.resourceValid = nullptr;
            other.objectState = StdReturnType::INVALID_STATE;
        }

        /// @brief Move assignment
        AllocObjPtr& operator=(AllocObjPtr&& other)
        {
            if (this != &other)
            {
                obj = other.obj;
                resourceValid = other.resourceValid;
                objectState = other.objectState;
                other.obj = nullptr;
                other.resourceValid = nullptr;
                other.objectState = StdReturnType::INVALID_STATE;
            }

            return *this;
        }

        /// @brief No copy operations are allowed, only a single instance may control the resource
        AllocObjPtr(const AllocObjPtr& other) = delete;
        AllocObjPtr& operator=(const AllocObjPtr& other) = delete;

        /// @brief Destructor, which deallocates the associated object
        ~AllocObjPtr()
        {
            deallocate();
        }

        /// @brief Moveable conversion function for related underlying classes
        template <typename D>
        operator AllocObjPtr<D>() &&
        {
           (void)static_cast<D*>(obj); // 'static' assertion whether the classes are compatible
           return std::move((*(reinterpret_cast<AllocObjPtr<D>*>(this))));
        }

        /// @brief State assertion of the pointer object
        /// The state can be:
        /// - OK : The object pointer is pointing to a valid object
        /// - INVALID_STATE : The object pointer is not valid anymore, e.g. it has been moved from
        /// - INSUFFICIENT_RESOURCES : The allocation failed due to no more storage being available from the allocator
        StdReturnType assertion() const
        {
            return (objectState);
        }

        /// @brief Boolean identitiy
        explicit operator bool() const
        {
            return (objectState == StdReturnType::OK);
        }

        /// @brief Dereference pointer
        T* operator->() const
        {
            return (obj);
        }

        /// @brief Dereference pointer
        T& operator*() const
        {
            return (*obj);
        }

        /// @brief Return the pointer to the object if it is valid, nullptr if not
        T* get() const
        {
            return (obj);
        }

        /// @brief Call the destructor of the associated object, deallocate its memory and invalidate the object pointer
        void deallocate()
        {
            if (objectState == StdReturnType::OK)
            {
                // Invalidate this object first to protect against race conditions & circular references
                objectState = StdReturnType::INVALID_STATE;
                obj->~T();
                obj = nullptr;
                *resourceValid = false;
                resourceValid = nullptr;
            }
        }

    private:
        StdReturnType objectState; ///< Current state of this object as in OK|INVALID_STATE|INSUFFICIENT_RESOURCES
        T* obj; ///< Pointer to the object
        bool* resourceValid; ///< Pointer to validity flag for the resource
};


/// @brief Object allocator class which implements a linear allocation strategy
/// The allocator returns AllocObjPtr instances, which manage the lifetime of the allocated object
template<typename T, size_t Elements, size_t ElementSize=sizeof(T), size_t Align = alignof(T)>
class LinearObjAllocator
{
    using placed_ptr_t = placed_ptr<T, ElementSize, Align>;
    static_assert((Elements > 0U), "Cannot create an allocator with 0 elements");

    public:
        using type = T;

        /// @brief Default constructor
        LinearObjAllocator() : objects(), allocMutex(), lastAllocPos(0U) { }

        /// @brief allocation of a (derived) object
        template<typename D=T, typename ...Args>
        AllocObjPtr<D> allocate(Args&&... args)
        {
            using AllocObjPtr_t = AllocObjPtr<D>;
            placed_ptr_t* obj = nullptr;
            
            // Lock the mutex and return early, if it's broken
            if (allocMutex.Lock() != StdReturnType::OK)
            {
                return (AllocObjPtr_t(StdReturnType::FATAL_ERROR));
            }

            // Determine the next free position and allocate the object if possible
            size_t newAllocPos = lastAllocPos;
            if (getNewAllocPos(newAllocPos))
            {
                lastAllocPos = newAllocPos;
                obj = &objects[newAllocPos];
                obj->template reset<D>(static_cast<Args&&>(args)...);
            }

            // Unlock the mutex and return early, if it's broken
            if (allocMutex.Unlock() != StdReturnType::OK)
            {
                return (AllocObjPtr_t(StdReturnType::FATAL_ERROR));
            }

            // Return a valid ObjPtr if allocation was successful, an invalid ObjPtr otherwise
            if (obj != nullptr)
            {
                return(AllocObjPtr_t(static_cast<D*>(obj->getRaw()), obj->getResourceHandle())); // PRQA S 3076 # The downcast is safe here, because we have constructed with typename D
            }
            else
            {
                return(AllocObjPtr_t(StdReturnType::INSUFFICIENT_RESOURCES));
            }
        }

    private:

        /// @brief Internal method to retrieve a new allocator position. Returns true if successful, otherwise false
        inline bool getNewAllocPos(size_t& newAllocPos)
        {
            bool stop = false;
            bool found = false;
            // Start searching from the last allocated position, this will most likely give the best runtime
            newAllocPos = lastAllocPos;
            do
            {
                // If the current position is free, take it
                if (!objects[newAllocPos])
                {
                    stop = true;
                    found = true;
                }
                else
                {
                    // Increment and wrap-around
                    newAllocPos++;
                    if (newAllocPos >= Elements)
                    {
                        newAllocPos = 0U;
                    }
                    // If we are back at the start, there is no free memory left
                    if (newAllocPos == lastAllocPos)
                    {
                        stop = true;
                    }
                }
            } while (!stop);
            
            return found;
        }

        placed_ptr_t objects[Elements]; ///< Array of objects which can be allocated
        utils::Mutex allocMutex; ///< Mutex for allocation of an object
        size_t lastAllocPos; ///< Position of the last allocated object
};


} // namespace exm

} // namespace utils


#endif // QNX_EXM_DELIVERABLES_SRC_UTILS_INC_UTILS_ALLOCATOR_HPP_