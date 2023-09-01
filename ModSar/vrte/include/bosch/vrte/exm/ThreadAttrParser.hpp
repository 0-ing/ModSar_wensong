//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
/// @file         ThreadAttrParser.hpp
/// @brief        Provides interfaces to parse a thread attribute
/// @author


#ifndef _THREADATTRPARSER_HPP_INCLUDED
#define _THREADATTRPARSER_HPP_INCLUDED

#include "utils/StdReturnType.hpp"
#include "IThreadAttrParserUtility.hpp"
#include "json/json_parser_interface.h"
#include <pthread.h>

namespace bosch
{
namespace vrte
{
namespace exm
{


/// @brief Class which provides interfaces to parse a thread attribute
class ThreadAttrParser
{
public:
    /// @brief Constructor
    ThreadAttrParser(IThreadAttrParserUtility& parserUtility);

    /// @brief Destructor
    ~ThreadAttrParser();

    /// @brief prevent copy construction
    /// @private
    ThreadAttrParser(const ThreadAttrParser &other) = delete;

    /// @brief prevent copy assignment
    /// @private
    ThreadAttrParser& operator=(const ThreadAttrParser& other) = delete;

    /// @brief      Parses the given thread attribute reference
    /// @param[in]  threadAttrRef Thread attribute reference
    /// @param[out] threadAttr Pointer to pthread attributes
    /// @return     OK on success, GENERAL_ERROR on failure.
    ::exm::StdReturnType parseAttr(const char *threadAttrRef, pthread_attr_t* threadAttr);

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

private:
    ::exm::StdReturnType storeAttr(pthread_attr_t* threadAttr);

    ::exm::StdReturnType storeAttrSchedPol(pthread_attr_t* threadAttr, bool& setinheritsched);

    ::exm::StdReturnType doParsing(const char* threadAttrRef);

    ::exm::StdReturnType verifyJsonParserError(bosch::vrte::json::JsonError const& errorCode);

    IThreadAttrParserUtility& attrParserUtility;            ///< Interface to thread attribute parser utility
    ::exm::utils::AlignedStorage_t<1024U> parserMemory;     ///< Memory space for parsing process
    bosch::vrte::json::JsonParserInterface *jsonParser;     ///< Json parser interface
};
}
}
}

#endif // _THREADATTRPARSER_HPP_INCLUDED
