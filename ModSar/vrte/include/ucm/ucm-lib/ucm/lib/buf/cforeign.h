//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/buf/cforeign.h
/// @brief        Constant foreign memory pointer implementation of the flexible
///               buffer model.
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup bosch_vrte_ucm_lib_buf

#ifndef UCM_AAP_LIBRARY__UCM_LIB_BUF__CFOREIGN_H_
#define UCM_AAP_LIBRARY__UCM_LIB_BUF__CFOREIGN_H_

#include <array>
#include <cassert>
#include <type_traits>

#if defined(GOOGLE_TEST)
#include <gtest/gtest_prod.h>
#endif

#include "ucm/lib/buf/view.h"
#include "ucm/lib/buf/model.h"
#include "ucm/lib/buf/ro_view.h"

/// @addtogroup bosch_vrte_ucm_lib_buf
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace buf   {

/// @class CForeign cforeign.h ucm/lib/buf/cforeign.h
/// @ingroup bosch_vrte_ucm_lib_buf
/// @brief Constant foreign memory pointer implementation of the flexible
/// buffer model.
///
class CForeign final : public Model
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_buf__Array, TEST__CTor);
#endif

public:
    explicit CForeign(const void *arena, std::size_t msize, std::size_t csize)
        : view_{arena, msize, csize}
    {}

    CForeign(CForeign     &&) = default;
    CForeign(CForeign const&) = delete;

    CForeign& operator=(CForeign     &&) = default;
    CForeign& operator=(CForeign const&) = delete;

    ~CForeign() = default;

    void reset() noexcept override
    {
        view_.reset();
    }

    void clear() noexcept override  {}

    bool resize(std::size_t) noexcept override
    { return false; }

    std::size_t memsize() const noexcept override
    { return view_.memsize(); }

    std::size_t cursize() const noexcept override
    { return view_.cursize(); }

    std::size_t nbviews() const noexcept override
    { return 1; }

    std::size_t nblocks() const noexcept override
    { return 1; }

    iterator end() noexcept override
    { return iterator(nbviews(), nbviews()); }

    iterator begin() noexcept override
    { return iterator(nbviews(), 0); }

    const_iterator end() const noexcept override
    { return const_iterator(nbviews(), nbviews()); }

    const_iterator begin() const noexcept override
    { return const_iterator(nbviews(), 0); }

    const_iterator cend() const noexcept override
    { return end(); }

    const_iterator cbegin() const noexcept override
    { return begin(); }

    View* view(const iterator& iter) noexcept override
    {
        if (iter == end())
            return nullptr;
        else
            return &view_;
    }

    View* view(memory_offset offset) noexcept override
    {
        if (offset >= view_.memsize())
            return nullptr;
        else
            return &view_;
    }

private:
    RO_View view_;
};

}    // namespace buf
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_LIB_BUF__CFOREIGN_H_
