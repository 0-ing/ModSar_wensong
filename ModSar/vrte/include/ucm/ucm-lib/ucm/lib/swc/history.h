//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
/// @file         ucm/lib/swc/history.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       HBE1LUD
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_UCM_LIB_SWC_HISTORY_H_
#define UCM_AAP_LIBRARY_UCM_LIB_SWC_HISTORY_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/ara/ara_types.h"

#include "ucm/lib/swc/types.h"
#include "ucm/lib/swc/depunit.h"
#include "ucm/lib/swc/db/transaction.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {

// SWS_UCM_00115 GetHistory
// SWS_UCM_00004 GetSwClusterInfo
// SWS_UCM_00030 GetSwClusterChangeInfo
// SWS_UCM_00069 GetSwPackages        (Not primarily related to database API)
// SWS_UCM_00018 GetSwProcessProgress (Not primarily related to database API)
// SWS_UCM_01103 SwPackageInventory (UCM Master)
// SWS_UCM_01247 GetCampaignHistory (UCM Master)

// query activation action history (kUpdate, kInstall, kRemove). Note, this is 
// not the same as the SwClusterInfoStateType.
inline ara::ARATypes::GetHistoryVectorType
    GetHistory (db::Transaction&, tstamp_type)
{
    throw std::runtime_error("not implememted");
}

// Query all packages in state kPresent
inline ara::ARATypes::SwClusterInfoVectorType
    GetSwClusterInfo (db::Transaction&)
{
    throw std::runtime_error("not implememted");
}

// query all packages in state kInstalled, kUpdated and kRemoved
inline ara::ARATypes::SwClusterInfoVectorType
    GetSwClusterChangeInfo (db::Transaction&)
{
    throw std::runtime_error("not implememted");
}

// query all package in state kPresent and get their description
//inline ara::ARATypes::SwDescVectorType
//    GetSwClusterDescription(db::Transaction&)
//{
//    throw std::runtime_error("not implememted");
//}

}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_UCM_LIB_SWC_HISTORY_H_
