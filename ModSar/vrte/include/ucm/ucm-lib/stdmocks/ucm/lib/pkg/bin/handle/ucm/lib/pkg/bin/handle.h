//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/pkg/bin/handle.h
/// @brief        Declaration of the SWP service handle
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_lib_pkg_bin

#ifndef UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__HANDLE_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__HANDLE_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/types.h"
#include "ucm/lib/pkg/bin/error.h"

/// @addtogroup bosch_vrte_ucm_lib_pkg_bin
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace pkg   {
namespace bin   {

/// @class Handle handle.h ucm/lib/pkg/bin/handle.h
/// @ingroup bosch_vrte_ucm_lib_pkg_bin
/// @brief Binary SWP processing service context identifier.
///
/// The class represents a context identifier for the binary SWP service.
/// All operations related with the binary SWP processing serivce are implicitly
/// or explicitly associated with a Handle.
///
class Handle final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_pkg_bin__Handle, TEST__Simple);
#endif

public:

    /// @brief Construct a valid object with specified id.
    ///
    explicit Handle(id_type id)
        : id_{id}
    {}

    Handle(Handle     &&) = default;
    Handle(Handle const&) = default;

    Handle& operator=(Handle     &&) = default;
    Handle& operator=(Handle const&) = default;

    ~Handle() = default;

    id_type operator()() const { return id_; }

private:
    id_type id_{0};
};

inline bool operator==(const Handle& lhs, const Handle& rhs)
{
    return lhs() == rhs();
}

inline bool operator!=(const Handle& lhs, const Handle& rhs)
{
    return !(lhs == rhs);
}

}    // namespace bin
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

namespace std
{
    template<>
    struct hash<bosch::vrte::ucm::lib::pkg::bin::Handle>
    {
        std::size_t
        operator()(const bosch::vrte::ucm::lib::pkg::bin::Handle& handle)
        const noexcept
        {
            return std::hash<bosch::vrte::ucm::id_type>{}(handle());
        }
    };

    template<>
    struct equal_to<bosch::vrte::ucm::lib::pkg::bin::Handle>
    {
        bool
        operator()(const bosch::vrte::ucm::lib::pkg::bin::Handle &lhs,
                   const bosch::vrte::ucm::lib::pkg::bin::Handle &rhs) const
        {
            return lhs == rhs;
        }
    };

    template<>
    struct less<bosch::vrte::ucm::lib::pkg::bin::Handle>
    {
        bool
        operator()(const bosch::vrte::ucm::lib::pkg::bin::Handle &lhs,
                   const bosch::vrte::ucm::lib::pkg::bin::Handle &rhs) const
        {
            return lhs() < rhs();
        }
    };
}   // namespace std

/// @}

#endif    // UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__HANDLE_H_
