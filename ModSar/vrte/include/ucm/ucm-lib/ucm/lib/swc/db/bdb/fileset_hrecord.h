//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/db/bdb/fileset_hrecord.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__FILESET_HRECORD_H_
#define UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__FILESET_HRECORD_H_

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

class FileSet_HRecord : public FileSet
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_HRecord, CTor);
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_HRecord, Load);
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_HRecord, Save);
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_HRecord, Count);
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_HRecord, Select);
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_HRecord, Insert);
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_HRecord, Update);
    FRIEND_TEST(Test_ucm_lib_swc_bdb__FileSet_HRecord, Remove);
#endif

    constexpr static const char* prefix = "";
    constexpr static const char* suffix = "";
    constexpr static const char* fsname = "hrecord";

public:
    explicit FileSet_HRecord(bool wlock, const std::string& path);

    FileSet_HRecord(FileSet_HRecord     &&) = delete;
    FileSet_HRecord(FileSet_HRecord const&) = delete;

    FileSet_HRecord& operator=(FileSet_HRecord     &&) = delete;
    FileSet_HRecord& operator=(FileSet_HRecord const&) = delete;

    virtual ~FileSet_HRecord() = default;

    Result count(Query&&);
    Result select(Query&&);
    Result insert(Query&&);
    Result update(Query&&);
    Result remove(Query&&);

private:
    swc::HRecord load();
    void save(const swc::HRecord&);
};


}    // namespace bdb
}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__FILESET_HRECORD_H_
