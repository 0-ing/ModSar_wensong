//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file        Reporter.hpp
/// @brief       handle ExM internal errors
/// @copyright   Robert Bosch GmbH 2018
/// @author

#ifndef DELIVERABLES_SRC_REP_INC_REP_REPORTER_HPP_
#define DELIVERABLES_SRC_REP_INC_REP_REPORTER_HPP_

#include "IApplicationError.hpp"
#include "ICriticalError.hpp"
#include "prd_base/IExecInstanceStaticDataAccessor.hpp"
#include "utils/IMutex.hpp"

namespace exm
{
namespace rep
{

/// @class    Reporter
/// @brief    handle critical error and application error
class Reporter : public IApplicationError, public ICriticalError
{
public:
    /// @brief      constructor
    /// @param stat interface to MFE
    /// @param fdslock_ reference to FDS lock
    Reporter(prd::IExecInstanceStaticDataAccessor& stat, utils::IMutex& fdslock_);

    /// @brief      destructor
    virtual ~Reporter() {}; // Not covered: Only the deleting destructor is not covered. We don't use the heap.

    /// @brief No copy constructor needed.
    Reporter(const Reporter&) = delete;

    /// @brief No copy assignment operator needed.
    Reporter& operator=(const Reporter&) = delete;

    /// @brief      report application error
    ///     - This is used to report application specific errors
    ///     - This error is invoked when ExM faces any errors while handling an application instance
    ///     - examples of application errors:
    ///          - error while starting an application instance
    ///          - error while setting dependency to an application instance
    /// @param      errortype = type of application error. e.g. UNEXPECTED_TERMINATION
    /// @param      appid = application id internally maintained by ExM for each application instance
    /// @param      errordata = data relevant for the error. The actual content depend upon the error being reported. Below are some examples:
    ///                  - for UNEXPECTED_TERMINATION, errordata will be a pointer to siginfo_t structure
    virtual void report(const ApplicationError errortype, const AppInstId appid, const void* const errordata) override;

    /// @brief      report critical error
    ///     - This is used to report generic errors which are not linked to an application
    ///     - some examples are:
    ///          - Invalid parameters passed to a function
    ///          - system call returned an error value
    /// @param      errortype = type of critical error
    virtual void report(const CriticalError errortype) override;

private:
    prd::IExecInstanceStaticDataAccessor& istatDataAccessor; ///< @brief interface to MFE
    utils::IMutex& fdsLock;                                  ///< @brief reference to file descriptor server lock variable
};

}
}

#endif
