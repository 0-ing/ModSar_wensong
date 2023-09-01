//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/vrte/cfg/table.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_vrte_cfg

#ifndef UCM_AAP_PROCESSING_VRTE__UCM_VRTE_CFG__TABLE_H_
#define UCM_AAP_PROCESSING_VRTE__UCM_VRTE_CFG__TABLE_H_

/// @addtogroup bosch_vrte_ucm_vrte_cfg
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace vrte  {
namespace cfg   {

/// @brief Configuration table for IPC mechanism.
///

struct Table final
{
    int  dlt_loglevel_{6}; // corresponds to ara::log::LogLevel::kVerbose;
    bool fc_exm_enable_{true};
    bool fc_sec_enable_{true};
    bool fc_stm_enable_{true};
    bool fc_exm_ipc_enable_{true};
    bool fc_sec_ipc_enable_{false};
    bool fc_stm_ipc_enable_{false};
};

}    // namespace cfg
}    // namespace vrte
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_PROCESSING_VRTE__UCM_VRTE_CFG__TABLE_H_
