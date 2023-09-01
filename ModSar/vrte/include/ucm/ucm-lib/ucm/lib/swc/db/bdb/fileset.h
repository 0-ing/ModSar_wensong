//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/db/bdb/fileset.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__FILESET_H_
#define UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__FILESET_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/utl/dir.h"
#include "ucm/lib/utl/file_io.h"
#include "ucm/lib/swc/db/bdb/header.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {
namespace bdb   {

class FileSet
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__FileSet, CTor);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__FileSet, Close);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__FileSet, Begin);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__FileSet, Abort);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__FileSet, Commit);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__FileSet, RDOpen);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__FileSet, WROpen);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__FileSet, Remove);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__FileSet, WRFlush);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__FileSet, Recover);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__FileSet, Cleanup);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__FileSet, FileExists);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__FileSet, DATFileCreate);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__FileSet, BAKFileCreate);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__FileSet, TMPFileCreate);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__FileSet, BAKFileRename);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__FileSet, TMPFileRename);
#endif
public:
    explicit FileSet(bool, const std::string&);

    FileSet(FileSet     &&) = delete;
    FileSet(FileSet const&) = delete;

    FileSet& operator=(FileSet     &&) = delete;
    FileSet& operator=(FileSet const&) = delete;

    virtual ~FileSet();

    Header& header() & noexcept;
    Header  header() && noexcept;
    const Header& header() const & noexcept;

    void begin();
    void abort();
    void commit();
    void recover();
    void cleanup();

protected:
    bool        wlock_;
    bool        begin_;
    Header      header_;
    std::string datfile_;
    std::string bakfile_;
    std::string tmpfile_;
    std::string pkpfile_;

    lib::utl::FileIO rdfile_{};
    lib::utl::FileIO wrfile_{};

    void rd_open();
    void wr_open();
    void wr_flush();

private:
    void datfile_create();
    void bakfile_create();
    void tmpfile_create();
    void bakfile_rename();
    void tmpfile_rename();

    void close(lib::utl::FileIO&);
    void remove(const std::string&);

    static bool file_exists(const std::string&);
};

inline Header& FileSet::header() & noexcept
{
    return header_;
}

inline Header FileSet::header() && noexcept
{
    return header_;
}

inline const Header& FileSet::header() const & noexcept
{
    return header_;
}

}    // namespace bdb
}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__FILESET_H_
