//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocks/ucm/lib/buf/rw_view/ucm/lib/buf/rw_view.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_BUF__RW_VIEW_H_
#define UCM_AAP_LIBRARY__UCM_LIB_BUF__RW_VIEW_H_

#include "ucm/lib/buf/view.h"


/// @defgroup bosch_vrte_ucm_lib_buf__RO_View
/// @ingroup bosch_vrte_ucm_lib_buf
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace buf   {

class RW_View final : public View
{
public:
    explicit RW_View(void *, std::size_t, std::size_t) noexcept {}

    RW_View() noexcept = default;

    RW_View(RW_View     &&) = default;
    RW_View(RW_View const&) = default;

    RW_View& operator=(RW_View     &&) = default;
    RW_View& operator=(RW_View const&) = delete;

    ~RW_View() = default;

protected:
    virtual const void* mregion() const & noexcept
    {
        return nullptr;
    }

    virtual void* mregion() & noexcept
    {
        return nullptr;
    }
};


}    // namespace buf
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_LIB_BUF__RW_VIEW_H_
