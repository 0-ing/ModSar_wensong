//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocks/ucm/lib/buf/ro_view/ucm/lib/buf/ro_view.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_BUF__RO_VIEW_H_
#define UCM_AAP_LIBRARY__UCM_LIB_BUF__RO_VIEW_H_

#include "ucm/lib/buf/view.h"


/// @defgroup bosch_vrte_ucm_lib_buf__RO_View
/// @ingroup bosch_vrte_ucm_lib_buf
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace buf   {

class RO_View final : public View
{
public:
    explicit RO_View(void *, std::size_t, std::size_t) noexcept {}

    RO_View() noexcept = default;

    RO_View(RO_View     &&) = default;
    RO_View(RO_View const&) = default;

    RO_View& operator=(RO_View     &&) = default;
    RO_View& operator=(RO_View const&) = delete;

    ~RO_View() = default;

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

#endif // UCM_AAP_LIBRARY__UCM_LIB_BUF__RO_VIEW_H_
