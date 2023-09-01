//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/db/service.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_UCM_LIB_SWC_DB__SERVICE_H_
#define UCM_AAP_LIBRARY_UCM_LIB_SWC_DB__SERVICE_H_

#include <mutex>
#include <vector>
#include <memory>
#include <type_traits>

#include "ucm/mock/sequence.h"

#include "ucm/lib/log/logger.h"
#include "ucm/lib/swc/db/backend.h"
#include "ucm/lib/swc/db/transaction.h"
#include "ucm/lib/app/service.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {


class Service final
      : public app::Service
      , virtual protected ucm::mock::Sequence
{

public:
    explicit Service()
        : app::Service("sdb::Service")
    {
    }

    Service(Service     &&) = delete;
    Service(Service const&) = delete;

    Service& operator=(Service     &&) = delete;
    Service& operator=(Service const&) = delete;

    ~Service() = default;

    Transaction wr_transaction() {return pop<Transaction>();}
    Transaction rd_transaction() {return pop<Transaction>();}

    void backend(std::unique_ptr<Backend>&&) {return pop<void>();}

private:
    std::vector<std::unique_ptr<Backend>> backends_{};

    bool startoff_nolock() noexcept {return pop<bool>();}
    bool shutdown_nolock() noexcept {return pop<bool>();}
    bool setup_nolock()    noexcept {return pop<bool>();}
};


}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_UCM_LIB_SWC_DB__SERVICE_H_
