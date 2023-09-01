//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
/// @file      vector.hpp
/// @brief     Declaration/Definition of vector
/// @author    baetz
//=============================================================================
#ifndef UTILS_VECTOR_HPP_INCLUDED
#define UTILS_VECTOR_HPP_INCLUDED

#include "StdReturnType.hpp"
#include <new>
#include <stdint.h>

namespace exm
{

namespace utils
{

/// @brief Implementation of a fixed-size vector class.
///
/// Reflects the standardized std vector interface, but avoids exceptions and
/// instead adds some calls (such as at()) with return values.
///
template <typename VALUE_T, uint32_t SIZE>
class vector
{
public:
    // Member types
    typedef VALUE_T value_type;            ///< Type of content.
    typedef VALUE_T* pointer;              ///< Type pointing to content.
    typedef const VALUE_T* const_pointer;  ///< Type pointing to content with const.
    typedef VALUE_T* iterator;             ///< Iterator type.
    typedef const VALUE_T* const_iterator; ///< Const iterator type.

    // NOTE: reverse iterator and const reverse iterator shall be implemented

    typedef VALUE_T& reference;             ///< Reference type of content.
    typedef const VALUE_T& const_reference; ///< Const reference type of content.
    typedef uint32_t size_type;             ///< Type representing vector size.

    // Default stuff

    /// @brief Standard ctor
    vector() : memory(), usedElements(0U) {};

    /// @brief Copy ctor
    vector(const vector& v) : memory(), usedElements(0U)
    {
        if (v.usedElements <= max_size())
        {
            for (auto& element: v)
            {
                (void)try_push_back(element);
            }
            usedElements = v.usedElements;
        }
    }

    /// @brief Copy assignment
    vector& operator=(const vector& v)
    {
        if (this != &v)
        {
            if (v.usedElements <= max_size())
            {
                clear();
                for (auto& element: v)
                {
                    (void)try_push_back(element);
                }
                usedElements = v.usedElements;
            }
        }
        return *this;
    }

    /// @brief Destructor
    /// Needs to clean up allocated objects.
    ~vector()
    {
        // Call the destructor of all elements which are currently in the vector
        for (auto& element: *this)
        {
            (void)element.~VALUE_T();
        }
    }

    // Element access

    /// @brief Access specific element with range checking.
    ///
    /// Variant of C++ Standard at(), as it returns an error code instead of throwing.
    ///
    /// @param[in] pos  Position of element to access.
    /// @param[out] ptr Returns a pointer to the requested element. Unchanged if false.
    /// @return true if element in range, false else.
    bool At(size_type pos, pointer& ptr) noexcept
    {
        if (pos < usedElements)
        {
            ptr = &(begin()[pos]);
            return true;
        }
        else
        {
            return false;
        }
    }

    /// @brief Access specific element with range checking.
    ///
    /// Const variant of C++ Standard at(), as it returns an error code instead of throwing.
    ///
    /// @param[in] pos  Position of element to access.
    /// @param[out] ptr  Returns a pointer to the requested element. Unchanged if false.
    /// @return true if element in range, false else.
    bool At(size_type pos, const_pointer& ptr) const noexcept
    {
        if (pos < usedElements)
        {
            ptr = &(cbegin()[pos]);
            return true;
        }
        else
        {
            return false;
        }
    }

    /// @brief Access specific element without range checking.
    ///
    /// @param[in] pos  Position of element to access.
    /// @return A reference to the requested element.
    reference operator[](size_type pos) { return begin()[pos]; } // PRQA S 3706 # Subscript on pointer required due to type-less 'memory' member

    /// @brief Access specific element without range checking.///
    /// Const variant.
    /// @param[in] pos  Position of element to access.
    /// @return A const_reference to the requested element.
    const_reference operator[](size_type pos) const { return cbegin()[pos]; } // PRQA S 3706 # Subscript on pointer required due to type-less 'memory' member

