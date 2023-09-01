//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/db/bdb/fsileset_irecord.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__FILESET_IRECORD_H_
#define UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__FILESET_IRECORD_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/swc/db/query.h"
#include "ucm/lib/swc/db/bdb/fileset.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {
namespace bdb   {

class FileSet_IRecord : public FileSet
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_IRecord, CTor);
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_IRecord, Load);
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_IRecord, Save);
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_IRecord, Count);
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_IRecord, Select);
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_IRecord, Insert);
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_IRecord, Update);
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_IRecord, Remove);
#endif

    constexpr static const char* prefix = "";
    constexpr static const char* suffix = "";
    constexpr static const char* fsname = "irecord";

public:
    explicit FileSet_IRecord(bool wlock, const std::string& path);

    FileSet_IRecord(FileSet_IRecord     &&) = delete;
    FileSet_IRecord(FileSet_IRecord const&) = delete;

    FileSet_IRecord& operator=(FileSet_IRecord     &&) = delete;
    FileSet_IRecord& operator=(FileSet_IRecord const&) = delete;

    virtual ~FileSet_IRecord() = default;

    Result count(Query&&);
    Result select(Query&&);
    Result insert(Query&&);
    Result update(Query&&);
    Result remove(Query&&);

private:
    swc::IRecord load();
    void save(const swc::IRecord&);
};


}    // namespace bdb
}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__FILESET_IRECORD_H_
