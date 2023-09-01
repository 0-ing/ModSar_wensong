//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file        IAppContainer.hpp
/// @brief       Abstract interface for application container
/// @copyright   Robert Bosch GmbH 2019
/// @author      Yohan Pistor


#ifndef IAPPCONTAINER_HPP_
#define IAPPCONTAINER_HPP_

#include "utils/AppInstId.hpp"
#include "utils/StdReturnType.hpp"

namespace exm {
namespace utils {

    ///  @brief    Container for application classes. The type T must derive from the AppContainerElement class.
    ///  @tparam   T Type of the container element. It must derive from the AppContainerElement class.
    template<class T>
    class IAppContainer
    {
        public:
            /// @brief Constructor
            IAppContainer() {}

            /// @brief Destructor
            virtual ~IAppContainer() {}

            /// @brief Get an instance of type T by a specific application Id. If this application Id was not found, create a new one with this Id. This method is reentrant.
            /// @warning lifetime of instance_out shall NOT outlive that of AppContainer
            /// @param[in] app_id Application Id to search for.
            /// @param[out] instance_out Where to store the found instance. If it is equal to nullptr, it was not possible to allocate a new element in the container.
            /// @return  StdReturnType
            /// @retval  OK              OK
            /// @retval  Any other value: a critical error happened.
            virtual StdReturnType GetOrCreate(const AppInstId app_id, T** instance_out) = 0;

            /// @brief Get an instance of type T by a specific application Id. This method is reentrant.
            /// @warning lifetime of instance_out shall NOT outlive that of AppContainer
            /// @param[in] app_id Application Id to search for.
            /// @param[out] instance_out Where to store the found instance. If it is equal to nullptr, it was not possible to find a matching element in the container.
            /// @return  StdReturnType
            /// @retval  OK OK
            /// @retval  Any other value: a critical error happened.
            virtual StdReturnType Get(const AppInstId app_id, T** instance_out) = 0;

            /// @brief Get an element from the array given an index, excluding unallocated elements
            /// @warning lifetime of instance_out shall NOT outlive that of AppContainer
            /// @param[in] index Index of the array element
            /// @param[out] instance_out Value at array index
            /// @retval  OK: free element found.
            /// @retval  INVALID_ARGUMENTS: no free element in array.
            virtual StdReturnType GetElement(uint32_t index, T** instance_out) = 0;
    };

}
}

#endif
