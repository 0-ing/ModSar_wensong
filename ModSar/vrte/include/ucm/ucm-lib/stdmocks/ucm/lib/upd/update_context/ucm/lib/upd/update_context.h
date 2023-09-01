//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocs/ucm/lib/upd/update_context/ucm/lib/upd/update_context.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_UCM_LIB_UPD__UPDATE_CONTEXT_H_
#define UCM_AAP_LIBRARY_UCM_LIB_UPD__UPDATE_CONTEXT_H_

#include "ucm/lib/ppl/instance.h"
#include "ucm/lib/pkg/mnf/model/manifest.h"

#include "ucm/lib/upd/swpackage.h"
#include "ucm/lib/upd/object_store.h"

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace upd   {

class UpdateContext final : virtual protected ucm::mock::Sequence
{
public:
    UpdateContext() = default;
    explicit UpdateContext(const std::string&) {}

    UpdateContext(UpdateContext     &&) = delete;
    UpdateContext(UpdateContext const&) = delete;

    UpdateContext& operator=(UpdateContext     &&) = delete;
    UpdateContext& operator=(UpdateContext const&) = delete;

    ~UpdateContext() = default;

    SWPackage* swpackage() noexcept
    {
        return pop<SWPackage*>();
    }

    const pkg::mnf::Manifest& manifest() const noexcept
    {
        return pop<pkg::mnf::Manifest&>();
    }

    void swpackage(SWPackage*) noexcept {}

    void manifest(pkg::mnf::Manifest&&) noexcept {}

    ppl::Instance& pipeline() noexcept
    {
        return pop<ppl::Instance&>();
    }

    ObjectStore& object_store() noexcept
    {
        return pop<ObjectStore&>();
    }

    void curritem(const id_type&) noexcept {}

    const id_type& curritem() const noexcept
    {
        return pop<id_type&>();
    }

protected:
    id_type curritem_{0};
    SWPackage* swpackage_{nullptr};
    ObjectStore object_store_{""};
    pkg::mnf::Manifest manifest_{};
    std::shared_ptr<ppl::Instance> pipeline_{};
};

}    // namespace upd
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_UCM_LIB_UPD__UPDATE_CONTEXT_H_
