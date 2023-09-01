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

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/app/service.h"
#include "ucm/lib/swc/db/backend.h"
#include "ucm/lib/swc/db/transaction.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {


class Service final : public app::Service
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_swc_db__Service, CTor);
    FRIEND_TEST(Test_ucm_lib_swc_db__Service, Setup);
    FRIEND_TEST(Test_ucm_lib_swc_db__Service, Backend);
    FRIEND_TEST(Test_ucm_lib_swc_db__Service, Startoff);
    FRIEND_TEST(Test_ucm_lib_swc_db__Service, Shutdown);
    FRIEND_TEST(Test_ucm_lib_swc_db__Service, WrTransaction);
    FRIEND_TEST(Test_ucm_lib_swc_db__Service, RdTransaction);
#endif

public:
    explicit Service();

    Service(Service     &&) = delete;
    Service(Service const&) = delete;

    Service& operator=(Service     &&) = delete;
    Service& operator=(Service const&) = delete;

    ~Service() = default;

    Transaction wr_transaction();
    Transaction rd_transaction();

    void backend(std::unique_ptr<Backend>&&);

protected:
    bool setup_nolock()    noexcept override;
    bool startoff_nolock() noexcept override;
    bool shutdown_nolock() noexcept override;

private:
    std::vector<std::unique_ptr<Backend>> backends_{};
};

}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_UCM_LIB_SWC_DB__SERVICE_H_
