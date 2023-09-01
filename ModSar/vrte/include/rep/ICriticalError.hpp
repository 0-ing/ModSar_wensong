//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file        ICriticalError.hpp
/// @brief       Interface for critical error
/// @copyright   Robert Bosch GmbH 2018
/// @author


#ifndef DELIVERABLES_SRC_REP_INC_REP_ICRITICALERROR_HPP_
#define DELIVERABLES_SRC_REP_INC_REP_ICRITICALERROR_HPP_

#include <stdint.h>
#include "utils/IMutex.hpp"

namespace exm
{
namespace rep
{

/// @class    ICriticalError
/// @brief    interface to handle critical errors
class ICriticalError
{
public:
    /// @brief different types of critical errors
    enum class CriticalError:uint8_t
    {
        GENERAL_ERROR = 0,
        SERVICE_ERROR = 1,
        OUT_OF_RESOURCE = 2,
        TIMEOUT = 3,
        INVALID_ARGUMENT = 4,
        POSIX_ERROR = 5,
        INVALID_STATE = 6,
        STARTUP_ERROR = 7,
        MUTEX_ERROR = 8
    };

    static const char * errorToString(const CriticalError errorCode){

        const char* ret = "Unknown Error";

        switch (errorCode)
        {
            case CriticalError::GENERAL_ERROR:
            {
                ret = "GENERAL_ERROR";
                break;  
            }
            case CriticalError::SERVICE_ERROR:
            {
                ret = "SERVICE_ERROR";
                break;  
            }
            case CriticalError::OUT_OF_RESOURCE:
            {
                ret = "OUT_OF_RESOURCE";
                break;  
            }
           case CriticalError::TIMEOUT:
            {
                ret = "TIMEOUT";
                break;  
            }
            case CriticalError::INVALID_ARGUMENT:
            {
                ret = "INVALID_ARGUMENT";
                break;  
            }
            case CriticalError::POSIX_ERROR:
            {
                ret = "POSIX_ERROR";
                break;  
            }
            case CriticalError::INVALID_STATE:
            {
                ret = "INVALID_STATE";
                break;  
            }
            case CriticalError::STARTUP_ERROR:
            {
                ret = "STARTUP_ERROR";
                break;  
            }
            case CriticalError::MUTEX_ERROR:
            {
                ret = "MUTEX_ERROR";
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

    /// @brief report critical error
    /// @param errortype  error type to be reported
    virtual void report(const CriticalError errortype) = 0;

    /// @brief      destructor
    virtual ~ICriticalError() {} // Not covered: Deleting destructors of pure virtual base classes can not be called.
};


/// @brief Global function to report a critical error in the system
/// @warning file descriptor lock may already be in use, hence it is to be ensured that it is not locked before locking!
extern void ErrorCritical(ICriticalError::CriticalError errortype, utils::IMutex& fdlock);

}
}

#endif
