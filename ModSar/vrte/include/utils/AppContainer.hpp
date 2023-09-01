//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file        AppContainer.hpp
/// @brief       Abstract interface between APL and PRT
/// @copyright   Robert Bosch GmbH 2018
/// @author      Arnaud Riess

#ifndef APPCONTAINER_HPP_
#define APPCONTAINER_HPP_

#include "utils/IAppContainer.hpp"
#include "utils/Mutex.hpp"
#include "utils/Try.hpp"

namespace exm
{
namespace utils
{

/// @brief    Container element base class for application classes.
class AppContainerElement
{
public:
    /// @brief Default destructor
    virtual ~AppContainerElement()
    {
    } // Not covered: Only the deleting destructor is not covered. We don't use the heap.
    /// @brief Default Constructor
    AppContainerElement() {}
    /// @brief Is this object corresponding to an application ID
    /// @param[in] app_id_ Application Id to match with.
    /// @return  bool
    ///      TRUE :if app_id_ matches to this object
    ///      FALSE :if app_id_ not match
    virtual bool isMatching(const AppInstId app_id_) = 0;

    /// @brief Sets this object to an application ID
    /// @param[in] app_id_ Application Id to set.
    virtual void setAppId(const AppInstId app_id_) = 0;
};

///  @brief    Container for application classes. The type T must derive from the
///  AppContainerElement class.
///  @tparam   T Type of the container element. It must derive from the AppContainerElement class.
///  @tparam   MAX_ELEMENTS Max number of elements of type T in the container.
template <class T, uint32_t MAX_ELEMENTS>
class AppContainer : public IAppContainer<T>
{
public:
    /// @brief Constructor
    AppContainer()
        : IAppContainer<T>(), array(), m(), next_free_instance(0U)
    {
        // left empty
    }

    /// @brief Destructor
    ~AppContainer()
    {
        // left empty
    } // Not covered: Only the deleting destructor is not covered. We don't use the heap.

    /// @brief No copy constructor  needed.
    AppContainer(const AppContainer&) = delete;

    /// @brief No copy assignment operator needed.
    AppContainer& operator=(const AppContainer&) = delete;

    /// @brief Get an instance of type T by a specific application Id. If this application Id was
    /// not found, create a new one with this Id. This method is reentrant.
    /// @warning lifetime of instance_out shall NOT outlive that of AppContainer
    /// @param[in] app_id Application Id to search for.
    /// @param[out] instance_out Where to store the found instance. If it is equal to nullptr, it
    /// was not possible to allocate a new element in the container.
    /// @return  StdReturnType
    /// @retval  OK              OK
    /// @retval  Any other value: a critical error happened.
    virtual StdReturnType GetOrCreate(const AppInstId app_id, T** instance_out) override
    {
        ASSERT_ARG(nullptr != instance_out);

        T* instance = nullptr;
        StdReturnType ret = StdReturnType::OK;

        if (m.Lock() != StdReturnType::OK)
        {
            ret = StdReturnType::FATAL_ERROR;
        }
        else
        {
            instance = GetNoLock(app_id);

            if (instance == nullptr)
            {
                instance = CreateNoLock(app_id);
            }

            if (m.Unlock() != StdReturnType::OK)
            {
                ret = StdReturnType::FATAL_ERROR;
            }
        }

        *instance_out = instance;

        return ret;
    }

    /// @brief Get an instance of type T by a specific application Id. This method is reentrant.
    /// @warning lifetime of instance_out shall NOT outlive that of AppContainer
    /// @param[in] app_id Application Id to search for.
    /// @param[out] instance_out Where to store the found instance. If it is equal to nullptr, it
    /// was not possible to find a matching element in the container.
    /// @return  StdReturnType
    /// @retval  OK OK
    /// @retval  Any other value: a critical error happened.
    virtual StdReturnType Get(const AppInstId app_id, T** instance_out) override
    {
        ASSERT_ARG(nullptr != instance_out);

        T* instance = nullptr;
        StdReturnType ret = StdReturnType::OK;

        if (m.Lock() != StdReturnType::OK)
        {
            ret = StdReturnType::FATAL_ERROR;
        }
        else
        {
            instance = GetNoLock(app_id);

            if (m.Unlock() != StdReturnType::OK)
            {
                ret = StdReturnType::FATAL_ERROR;
            }
        }

        *instance_out = instance;

        return ret;
    }

    /// @brief Get an element from the array given an index, excluding unallocated elements
    /// @warning lifetime of instance_out shall NOT outlive that of AppContainer
    /// @param[in] index Index of the array element
    /// @param[out] instance_out Value at array index
    /// @retval  OK: free element found.
    /// @retval  INVALID_ARGUMENTS: no free element in array.
    virtual StdReturnType GetElement(uint32_t index, T** instance_out) override
    {
        if (nullptr == instance_out)
        {
            return StdReturnType::INVALID_ARGUMENTS;
        }

        if (index < next_free_instance)
        {
            *instance_out = &array[index]; // PRQA S 2516 # Lifetime of instance_out is shorter than
                                           // that of AppContainer
            return StdReturnType::OK;
        }
        else
        {
            *instance_out = nullptr;
            return StdReturnType::INVALID_ARGUMENTS;
        }
    }

    /// @brief Get an element from the array given an index, including unallocated elements
    /// @warning lifetime of instance_out shall NOT outlive that of AppContainer
    /// @param[in] index Index of the array element
    /// @param[out] instance_out Value at array index
    /// @retval  OK: free element found.
    /// @retval  INVALID_ARGUMENTS: no free element in array.
    StdReturnType GetElementWoLimit(uint32_t index, T** instance_out)
    {
        if (nullptr == instance_out)
        {
            return StdReturnType::INVALID_ARGUMENTS;
        }

        if (index < MAX_ELEMENTS)
        {
            *instance_out = &array[index]; // PRQA S 2516 # Lifetime of instance_out is shorter than
                                           // that of AppContainer
            return StdReturnType::OK;
        }
        else
        {
            *instance_out = nullptr;
            return StdReturnType::INVALID_ARGUMENTS;
        }
    }

private:
    /// @brief Get an instance of type T by a specific application Id.
    /// @warning lifetime of returned pointer shall NOT outlive that of AppContainer
    /// @param[in] app_id Application Id to search for.
    /// @return  Found element
    /// @retval  nullptr Not possible to find a matching element.
    /// @retval  Any other value: matching element found.
    T* GetNoLock(const AppInstId app_id)
    {
        T* instance = nullptr;

        for (uint32_t i = 0U; i < next_free_instance; i++)
        {
            AppContainerElement& element = array[i];
            if (element.isMatching(app_id))
            {
                instance = &array[i];
                break;
            }
        }

        return instance;
    }

    /// @brief Get an instance of type T by a specific application Id. If this application Id was
    /// not found, create a new one with this Id.
    /// @warning lifetime of returned pointer shall NOT outlive that of AppContainer
    /// @param[in] app_id Application Id to search for.
    /// @return  Found element
    /// @retval  nullptr Not possible to create a new element.
    /// @retval  Any other value: matching element found.
    T* CreateNoLock(const AppInstId app_id)
    {
        T* instance = nullptr;

        if (next_free_instance < MAX_ELEMENTS)
        {
            AppContainerElement& element = array[next_free_instance];
            element.setAppId(app_id);

            instance = &array[next_free_instance];
            next_free_instance++;
        }

        return instance;
    }

    T array[MAX_ELEMENTS];       ///< Array of elements.
    utils::Mutex m;              ///< Guarding mutex.
    uint32_t next_free_instance; ///< Next free instance in the array.
};
}
}

#endif
