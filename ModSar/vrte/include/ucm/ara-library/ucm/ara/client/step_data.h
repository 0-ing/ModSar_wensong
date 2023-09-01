//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/client/step_data.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_CLIENT_STEP_DATA_H_
#define UCM_AAP_PKGMANAGER_ARA_CLIENT_STEP_DATA_H_

#include <string>
#include <vector>
#include <cstddef>

#include "ucm/lib/utl/file_io.h"
#include "ucm/ara/client/value_pair.h"
#include "ucm/ara/client/aracom_includes.h"

namespace bosch  {
namespace vrte   {
namespace ucm    {
namespace ara    {
namespace client {

struct StepData
{
    using name_type         = std::string;
    using data_type         = ARATypes::ByteVectorType;
    using datasize_type     = std::uint64_t;
    using loglevel_type     = ARATypes::LogLevelType;
    using araerror_type     = ARATypes::ApplicationErrorsType;
    using transferid_type   = ARATypes::TransferIdType;
    using arastatus_type    = ARATypes::PackageManagerStatusType;

    using datasize_pair =
            ValuePair<datasize_type, false, 0>;
    using transferid_pair =
            ValuePair<transferid_type, false, 0>;
    using araerror_pair =
            ValuePair<araerror_type, true, araerror_type::Ok>;
    using loglevel_pair =
            ValuePair<loglevel_type, false, loglevel_type::kVerbose>;
    using arastatus_pair =
            ValuePair<arastatus_type, true, arastatus_type::kIdle>;

    name_type       file_           {};
    name_type       mutex_          {};
    name_type       barrier_        {};
    data_type       tx_data_        {};
    araerror_pair   araerror_       {};
    arastatus_pair  arastatus_      {};
    loglevel_pair   loglevel_       {};
    datasize_pair   data_size_      {};
    datasize_pair   block_size_     {};
    datasize_pair   block_cnt_s_    {};
    datasize_pair   block_cnt_e_    {};
    datasize_pair   file_offt_s_    {};
    datasize_pair   file_offt_e_    {};
    transferid_pair transfer_id_    {};

    std::unique_ptr<ucm::lib::utl::FileIO> file_io_{};
};

}    // namespace client
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_PKGMANAGER_ARA_CLIENT_STEP_DATA_H_
