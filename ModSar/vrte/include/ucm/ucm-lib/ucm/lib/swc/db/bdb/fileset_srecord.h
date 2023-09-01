//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/db/bdb/fileset_srecord.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       dsh8cob
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__FILESET_SRECORD_H_
#define UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__FILESET_SRECORD_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/swc/db/query.h"
#include "ucm/lib/swc/db/bdb/fileset.h"
#include "ucm/lib/swc/db/bdb/srecord.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {
namespace bdb   {

class FileSet_SRecord : public FileSet
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_SRecord, CTor);
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_SRecord, Load);
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_SRecord, Save);
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_SRecord, Count);
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_SRecord, Select);
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_SRecord, Insert);
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_SRecord, Update);
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_SRecord, Remove);
#endif

    constexpr static const char* prefix = "";
    constexpr static const char* suffix = "";
    constexpr static const char* fsname = "srecord";

public:
    explicit FileSet_SRecord(bool wlock, const std::string& path);

    FileSet_SRecord(FileSet_SRecord     &&) = delete;
    FileSet_SRecord(FileSet_SRecord const&) = delete;

    FileSet_SRecord& operator=(FileSet_SRecord     &&) = delete;
    FileSet_SRecord& operator=(FileSet_SRecord const&) = delete;

    virtual ~FileSet_SRecord() = default;

    Result count(Query&&);
    Result select(Query&&);
    Result insert(Query&&);
    Result update(Query&&);
    Result remove(Query&&);

private:
    swc::SRecord load();
    void save(SRecord&);
    void save(const swc::SRecord&);
};


}    // namespace bdb
}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__FILESET_SRECORD_H_
