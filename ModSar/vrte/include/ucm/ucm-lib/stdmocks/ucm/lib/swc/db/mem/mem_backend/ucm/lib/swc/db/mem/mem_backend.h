//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/db/mem/mem_backend.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_UCM_LIB_SWC_DB_MEM__MEM_BACKEND_H_
#define UCM_AAP_LIBRARY_UCM_LIB_SWC_DB_MEM__MEM_BACKEND_H_

#include <string>
#include <atomic>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/mock/sequence.h"
#include "ucm/lib/swc/irecord.h"
#include "ucm/lib/swc/hrecord.h"
#include "ucm/lib/swc/frecord.h"

#include "ucm/lib/swc/db/backend.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {
namespace mem   {

class MEM_Backend final
      : public Backend
      , protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_swc_db_mem__MEM_Backend, CTor);
#endif

    constexpr static const char *backend_name = "SwC_MEM";
    constexpr static const char *backend_specs = "memory";
    constexpr static const bool  irecord_enable = true;
    constexpr static const bool  hrecord_enable = true;
    constexpr static const bool  frecord_enable = true;

public:
    explicit MEM_Backend()
    : Backend(backend_name, backend_specs,
                  irecord_enable, hrecord_enable, frecord_enable)
    {
        pop<void>();
    }

    MEM_Backend(MEM_Backend     &&) = delete;
    MEM_Backend(MEM_Backend const&) = delete;

    MEM_Backend& operator=(MEM_Backend     &&) = delete;
    MEM_Backend& operator=(MEM_Backend const&) = delete;

    virtual ~MEM_Backend();

    virtual void startoff() override {pop<void>();}
    virtual void shutdown() override  {pop<void>();}

    virtual std::unique_ptr<Handle> select_handle() override  {return pop<std::unique_ptr<Handle>>();}
    virtual std::unique_ptr<Handle> update_handle() override  {return pop<std::unique_ptr<Handle>>();}

private:
    unique_type iunique_{0};
    unique_type hunique_{0};
    unique_type funique_{0};
    std::vector<IRecord> irecords_{};
    std::vector<HRecord> hrecords_{};
    std::vector<FRecord> frecords_{};
};

}    // namespace mem
}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_UCM_LIB_SWC_DB_MEM__MEM_BACKEND_H_
