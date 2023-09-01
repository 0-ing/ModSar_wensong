//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/client/ara_proxy.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_CLIENT_ARA_PROXY_H_
#define UCM_AAP_PKGMANAGER_ARA_CLIENT_ARA_PROXY_H_

#include <chrono>
#include <memory>

#include "ucm/lib/log/logger.h"
#include "ucm/ara/lib/araconv.h"
#include "ucm/ara/client/value_pair.h"
#include "ucm/ara/client/aracom_includes.h"

namespace bosch  {
namespace vrte   {
namespace ucm    {
namespace ara    {
namespace client {

class AraProxy final
{
    constexpr static const auto timeout() noexcept
    {
        return std::chrono::seconds(3600);
    }

    constexpr static const char* ara_instance_id = "1";
    constexpr static const char* ara_mq_app_name
                                    = "/UpdateConfigurationManagement";

public:
    using result_type   = ::ara::core::future_status;
    using instance_type = ::ara::com::InstanceIdentifier;
    using araproxy_type = ::ara::ucm::pkgmgr::proxy::PackageManagementProxy;

    explicit AraProxy();

    AraProxy(AraProxy     &&) = delete;
    AraProxy(AraProxy const&) = delete;

    AraProxy& operator=(AraProxy     &&) = delete;
    AraProxy& operator=(AraProxy const&) = delete;

    ~AraProxy();

    ARATypes::TransferIdType TransferStart(const uint64_t size);

    ARATypes::ApplicationErrorsType TransferData(
            const ARATypes::TransferIdType input0,
            const ByteVectorType input1,
            const uint64_t input2);

    ARATypes::ApplicationErrorsType TransferExit(
            const ARATypes::TransferIdType& input0);

    ARATypes::ApplicationErrorsType ProcessSwPackage(
            const ARATypes::TransferIdType& input0);

    ARATypes::ApplicationErrorsType DeleteTransfer(
                const ARATypes::TransferIdType& input0);

    ARATypes::PackageManagerStatusType CurrentStatus();

    UCMIdentifierType GetId();

    ARATypes::ApplicationErrorsType Activate();

    ARATypes::ApplicationErrorsType Finish();

    ARATypes::ApplicationErrorsType Cancel(
            const ARATypes::TransferIdType& input0);

    ARATypes::ApplicationErrorsType Rollback();

    SwClusterInfoVectorType GetSwClusterChangeInfo();

    SwClusterInfoVectorType GetSwClusterInfo();

    SwPackageInfoVectorType GetSwPackages();

    ARATypes::ApplicationErrorsType RevertProcessedSwPackages();

    std::uint8_t GetSwProcessProgress(const ARATypes::TransferIdType&);

    void CurrentStatusReceived();

private:
    instance_type                  instance_;
    mutable std::mutex             mutex_{};
    std::unique_ptr<araproxy_type> araproxy_{};
    void SubscribeService();
};


}    // namespace client
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_PKGMANAGER_ARA_CLIENT_ARA_PROXY_H_
