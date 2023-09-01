//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/db/bdb/irecord.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__IRECORD_H_
#define UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__IRECORD_H_

#include <cstdint>
#include <type_traits>

#include "ucm/mock/sequence.h"
#include "ucm/lib/swc/irecord.h"
#include "ucm/lib/swc/db/bdb/header.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {
namespace bdb   {

class IRecord final
      : virtual protected ucm::mock::Sequence
{
public:
    explicit IRecord(const Header&)
    {
    }
    explicit IRecord(const Header&, swc::IRecord&&)
    {
    }

    IRecord(IRecord     &&) = default;
    IRecord(IRecord const&) = default;

    IRecord& operator=(IRecord     &&) = default;
    IRecord& operator=(IRecord const&) = default;

    ~IRecord() = default;

    void load(lib::utl::FileIO&) {}

    void save(lib::utl::FileIO&) {}

    swc::IRecord& record() &  noexcept;
    swc::IRecord  record() && noexcept;
    const swc::IRecord&  record() const & noexcept;
};

inline swc::IRecord& IRecord::record() &  noexcept
{
    return pop<swc::IRecord&>();
}

inline swc::IRecord IRecord::record() && noexcept
{
    return pop<swc::IRecord&&>();
}

inline const swc::IRecord& IRecord::record() const & noexcept
{
    return pop<swc::IRecord const&>();
}


}    // namespace bdb
}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__IRECORD_H_
