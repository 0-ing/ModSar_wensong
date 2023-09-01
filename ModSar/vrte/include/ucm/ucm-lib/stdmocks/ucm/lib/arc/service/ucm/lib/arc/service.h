//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/arc/service.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       dsh8cob
/// @version
/// @remarks


#ifndef UCM_AAP_LIBRARY_LIB_ARC_SERVICE_H_
#define UCM_AAP_LIBRARY_LIB_ARC_SERVICE_H_

#include <array>
#include <memory>

#include "ucm/mock/sequence.h"

#include "ucm/lib/arc/factory.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace arc   {

class Service final
    : public app::Service
    , virtual protected ucm::mock::Sequence
{
public:

    explicit Service()
        : app::Service("arc::Service")
    {}

    Service(const Service& other) = delete;
    Service& operator=(const Service&) = delete;

    Service(Service&&) = default;
    Service& operator=(Service&&) = default;

    ~Service() = default;

    std::unique_ptr<Archive> archive(std::string const& type)
    {
        Factory& arcf = pop<Factory&>();
        return arcf.archive(type);
    }

    void register_factory(std::unique_ptr<Factory>&&) { pop<void>(); }

protected:
    bool setup_nolock()    noexcept override { return true; }
    bool startoff_nolock() noexcept override { return true; }
    bool shutdown_nolock() noexcept override { return true; }
};


}    // namespace arc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_ARC_SERVICE_H_
