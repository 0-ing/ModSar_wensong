//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/arc/factory.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       dsh8cob
/// @version
/// @remarks


#ifndef UCM_AAP_LIBRARY__UCM_LIB_ARC_FACTORY_H_
#define UCM_AAP_LIBRARY__UCM_LIB_ARC_FACTORY_H_


#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/arc/archive.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace arc   {

/// @brief This is an method to create archive pointer with supported type

class Factory
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_arc_Factory, TEST__CTor);
#endif

public:

    virtual ~Factory() = default;

    /// @brief Virtual function to check supported archive type.
    /// @param[in] archive type.
    /// @return bool TRUE if supported else FALSE.
    virtual bool is_supported(std::string const&) noexcept = 0;

    /// @brief Return a Archive of specified type.
    /// @param[in] archive type.
    /// @return A unique pointer to a Archive that implements Archive API.
    virtual std::unique_ptr<Archive> archive(std::string const&) = 0;

protected:

    explicit Factory() = default;

    Factory(      Factory&&) = default;
    Factory(const Factory &) = default;

    Factory& operator=(      Factory&&) = default;
    Factory& operator=(const Factory &) = default;

};

}    // namespace arc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch


#endif // UCM_AAP_LIBRARY__UCM_LIB_ARC_FACTORY_H_
