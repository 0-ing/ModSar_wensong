//=============================================================================
//  C O P Y R I G H T
//-----------------------------------------------------------------------------
//  Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
//  The reproduction, distribution and utilization of this file as
//  well as the communication of its contents to others without express
//  authorization is prohibited. Offenders will be held liable for the
//  payment of damages. All rights reserved in the event of the grant
//  of a patent, utility model or design.
//=============================================================================
//  P R O J E C T   I N F O R M A T I O N
//-----------------------------------------------------------------------------
//       Projectname: AOS Carma
//  Target system(s):
//       Compiler(s): C++11 compliant
//=============================================================================
//  N O T E S
//-----------------------------------------------------------------------------
//  Notes:
//=============================================================================
//  I N I T I A L   A U T H O R   I D E N T I T Y
//-----------------------------------------------------------------------------
//        Name: Baumgaertner Rainer
//  Department: CC-AD/ESW1
//=============================================================================
/// @swcomponent carma_ara
/// @file runtime.hpp
/// @brief Implementation of the ara::com API.
//=============================================================================

///@todo: remove from public interface once API update is final
#ifndef ARA_RUNTIME_HPP_INCLUDED
#define ARA_RUNTIME_HPP_INCLUDED

#include "ara/com/com_error_domain.h"
#include "ara/com/types.h"
#include "ara/core/instance_specifier.h"
#include "ara/core/result.h"

#include <atomic>
#include <cstdint>
#include <string>

namespace ara
{
class Runtime
{
public:
    // forward declaration for runtime factories
    /// @note don't use them from whitin the ara component, since the factories are defined in a different component and
    /// would result in cyclic link dependencies
    static Runtime& GetInstance(const std::string& f_name = "dummy");
    static Runtime& GetInstance(int argc, const char** argv);
};

} // namespace ara

#endif
