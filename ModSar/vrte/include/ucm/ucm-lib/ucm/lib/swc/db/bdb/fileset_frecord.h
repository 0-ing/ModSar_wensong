//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/db/bdb/fileset_frecord.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__FILESET_FRECORD_H_
#define UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__FILESET_FRECORD_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/swc/db/query.h"
#include "ucm/lib/swc/db/bdb/fileset.h"
#include "ucm/lib/swc/db/bdb/frecord.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {
namespace bdb   {

class FileSet_FRecord : public FileSet
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_FRecord, CTor);
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_FRecord, Load);
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_FRecord, Save);
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_FRecord, Count);
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_FRecord, Select);
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_FRecord, Insert);
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_FRecord, Update);
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_FRecord, Remove);
#endif

    constexpr static const char* prefix = "";
    constexpr static const char* suffix = "";
    constexpr static const char* fsname = "frecord";

public:
    explicit FileSet_FRecord(bool wlock, const std::string& path);

    FileSet_FRecord(FileSet_FRecord     &&) = delete;
    FileSet_FRecord(FileSet_FRecord const&) = delete;

    FileSet_FRecord& operator=(FileSet_FRecord     &&) = delete;
    FileSet_FRecord& operator=(FileSet_FRecord const&) = delete;

    virtual ~FileSet_FRecord() = default;

    Result count(Query&&);
    Result select(Query&&);
    Result insert(Query&&);
    Result update(Query&&);
    Result remove(Query&&);

private:
    swc::FRecord load();
    void save(FRecord&);
    void save(const swc::FRecord&);
};


}    // namespace bdb
}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__FILESET_FRECORD_H_
