//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/pkgmanager_ara.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_H_
#define UCM_AAP_PKGMANAGER_ARA_H_

#include <memory>

#include "ucm/lib/app/module.h"
#include "ucm/ara/api/server.h"
#include "ucm/lib/app/supp_module.h"
#include "ucm/lib/app/module_task.h"
#include "ucm/lib/dev/memory_layout.h"

/// @addtogroup bosch_vrte_ucm_ara
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace ara   {

/// @class PkgmanagerARA
/// @ingroup bosch_vrte_ucm_ara
/// @brief This is the interface for setup,configuration 
/// and shutdown of the ucm-aap-pkgmanager-ara module.
///

class PkgmanagerARA : public ucm::lib::app::SuppModule
{
    
public:
    /// Explicit parameterized constructor
    explicit PkgmanagerARA(ucm::lib::app::CoreContext& context,
                           ucm::lib::upd::TransactionsManager& tmanager);
    
    /// Copy Semantics
    PkgmanagerARA(PkgmanagerARA&&) noexcept = delete;
    
    /// Copy Semantics
    PkgmanagerARA& operator=(PkgmanagerARA&&) = delete;
    
    /// Move Semantics
    PkgmanagerARA(const PkgmanagerARA&) = delete;
    
    /// Move Semantics
    PkgmanagerARA& operator=(const PkgmanagerARA&) = delete;
    
    /// Virtual destructor
    virtual ~PkgmanagerARA() = default;

protected:
    /// \brief Method to return Configuration status of the module.
    /// \return Status of configuration setup (always returns TRUE)
    virtual bool setup_config_derived() noexcept override;
    
    /// \brief Method to return setup of the module.
    /// \return Status of setup (always returns TRUE)
    virtual bool setup_module_derived() noexcept override;
    
    /// \brief Method to create the server and offer services.
    /// \return  TRUE: If creation and startoff of api::server was successful. 
    ///          FALSE: If creation or startoff api::server failed.
    virtual bool startoff_module_derived() noexcept override;

    /// \brief Method to shutdown api::server.
    /// \return  TRUE: If shutdown of api::server was successful. 
    ///          FALSE: If shutdown of api::server failed.
    virtual bool shutdown_module_derived() noexcept override;

private:
    std::unique_ptr<api::Server> server_{};/// Unique pointer to Server Instance
};

}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_PKGMANAGER_ARA_H_
