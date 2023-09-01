#ifndef IMPL_TYPE_APPLICATIONERRORSTYPE_H
#define IMPL_TYPE_APPLICATIONERRORSTYPE_H
/***********************************************************************************************************************
 *
 * COPYRIGHT RESERVED, Robert Bosch GmbH, 2018. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
 * All rights reserved in the event of the grant of a patent, utility model or design.
 *
 ***********************************************************************************************************************
 *
 * \\file    impl_type_applicationerrorstype.h
 * \\authors This file was generated with VRTE DataTypes Generator 
 *
 **********************************************************************************************************************/
#include <cstdint>

/***********************************************************************************************************************
 *
 * Typedefs
 *
 **********************************************************************************************************************/
using ApplicationErrorsType = enum class ApplicationErrorsType:uint8_t {
                                 Ok = 0U, 
                                 InsufficientMemory = 1U, 
                                 IncorrectBlock = 2U, 
                                 IncorrectSize = 3U, 
                                 InvalidTransferId = 4U, 
                                 OperationNotPermitted = 5U, 
                                 InsufficientData = 6U, 
                                 PackageInconsistent = 7U, 
                                 AuthenticationFailed = 8U, 
                                 OldVersion = 9U, 
                                 GeneralReject = 10U, 
                                 GeneralMemoryError = 11U, 
                                 ServiceBusy = 12U, 
                                 InvalidManifest = 13U, 
                                 NothingToRevert = 14U, 
                                 NotAbleToRevertPackages = 15U, 
                                 CancelFailed = 16U, 
                                 NothingToRollback = 17U, 
                                 NotAbleToRollback = 18U, 
                                 PreActivationFailed = 19U, 
                                 ErrorNoValidProcessing = 20U, 
                                 MissingDependencies = 21U, 
                                 ProcessSwPackageCancelled = 22U, 
                                 ProcessedSoftwarePackageInconsistent = 23U, 
                                 IncompatiblePackageVersion = 24U, 
                                 BlockInconsistent = 25U, 
                                 TransferInterrupted = 26U, 
                                 VerificationFailed = 27U
                               };

#endif

