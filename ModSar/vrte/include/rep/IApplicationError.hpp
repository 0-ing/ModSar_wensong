//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file        IApplicationError.hpp
/// @brief       Interface for application error
/// @copyright   Robert Bosch GmbH 2018
/// @author

#ifndef DELIVERABLES_SRC_REP_INC_REP_IAPPLICATIONERROR_HPP_
#define DELIVERABLES_SRC_REP_INC_REP_IAPPLICATIONERROR_HPP_

#include "utils/AppInstId.hpp"
#include "utils/IMutex.hpp"

namespace exm
{
namespace rep
{

/// @brief Interface to handle application errors
class IApplicationError
{
public:
    /// @brief different types of application errors
    enum class ApplicationError : uint8_t
    {
        GENERAL_ERROR = 0,      ///< General error
        ENTER_TIMEOUT,          ///< An application didn't start within the given timeout
        EXIT_TIMEOUT,           ///< An application didn't Stop within the given timeout
        UNEXPECTED_TERMINATION, ///< An application terminated unexpectedly
        CHANGE_TO_RUNNING_ERROR, ///< An application didn't change to running state correctly
        CHANGE_TO_TERMINATING_ERROR,        ///< An application didn't change to terminating state correctly
        TERMINATE_TIMEOUT_ERROR, ///< An application didn't terminate due to a timeout handling error
        TERMINATE_ERROR,         ///< An application didn't terminate
        FATAL_ERROR             ///< A fatal error occured during an operation on this application 
    };

    static const char * errorToString(const ApplicationError errorCode){

        const char* ret = "Unknown Error";
        switch (errorCode) {
            case ApplicationError::GENERAL_ERROR:
            {
                ret = "GENERAL_ERROR";
                break;
            }
            case ApplicationError::ENTER_TIMEOUT:
            {
                ret = "ENTER_TIMEOUT";
                break;
            }
            case ApplicationError::EXIT_TIMEOUT:
            {
                ret = "EXIT_TIMEOUT";
                break;
            }
            case ApplicationError::UNEXPECTED_TERMINATION:
            {
                ret = "UNEXPECTED_TERMINATION";
                break;
            }
            case ApplicationError::CHANGE_TO_RUNNING_ERROR:
            {
                ret = "CHANGE_TO_RUNNING_ERROR";
                break;
            }
            case ApplicationError::CHANGE_TO_TERMINATING_ERROR:
            {
                ret = "CHANGE_TO_TERMINATING_ERROR";
                break;
            }
            case ApplicationError::TERMINATE_TIMEOUT_ERROR:
            {
                ret = "TERMINATE_TIMEOUT_ERROR";
                break;
            }
            case ApplicationError::TERMINATE_ERROR:
            {
                ret = "TERMINATE_ERROR";
                break;
            }
            case ApplicationError::FATAL_ERROR:
            {
                ret = "FATAL_ERROR";
                break;
            }
            default: 
            {
                ret = "Unknown Error";
                break;
            }
        }
        return ret;    
    };

    /// @brief Destructor
    virtual ~IApplicationError() {} // Not covered: Deleting destructors of pure virtual base classes can not be called.

    /// @brief Report application error
    /// @param errortype Type of the error
    /// @param appid Application that generated the error
    /// @param errordata Debug data
    virtual void report(ApplicationError errortype, AppInstId appid,  const void* const errordata) = 0;
};

/// @brief Global function to report an application error in the system
/// @warning file descriptor lock may already be in use, hence it is to be ensured that it is not locked before locking!
extern void ErrorApp(IApplicationError::ApplicationError errortype, AppInstId appid,  const void* const errordata, utils::IMutex& fdlock);

}
}

#endif
