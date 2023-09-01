//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/pkg/bin/factory.h
/// @brief        Base class for binary SWP process/compose factories.
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_lib_pkg_bin


#ifndef UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__FACTORY_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__FACTORY_H_


#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/utl/file_io.h"
#include "ucm/lib/sec/provider.h"
#include "ucm/lib/pkg/bin/handle.h"
#include "ucm/lib/pkg/bin/auth_block.h"
#include "ucm/lib/pkg/bin/swp_process.h"
#include "ucm/lib/pkg/bin/swp_compose.h"

#include "ucm/mock/sequence.h"

/// @addtogroup bosch_vrte_ucm_lib_pkg_bin
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace pkg   {
namespace bin   {

/// @class Factory factory.h ucm/lib/pkg/bin/factory.h
/// @ingroup bosch_vrte_ucm_lib_pkg_bin
/// @brief Base class for constructing a SWP processor/composer.
///
class Factory : virtual protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_pkg_bin__Factory, TEST__CTor);
#endif

public:
    explicit Factory(sec::Provider& sec_provider)
            : sec_provider_{sec_provider}
    {}

    Factory(Factory     &&) = default;
    Factory(Factory const&) = delete;

    Factory& operator=(Factory     &&) = default;
    Factory& operator=(Factory const&) = delete;

    virtual ~Factory() = default;

    /// @brief Check if the Factory supports given vendor and format.
    ///
    /// @param[in] vendor The vendor tag for the SWP format.
    /// @param[in] format The container format version of the SWP.
    /// @retval true if the vendor/format pair is supported.
    /// @retval false if the vendor/format pair is <b>NOT</b> supported.
    ///
    virtual bool
    is_supported(uint32_t, uint32_t) const noexcept = 0;

    /// @brief Create a binary SWP_Compose object.
    ///
    /// The method creates a binary SWP composer for the specified vendor and
    /// container format fields.
    ///
    /// @param[in] file The output SWP file.
    /// @param[in] vendor The vendor tag for the SWP format.
    /// @param[in] format The container format version of the SWP.
    /// @return A unique pointer to the created lib::pkg::bin::SWP_Compose
    /// is returned on success.
    /// @throws May throw an exception generated in the implementation of the
    /// derived class method.
    ///
    virtual std::unique_ptr<SWP_Compose>
    swp_compose(const std::string&,
                uint32_t, uint32_t) = 0;

    /// @brief Create a SWP processor for given base AuthTag.
    virtual std::unique_ptr<SWP_Process>
    swp_process(const AuthBlock&, const std::string&, const std::string&) = 0;

protected:
    /// @brief Reference to UCM wide security provider.
    sec::Provider& sec_provider_;
};

}    // namespace bin
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__FACTORY_H_
