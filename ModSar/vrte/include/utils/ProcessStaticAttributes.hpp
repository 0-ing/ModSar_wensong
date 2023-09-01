//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
/// @file      ProcessStaticAttributes.hpp
/// @brief     attributes of a process
/// @author    Anjana Devi Narayanan
//=============================================================================
#ifndef PROCESSSTATICATTRIBUTES_HPP_INCLUDED
#define PROCESSSTATICATTRIBUTES_HPP_INCLUDED

#include "PrimaryConfig.hpp"
#include "StdReturnType.hpp"
#include "String.hpp"
#include "vector.hpp"
#include "ExecInstanceAttr.hpp"

namespace exm
{
namespace utils
{
typedef utils::String<utils::MAX_LENGTH_OF_PATH> exeString;
typedef utils::String<utils::MAX_DIR_SIZE> wdString;;
/// @brief Contains all necessary attributes to spawn a Process.
class ProcessStaticAttributes
{
    public:
       
    AppInstId appId;
    exeString execName;
    exeString execPath;
    wdString execCwd;
    char** execArgv;
    uint32_t argvCount;
    char** execEnvVars;
    uint32_t envCount;
    ExecInstanceAttr execInstAttrinfo;

};

}
}

#endif