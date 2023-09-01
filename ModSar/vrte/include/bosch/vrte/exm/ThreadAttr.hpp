//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
/// @file         ThreadAttr.hpp
/// @brief        Provides interfaces to access the user configured thread attributes
/// @author


#ifndef _THREADATTR_HPP_INCLUDED
#define _THREADATTR_HPP_INCLUDED

#include "utils/StdReturnType.hpp"
#include "ThreadAttrParserUtility.hpp"
#include "ThreadAttrParser.hpp"
#include <pthread.h>

namespace bosch
{
namespace vrte
{
namespace exm
{


/// @brief Class which provides interfaces to access the user configured thread attributes
class ThreadAttr
{
public:
    /// @brief Constructor
    ThreadAttr();

    /// @brief Constructor
    /// @param threadAttrRef Thread attribute reference
    ThreadAttr(const char* threadAttrRef);

    /// @brief Destructor
    ~ThreadAttr();

    /// @brief prevent copy construction
    /// @private
    ThreadAttr(const ThreadAttr &other) = delete;

    /// @brief prevent copy assignment
    /// @private
    ThreadAttr& operator=(const ThreadAttr& other) = delete;

    /// @brief Creates a thread
    ///
    /// @param      Reads in the configuration attributes for the given thread attribute reference
    /// @param      threadAttrRef Thread attribute reference
    /// @return     ::exm::StdReturnType
    /// @retval     ::exm::StdReturnType::OK on success
    /// @retval     ::exm::StdReturnType::NOT_APPLICABLE if the thread attribute reference was not found.
    ///                                                  This is not an error, the provided pthread_attr_t will be initialized with the default pthread values.
    /// @retval     All other values: an error occured. The provided pthread_attr_t cannot be used.
    ::exm::StdReturnType readAttr(const char *threadAttrRef);

    /// @brief Gets the pthread attribute holding the read in thread attributes
    /// @return Pointer to pthread attributes
    const pthread_attr_t* getPthreadAttr() const;

    /// @brief Gets the thread name prefix
    /// @return Pointer to string holding thread name prefix
    /// @retval Empty if not configured
    const ThreadNamePrefix* getThreadNamePrefix() const;

    /// @brief Gets the thread runmask
    /// @return Thread runmask
    /// @retval All cores if not configured
    const RunMask* getThreadRunmask() const;

    /// @brief Gets the thread stack size
    /// @return Thread stack size
    /// @retval nullptr if not configured
    const uint32_t* getThreadStackSize() const;

    /// @brief Returns the thread attribute state
    /// @return     ::exm::StdReturnType
    /// @retval     ::exm::StdReturnType::OK on success
    /// @retval     ::exm::StdReturnType::NOT_APPLICABLE if the thread attribute reference was not found.
    ///                                                  This is not an error, the provided pthread_attr_t will be initialized with the default pthread values.
    /// @retval     All other values: an error occured. The provided pthread_attr_t cannot be used.
    ::exm::StdReturnType assertion() const;

private:
    pthread_attr_t pThreadAttr;                             ///< Thread attributes
    ::exm::StdReturnType attrState;                         ///< Attribute state
    ThreadAttrParserUtility parserUtility;                  ///< Thread attribute parser utility
    ThreadAttrParser attrParser;                            ///< Thread attribute parser
};
}
}
}

#endif // _THREADATTR_HPP_INCLUDED