    /// @brief Returns a reference to the first element in the vector.
    /// @warning Unsafe, does not perform any range checks.
    /// @return Reference to the first element. If container is empty, this reference is illegal.
    reference front() { return *begin(); }

    /// @brief Returns a const reference to the first element in the vector.
    /// @warning Unsafe, does not perform any range checks.
    /// @return Const reference to the first element. If container is empty, this reference is
    /// illegal.
    const_reference front() const { return *cbegin(); }

    /// @brief Returns a reference to the last element in the vector.
    /// @warning Unsafe, does not perform any range checks.
    /// @return Reference to the last element. If container is empty, this reference is illegal.
    reference back() { return (end()[-1]); } // PRQA S 3706 # Subscript on pointer required due to type-less 'memory' member

    /// @brief Returns a const reference to the last element in the vector.
    /// @warning Unsafe, does not perform any range checks.
    /// @return Const reference to the last element. If container is empty, this reference is
    /// illegal.
    const_reference back() const { return (cend()[-1]); }

    /// @brief Allows raw access to the underlying data array of the vector
    ///
    /// @return A pointer to the first data element, or nullptr if emty.
    VALUE_T* data()
    {
        if (usedElements == 0U)
        {
            return nullptr;
        }
        else
        {
            return begin();
        }
    }

    // Iterators

    /// @brief Access vector with iterator
    /// @return An iterator (i.e. a pointer) to the first element in the container. If vector is
    /// empty, the iterator is illegal.
    iterator begin() noexcept
    {
        return content();
    }
    

    /// @brief Access vector with const iterator
    /// @return A const_iterator (i.e. a const pointer) to the first element in the container. If
    /// vector is empty, the iterator is illegal.
    const_iterator cbegin() const noexcept
    {
        return content();
    }

    /// @brief Access vector with const iterator
    /// @return A const_iterator (i.e. a const pointer) to the first element in the container. If
    /// vector is empty, the iterator is illegal.
    const_iterator begin() const noexcept
    {
        return content();
    }

    /// @brief Get an iterator which indicates the end of valid data.
    /// @return An iterator (i.e. a pointer) pointing one beyond the last element. Accessing the
    /// content is illegal.
    iterator end() noexcept
    {
        return &content()[usedElements]; // PRQA S 3706 # Subscript on pointer required due to type-less 'memory' member
    }

    /// @brief Get a const_iterator which indicates the end of valid data.
    /// @return A const_iterator (i.e. a const pointer) pointing one beyond the last element.
    /// Accessing the content is illegal.
    const_iterator cend() const noexcept
    {
        return &content()[usedElements]; // PRQA S 3706 # Subscript on pointer required due to type-less 'memory' member
    }

    /// @brief Get a const_iterator which indicates the end of valid data.
    /// @return A const_iterator (i.e. a const pointer) pointing one beyond the last element.
    /// Accessing the content is illegal.
    const_iterator end() const noexcept
    {
        return &content()[usedElements]; // PRQA S 3706 # Subscript on pointer required due to type-less 'memory' member
    }

    // Capacity

    /// @brief Indication if vector is full.
    /// @return true if vector is full, false if there is free space.
    bool full() const noexcept
    {
        return SIZE == usedElements;
    }

    /// @brief Indication if vector is empty.
    /// @return true if vector is empty, false if there is at least one element in.
    bool empty() const noexcept
    {
        return (0U == usedElements);
    }

    /// @brief Returns the number of elements currently in the vector.
    /// @return Returns the number of elements currently in the vector.
    size_type size() const { return usedElements; }

    /// @brief Returns the maximum number of elements, which is equivalent to the SIZE template
    /// argument.
    /// @return The maximum allowed number of element in the vector.
    size_type max_size() const noexcept
    {
        return SIZE;
    }

    /// @brief Returns the capacity of the vector, which is equivalent to the SIZE template
    /// argument. Remark: In a normal vector, capacity is the number of element which fit without
    /// allocation and max_size the total
    ///  absolute value. Here, both values are the same.
    /// @return The maximum allowed number of element in the vector.
    size_type capacity() const noexcept
    {
        return SIZE;
    }

