//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/ppl/tag.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks
///

#ifndef UCM_AAP_LIBRARY_LIB_PPL_TAG_H_
#define UCM_AAP_LIBRARY_LIB_PPL_TAG_H_

#include "ucm/mock/sequence.h"
#include <limits>
#include <cstddef>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace ppl {

class Tag final
    : virtual protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_Lib_Pipeline_Tag, Simple);
#endif
public:
    using taskid_type = std::size_t;
    // using seqnum_type = std::size_t; - just a hint

    constexpr static taskid_type invalid_taskid() noexcept
    {
        return std::numeric_limits<taskid_type>::max();
    }

    Tag() noexcept = default;

    Tag(const taskid_type& value) noexcept : taskid_{value} {};

    // move semantic
    Tag(Tag&&) noexcept = default;
    Tag& operator=(Tag&&) = default;

    // copy semantics
    Tag(const Tag& other) = default;
    Tag& operator=(const Tag&) = default;

    ~Tag() = default;

    const auto& taskid() const noexcept;

    bool taskid_valid() const noexcept;

private:
    taskid_type taskid_{invalid_taskid()};
};

inline const auto& Tag::taskid() const noexcept
{
    return pop<taskid_type const&>();
}

inline bool Tag::taskid_valid() const noexcept
{
    return pop<bool>();
}

}    // namespace ppl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_PPL_TAG_H_
