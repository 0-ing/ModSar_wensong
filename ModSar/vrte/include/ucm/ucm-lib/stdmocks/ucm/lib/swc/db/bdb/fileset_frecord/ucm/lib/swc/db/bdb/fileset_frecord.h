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

#include "ucm/mock/sequence.h"
#include "ucm/lib/swc/db/query.h"
#include "ucm/lib/swc/db/bdb/fileset.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {
namespace bdb   {

class FileSet_FRecord
        : public FileSet
          , virtual protected ucm::mock::Sequence
{
    constexpr static const char* prefix = "";
    constexpr static const char* suffix = "";
    constexpr static const char* fsname = "frecord";

public:
    explicit FileSet_FRecord(bool wlock, const std::string& path)
             : FileSet(wlock, path + "/" + prefix + fsname + suffix)
    {}

    FileSet_FRecord(FileSet_FRecord     &&) = default;
    FileSet_FRecord(FileSet_FRecord const&) = default;

    FileSet_FRecord& operator=(FileSet_FRecord     &&) = default;
    FileSet_FRecord& operator=(FileSet_FRecord const&) = default;

    virtual ~FileSet_FRecord() = default;

    Result count (Query&&)  {return pop<Result&&>();}
    Result select(Query&&) {return pop<Result&&>();}
    Result insert(Query&&) {return pop<Result&&>();}
    Result update(Query&&) {return pop<Result&&>();}
    Result remove(Query&&) {return pop<Result&&>();}

private:
    swc::FRecord load()  {return pop<swc::FRecord>();}
    void save(FRecord&) {pop<void>();}
    void save(const swc::FRecord&) {pop<void>();}
};


}    // namespace bdb
}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__FILESET_FRECORD_H_
