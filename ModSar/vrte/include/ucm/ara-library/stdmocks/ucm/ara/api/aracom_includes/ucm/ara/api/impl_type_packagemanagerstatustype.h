#ifndef IMPL_TYPE_PACKAGEMANAGERSTATUSTYPE_H
#define IMPL_TYPE_PACKAGEMANAGERSTATUSTYPE_H
/***********************************************************************************************************************
 *
 * COPYRIGHT RESERVED, Robert Bosch GmbH, 2018. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
 * All rights reserved in the event of the grant of a patent, utility model or design.
 *
 ***********************************************************************************************************************
 *
 * \\file    impl_type_packagemanagerstatustype.h
 * \\authors This file was generated with VRTE DataTypes Generator 
 *
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 * Typedefs
 *
 **********************************************************************************************************************/
using PackageManagerStatusType = enum class PackageManagerStatusType:uint8_t {
                                    kIdle = 0, 
                                    kReady = 1, 
                                    kBusy = 2, 
                                    kActivating = 3, 
                                    kActivated = 4, 
                                    kRollingBack = 5, 
                                    kRolledBack = 6, 
                                    kCleaningUp = 7, 
                                    kVerifying = 8
                                  };

#endif

