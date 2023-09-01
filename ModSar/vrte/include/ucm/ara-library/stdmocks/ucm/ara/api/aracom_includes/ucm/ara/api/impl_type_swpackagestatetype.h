#ifndef IMPL_TYPE_SWPACKAGESTATETYPE_H
#define IMPL_TYPE_SWPACKAGESTATETYPE_H
/***********************************************************************************************************************
 *
 * COPYRIGHT RESERVED, Robert Bosch GmbH, 2018. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
 * All rights reserved in the event of the grant of a patent, utility model or design.
 *
 ***********************************************************************************************************************
 *
 * \\file    impl_type_swpackagestatetype.h
 * \\authors This file was generated with VRTE DataTypes Generator 
 *
 **********************************************************************************************************************/
#include <cstdint>

/***********************************************************************************************************************
 *
 * Typedefs
 *
 **********************************************************************************************************************/
using SwPackageStateType = enum class SwPackageStateType:uint8_t {
                              kTransferring = 0U, 
                              kTransferred = 1U, 
                              kProcessing = 2U, 
                              kProcessed = 3U, 
                              kProcessingStream = 4U
                            };

#endif