    // Modifiers

    /// @brief clears the vector by destructing the contents and changing the nr of elements to 0.
    
    void clear() noexcept
    {
        // Call the destructor of all elements which are currently in the vector
        for (auto& element : *this)
        {
            (void)element.~VALUE_T();
        }
        usedElements = 0U;
    }

    /// @brief appends a new element to the container. The element is constructed in-place at the
    /// location provided by the container.
    /// @param[in] args arguments to forward the constructor of the element
    /// @return true if the construction of the element was successful, false otherwise
    template <class... Args>
    StdReturnType try_emplace_back(Args&&... args)
    {
        if (usedElements < SIZE)
        {
            // Make sure we don't invoke a copy assignment, because we'd be copying to an object with an undefined state.
            // With the placement new operator we only call the copy constructor.
            iterator lastPtr = end();
            lastPtr = new(lastPtr) VALUE_T(static_cast<Args&&>(args)...);
            usedElements++;
            return StdReturnType::OK;
        }
        else
        {
            return StdReturnType::INSUFFICIENT_RESOURCES;
        }
    }

    /// @brief Extension to push_back with a return value.
    /// Will do nothing if vector is full.
    /// @param[in] value The value to append to the vector. Will be copy constructed.
    /// @return StdReturnType::OK if new element did fit into the vector,
    /// StdReturnType::INSUFFICIENT_RESOURCES else.
    StdReturnType try_push_back(const VALUE_T& value)
    {
        if (Push_back(value))
        {
            return StdReturnType::OK;
        }

        return StdReturnType::INSUFFICIENT_RESOURCES;
    }

    /// @brief Extension to const push_back with a return value.
    /// Will do nothing if vector is full.
    /// @param[in] value The value to append to the vector. Will be copy constructed.
    /// @return true if new element did fit into the vector, false else.
    bool Push_back(const VALUE_T& value)
    {
        if (usedElements < SIZE)
        {
            // Make sure we don't invoke a copy assignment, because we'd be copying to an object with an undefined state.
            // With the placement new operator we only call the copy constructor.
            iterator lastPtr = end();
            lastPtr = new(lastPtr) VALUE_T(value);
            (void)lastPtr;
            usedElements++;
            return true;
        }
        else
        {
            return false;
        }
    }

    /// @brief Extension to push_back with a return value.
    /// Will do nothing if vector is full.
    /// @param[in] value The value to append to the vector. Will be copy constructed.
    /// @return true if new element did fit into the vector, false else.
    bool Push_back(VALUE_T&& value)
    {
        if (usedElements < SIZE)
        {
            // Make sure we don't invoke a copy assignment, because we'd be copying to an object with an undefined state.
            // With the placement new operator we only call the copy constructor.
            iterator lastPtr = end();
            lastPtr = new(lastPtr) VALUE_T(value);
            usedElements++;
            return true;
        }
        else
        {
            return false;
        }
    }

    ///@brief Remove the last element from the vector.
    /// If no element is in the vector, nothing happens.
    void pop_back()
    {
        if (usedElements > 0U)
        {
            back().~VALUE_T();
            usedElements--;
        }
    }

private:
    // HINT: 
    // We will suffer from memory leaks, if we use an array of objects and the default constructor of VALUE_T allocates memory.
    // Use a statically allocated chunk of memory instead, which has the required size and alignment.
    alignas(VALUE_T) uint8_t memory[sizeof(VALUE_T)*SIZE];
    VALUE_T* content() ///< Wrapper to treat memory as a normal array
    {
        return reinterpret_cast<VALUE_T*>(memory); 
    }
    const VALUE_T* content() const ///< Wrapper to treat memory as a normal array (const version)
    {
        return reinterpret_cast<const VALUE_T*>(memory); 
    }
    uint32_t usedElements; ///< Value indicating current vector size.
};
} // namespace utils
} // namespace exm

#endif // UTILS_VECTOR_HPP_INCLUDED
