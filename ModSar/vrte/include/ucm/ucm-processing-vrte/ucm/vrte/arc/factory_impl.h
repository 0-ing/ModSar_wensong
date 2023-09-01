//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/vrte/arc/factory_impl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       dsh8cob
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_vrte_arc


#ifndef UCM_AAP_PROCESSING_VRTE_UCM_VRTE_ARC_FACTORY_IMPL_H_
#define UCM_AAP_PROCESSING_VRTE_UCM_VRTE_ARC_FACTORY_IMPL_H_


#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/arc/factory.h"

/// @addtogroup bosch_vrte_ucm_vrte_arc
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace vrte  {
namespace arc   {

/// @brief Archive service factory implementation

class FactoryImpl final : public ucm::lib::arc::Factory
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_vrte_arc__FactoryImpl, TEST__CTor);
#endif

public:
    explicit FactoryImpl() noexcept = default;

    FactoryImpl(FactoryImpl     &&) = default;
    FactoryImpl(FactoryImpl const&) = default;

    FactoryImpl& operator=(FactoryImpl     &&) = default;
    FactoryImpl& operator=(FactoryImpl const&) = default;

    virtual ~FactoryImpl() = default;

    /// @brief Function to check supported archive type.
    /// @param [in] archive type.
    /// @return bool TRUE if supported else FALSE.
    virtual bool
    is_supported(std::string const&) noexcept override;

    /// @brief Return a Archive of specified type.
    /// @param [in] archive type.
    /// @return A unique pointer to a Archive that implements Archive API.
    /// @throws std::runtime_error if unsupported Archive type passed.
    virtual std::unique_ptr<ucm::lib::arc::Archive>
    archive(std::string const&) override;

};

}    // namespace arc
}    // namespace vrte
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_PROCESSING_VRTE_UCM_VRTE_ARC_FACTORY_IMPL_H_
