//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/upd/update_context.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_UPD__UPDATE_CONTEXT_H_
#define UCM_AAP_LIBRARY__UCM_LIB_UPD__UPDATE_CONTEXT_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/ppl/instance.h"
#include "ucm/lib/pkg/mnf/model/manifest.h"

#include "ucm/lib/upd/swpackage.h"
#include "ucm/lib/upd/object_store.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace upd   {

class UpdateContext final
{
#if defined(GOOGLE_TEST)
        FRIEND_TEST(Test__ucm_lib_upd__UpdateContext, Simple);
#endif

public:
    explicit UpdateContext(const std::string&);

    UpdateContext(UpdateContext     &&) = delete;
    UpdateContext(UpdateContext const&) = delete;

    UpdateContext& operator=(UpdateContext     &&) = delete;
    UpdateContext& operator=(UpdateContext const&) = delete;

    ~UpdateContext() = default;

    SWPackage* swpackage() noexcept;

    const pkg::mnf::Manifest& manifest() const noexcept;

    void swpackage(SWPackage* swp) noexcept;

    void manifest(pkg::mnf::Manifest&&) noexcept;

    ppl::Instance& pipeline() noexcept;

    ObjectStore& object_store() noexcept;

    void curritem(const id_type& item) noexcept;

    const id_type& curritem() const noexcept;

protected:
    id_type curritem_{0};
    SWPackage* swpackage_{nullptr};
    ObjectStore object_store_;
    pkg::mnf::Manifest manifest_{};
    std::shared_ptr<ppl::Instance> pipeline_{};
};

inline ppl::Instance& UpdateContext::pipeline() noexcept
{
    return *pipeline_;
}

inline ObjectStore& UpdateContext::object_store() noexcept
{
    return object_store_;
}

inline SWPackage* UpdateContext::swpackage() noexcept
{
    return swpackage_;
}

inline void UpdateContext::swpackage(SWPackage* swp) noexcept
{
    swpackage_ = swp;
}

inline const pkg::mnf::Manifest& UpdateContext::manifest() const noexcept
{
    return manifest_;
}

inline void UpdateContext::curritem(const id_type& item) noexcept
{
    curritem_ = item;
}

inline const id_type& UpdateContext::curritem() const noexcept
{
    return curritem_;
}

}    // namespace upd
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_UPD__UPDATE_CONTEXT_H_
