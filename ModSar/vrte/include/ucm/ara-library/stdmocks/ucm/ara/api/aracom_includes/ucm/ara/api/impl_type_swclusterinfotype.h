#ifndef IMPL_TYPE_SWCLUSTERINFOTYPE_H
#define IMPL_TYPE_SWCLUSTERINFOTYPE_H
/***********************************************************************************************************************
 *
 * COPYRIGHT RESERVED, Robert Bosch GmbH, 2018. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
 * All rights reserved in the event of the grant of a patent, utility model or design.
 *
 ***********************************************************************************************************************
 *
 * \\file    impl_type_swclusterinfotype.h
 * \\authors This file was generated with VRTE DataTypes Generator 
 *
 **********************************************************************************************************************/
#include "impl_type_swclusterstatetype.h"
#include "impl_type_strongrevisionlabelstring.h"
#include "impl_type_swnametype.h"

/***********************************************************************************************************************
 *
 * Typedefs
 *
 **********************************************************************************************************************/
using SwClusterInfoType = struct SwClusterInfoType {
                             SwNameType Name;
                             StrongRevisionLabelString Version;
                             SwClusterStateType State;
                           };

#endif

