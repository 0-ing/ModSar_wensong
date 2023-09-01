//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      ILogStaticDataAccessor.hpp
/// @brief     Interface Definition: Log <-> MFE IStaticDataAccessor
/// @copyright Robert Bosch GmbH  2018
/// @author    Jyothi Kuntegowda

#ifndef LOG_ILOGSTATICDATAACCESSOR_HPP_INCLUDED
#define LOG_ILOGSTATICDATAACCESSOR_HPP_INCLUDED

#include <stdint.h>

#include "utils/AppInstId.hpp"
#include "utils/StdReturnType.hpp"
#include "utils/ExecInstanceAttr.hpp"
#include "utils/ApplicationInfo.hpp"

namespace exm
{
namespace log
{
/// @class    ILogStaticDataAccessor
/// @brief    Abstract class which defines the Interface between the Log and the MFE
class ILogStaticDataAccessor
{
public :
    /// @brief Destructor
    virtual ~ILogStaticDataAccessor()
    {
    };

    /// @brief Get the instance/process name for application instance
    /// @param[in]    appId                Application Instance Id
    /// @param[out]   processName          Name of the  Process/Instance
    /// @return  StdReturnType
    /// @retval  OK              OK
    /// @retval  GENERAL_ERROR   Error occurred

    virtual StdReturnType GetProcessName(AppInstId appId, char** processName) = 0;

};/* class ILogStaticDataAccessor */
}/* namespace prd */
}/* namespace exm */
#endif
