//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/api/aracom_includes.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_API_ARACOM_INCLUDES_H_
#define UCM_AAP_PKGMANAGER_ARA_API_ARACOM_INCLUDES_H_

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wtype-limits"
#pragma GCC diagnostic ignored "-Wreturn-type"
#pragma GCC diagnostic ignored "-Wswitch-enum"
#pragma GCC diagnostic ignored "-Wswitch-default"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wstack-protector"
#pragma GCC diagnostic ignored "-Wstrict-overflow"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#pragma GCC diagnostic ignored "-Wctor-dtor-privacy"
#pragma GCC diagnostic ignored "-Weffc++"
#include "types.hpp"
#include "impl_type_bytevectortype.h"
#include "impl_type_transferidtype.h"
#include "impl_type_swnamevectortype.h"
#include "impl_type_ucmidentifiertype.h"
#include "impl_type_applicationerrorstype.h"
#include "impl_type_swclusterinfovectortype.h"
#include "impl_type_packagemanagerstatustype.h"
#include "impl_type_swclusterinfotype.h"
#include "impl_type_swpackageinfovectortype.h"
#pragma GCC diagnostic pop

namespace ara    {
namespace ucm    {
namespace pkgmgr {

/** Output structure for GetSwPackages **/
using OutputGetSwPackages = struct OutputGetSwPackages {
    SwPackageInfoVectorType swpackage_info {};
};

/** Output structure for RevertProcessedSwPackages **/
using OutputRevertProcessedSwPackages = struct OutputRevertProcessedSwPackages {
    ApplicationErrorsType error_code;
};

/** Output structure for DeleteTransfer **/
using OutputDeleteTransfer = struct OutputDeleteTransfer {
    ApplicationErrorsType error_code;
};

using OutputTransferData = struct OutputTransferData {
    ApplicationErrorsType error_code;
};

/** Output structure for TransferExit **/
using OutputTransferExit = struct OutputTransferExit {
    ApplicationErrorsType error_code;
};

/** Output structure for TransferStart **/
using OutputTransferStart = struct OutputTransferStart {
    TransferIdType transfer_id;
};

/** Output structure for ProcessSwPackage **/
using OutputProcessSwPackage = struct OutputProcessSwPackage {
    ApplicationErrorsType error_code;
};

/** Output structure for GetId **/
using OutputGetId = struct OutputGetId {
    UCMIdentifierType get_id{};
};

/** Output structure for Activate **/
using OutputActivate = struct OutputActivate {
    ApplicationErrorsType error_code;
};

/** Output structure for Finish **/
using OutputFinish = struct OutputFinish {
    ApplicationErrorsType error_code {};
};

/** Output structure for Cancel **/
using OutputCancel = struct OutputCancel {
    ApplicationErrorsType error_code {};
};

/** Output structure for Rollback **/
using OutputRollback = struct OutputRollback {
    ApplicationErrorsType error_code {};
};

/** Output structure for GetSwClusterChangeInfo **/
using OutputGetSwClusterChangeInfo = struct OutputGetSwClusterChangeInfo {
    SwClusterInfoVectorType swcluster_info {};
};

/** Output structure for GetSwClusterInfo **/
using OutputGetSwClusterInfo = struct OutputGetSwClusterInfo {
    SwClusterInfoVectorType swcluster_info {};
};

/** Output structure for GetSwProcessProgress **/
using OutputGetSwProcessProgress = struct OutputGetSwProcessProgress {
    uint8_t progress;
};

namespace skeleton {
namespace fields   {

using CurrentStatus = ara::com::Decorator<PackageManagerStatusType>;

}    // namespace fields

struct PackageManagementSkeleton
{
    PackageManagementSkeleton(const ara::com::InstanceIdentifier&)
    {
    }

    virtual ~PackageManagementSkeleton() = default;

    virtual ::ara::core::Future<::ara::ucm::pkgmgr::OutputTransferStart>
    TransferStart(const uint64_t input0) = 0;

    virtual ::ara::core::Future<::ara::ucm::pkgmgr::OutputTransferData>
    TransferData(const TransferIdType input0, const ByteVectorType input1,
                 const uint64_t input2) = 0;

    virtual ::ara::core::Future<::ara::ucm::pkgmgr::OutputTransferExit>
    TransferExit(const TransferIdType input0) = 0;

    virtual ara::core::Future<::ara::ucm::pkgmgr::OutputProcessSwPackage>
    ProcessSwPackage(const TransferIdType input0) = 0;

    virtual ara::core::Future<::ara::ucm::pkgmgr::OutputGetId>
    GetId(void) = 0;

    virtual ::ara::core::Future<::ara::ucm::pkgmgr::OutputActivate>
    Activate() = 0;

    virtual ::ara::core::Future<::ara::ucm::pkgmgr::OutputFinish>
    Finish() = 0;

    virtual ::ara::core::Future<::ara::ucm::pkgmgr::OutputCancel>
    Cancel(const TransferIdType input0) = 0;

    virtual ::ara::core::Future<::ara::ucm::pkgmgr::OutputRollback>
    Rollback() = 0;

    virtual ::ara::core::Future<::ara::ucm::pkgmgr::OutputGetSwClusterChangeInfo>
    GetSwClusterChangeInfo() = 0;

    virtual ::ara::core::Future<::ara::ucm::pkgmgr::OutputGetSwClusterInfo>
    GetSwClusterInfo() = 0;

    virtual ::ara::core::Future<::ara::ucm::pkgmgr::OutputGetSwPackages>
    GetSwPackages(void) = 0;

    virtual ::ara::core::Future<
    ::ara::ucm::pkgmgr::OutputRevertProcessedSwPackages>
    RevertProcessedSwPackages(void) = 0;

    virtual ::ara::core::Future<::ara::ucm::pkgmgr::OutputDeleteTransfer>
    DeleteTransfer(const TransferIdType input0) = 0;

    virtual ::ara::core::Future<::ara::ucm::pkgmgr::OutputGetSwProcessProgress>
    GetSwProcessProgress(const TransferIdType input0) = 0;

    /*fields*/
    fields::CurrentStatus CurrentStatus { };

    void OfferService()
    {
    }
    void StopOfferService()
    {
    }
};

}
}
}
}

#endif    // UCM_AAP_PKGMANAGER_ARA_API_ARACOM_INCLUDES_H_
