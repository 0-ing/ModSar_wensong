//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/db/mem/select_handle.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_UCM_LIB_SWC_DB_MEM__SELECT_HANDLE_H_
#define UCM_AAP_LIBRARY_UCM_LIB_SWC_DB_MEM__SELECT_HANDLE_H_

#include <vector>
#include <memory>
#include <type_traits>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/swc/db/handle.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {
namespace mem   {


class SelectHandle : public Handle
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_swc_db_mem__SelectHandle, CTor);
    FRIEND_TEST(Test_ucm_lib_swc_db_mem__SelectHandle, Count);
    FRIEND_TEST(Test_ucm_lib_swc_db_mem__SelectHandle, Select);
    FRIEND_TEST(Test_ucm_lib_swc_db_mem__SelectHandle, DoQuery);
#endif
public:
    explicit SelectHandle(Mutex& mutex, const Tuple&,
                          std::vector<IRecord>&,
                          std::vector<HRecord>&,
                          std::vector<FRecord>&,
                          std::vector<SRecord>&);

    SelectHandle(SelectHandle     &&) = default;
    SelectHandle(SelectHandle const&) = delete;

    SelectHandle& operator=(SelectHandle     &&) = delete;
    SelectHandle& operator=(SelectHandle const&) = delete;

    virtual ~SelectHandle() = default;

    virtual void abort() noexcept override;

    virtual void commit() override;

    virtual Result do_query(Query&&) override;

protected:
    std::vector<IRecord>& irecords_;
    std::vector<HRecord>& hrecords_;
    std::vector<FRecord>& frecords_;
    std::vector<SRecord>& srecords_;

    explicit SelectHandle(bool wlock,
                          Mutex& mutex, const Tuple&,
                          std::vector<IRecord>&,
                          std::vector<HRecord>&,
                          std::vector<FRecord>&,
                          std::vector<SRecord>&);

    virtual Result count(Query&&);

    virtual Result select(Query&&);
};


}    // namespace mem
}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_UCM_LIB_SWC_DB_MEM__SELECT_HANDLE_H_
