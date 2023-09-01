#ifndef IMPL_TYPE_SWPACKAGEINFOTYPE_H
#define IMPL_TYPE_SWPACKAGEINFOTYPE_H
/***********************************************************************************************************************
 *
 * COPYRIGHT RESERVED, Robert Bosch GmbH, 2018. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
 * All rights reserved in the event of the grant of a patent, utility model or design.
 *
 ***********************************************************************************************************************
 *
 * \\file    impl_type_swpackageinfotype.h
 * \\authors This file was generated with VRTE DataTypes Generator 
 *
 **********************************************************************************************************************/
#include <cstdint>
#include "impl_type_swpackagestatetype.h"
#include "impl_type_transferidtype.h"
#include "impl_type_strongrevisionlabelstring.h"
#include "impl_type_swnametype.h"

/***********************************************************************************************************************
 *
 * Typedefs
 *
 **********************************************************************************************************************/
using SwPackageInfoType = struct SwPackageInfoType {
                             SwNameType Name;
                             StrongRevisionLabelString Version;
                             TransferIdType TransferID;
                             uint64_t ConsecutiveBytesReceived;
                             uint64_t ConsecutiveBlocksReceived;
                             SwPackageStateType State;
                           };

#endif

