#ifndef IMPL_TYPE_SWCLUSTERSTATETYPE_H
#define IMPL_TYPE_SWCLUSTERSTATETYPE_H
/***********************************************************************************************************************
 *
 * COPYRIGHT RESERVED, Robert Bosch GmbH, 2018. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
 * All rights reserved in the event of the grant of a patent, utility model or design.
 *
 ***********************************************************************************************************************
 *
 * \\file    impl_type_swclusterstatetype.h
 * \\authors This file was generated with VRTE DataTypes Generator 
 *
 **********************************************************************************************************************/
#include <cstdint>

/***********************************************************************************************************************
 *
 * Typedefs
 *
 **********************************************************************************************************************/
using SwClusterStateType = enum class SwClusterStateType:uint8_t {
                              kPresent = 0U, 
                              kAdded = 1U, 
                              kUpdated = 2U, 
                              kRemoved = 3U
                            };

#endif

