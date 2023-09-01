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

#include "ucm/mock/sequence.h"
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
      :  virtual protected ucm::mock::Sequence
{
public:
    explicit FileSet(bool, const std::string&) {}

    FileSet(FileSet     &&) = delete;
    FileSet(FileSet const&) = delete;

    FileSet& operator=(FileSet     &&) = delete;
    FileSet& operator=(FileSet const&) = delete;

    virtual ~FileSet() = default;

    Header& header() & noexcept;
    Header  header() && noexcept;
    const Header& header() const & noexcept;

    void begin() {pop<void>();}
    void abort() {pop<void>();}
    void commit() {pop<void>();}
    void recover() {pop<void>();}
    void cleanup() {pop<void>();}

protected:
    bool        wlock_{};
    bool        begin_{};
    Header      header_{};
    std::string datfile_{};
    std::string bakfile_{};
    std::string tmpfile_{};
    std::string pkpfile_{};

    lib::utl::FileIO rdfile_{};
    lib::utl::FileIO wrfile_{};

    void rd_open() {pop<void>();}
    void wr_open() {pop<void>();}
    void wr_flush() {pop<void>();}

private:
    void datfile_create() {pop<void>();}
    void bakfile_create() {pop<void>();}
    void tmpfile_create() {pop<void>();}
    void bakfile_rename() {pop<void>();}
    void tmpfile_rename() {pop<void>();}

    void close(lib::utl::FileIO&) {pop<void>();}
    void remove(const std::string&) {pop<void>();}

    static bool file_exists(const std::string&) {return pop<bool>();}
};

inline Header& FileSet::header() & noexcept
{
    return pop<Header&>();
}

inline Header FileSet::header() && noexcept
{
    return pop<Header>();
}

inline const Header& FileSet::header() const & noexcept
{
    return pop<Header const&>();
}

}    // namespace bdb
}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__FILESET_H_
