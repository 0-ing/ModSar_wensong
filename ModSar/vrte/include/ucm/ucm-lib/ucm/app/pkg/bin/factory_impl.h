//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/pkg/bin/factory_impl.h
/// @brief        Implementation of factory for SWP process/compose objects.
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_pkg_bin


#ifndef UCM_AAP_LIBRARY__UCM_APP_PKG_BIN__FACTORY_IMPL_H_
#define UCM_AAP_LIBRARY__UCM_APP_PKG_BIN__FACTORY_IMPL_H_

#include <array>
#include <algorithm>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/buf/array.h"
#include "ucm/app/pkg/bin/types.h"
#include "ucm/lib/pkg/bin/factory.h"
#include "ucm/app/pkg/bin/ctx_cache.h"
#include "ucm/app/pkg/bin/v01xx/bitable.h"

/// @addtogroup bosch_vrte_ucm_app_pkg_bin
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace bin   {

/// @class FactoryImpl
/// @ingroup bosch_vrte_ucm_app_pkg_bin
/// @brief Factory implementation.

class FactoryImpl final : public lib::pkg::bin::Factory
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_app_pkg_bin_factory_impl, CTor);
    FRIEND_TEST(Test_ucm_app_pkg_bin_factory_impl, is_supported);
    FRIEND_TEST(Test_ucm_app_pkg_bin_factory_impl, swp_compose);
    FRIEND_TEST(Test_ucm_app_pkg_bin_factory_impl, swp_process);
#endif

    using Buffer  = lib::buf::Model;
    using Handle  = lib::pkg::bin::Handle;
public:
    explicit FactoryImpl(lib::sec::Provider& sec_provider);

    FactoryImpl(FactoryImpl     &&) = delete;
    FactoryImpl(FactoryImpl const&) = delete;

    FactoryImpl& operator=(FactoryImpl     &&) = delete;
    FactoryImpl& operator=(FactoryImpl const&) = delete;

    virtual ~FactoryImpl() = default;

    /// @brief Check if the Factory supports given vendor and format.
    ///
    /// @param[in] vendor The vendor tag for the SWP format.
    /// @param[in] format The container format version of the SWP.
    /// @retval true if the vendor/format pair is supported.
    /// @retval false if the vendor/format pair is <b>NOT</b> supported.
    ///
    /// @remark Currently supported vendor/format are: vendor(0x00000000)/
    /// format(0x00000102, 0x00000104).
    ///
    virtual bool
    is_supported(uint32_t vendor, uint32_t format) const noexcept override;

    /// @brief Check if the Factory supports given vendor and format.
    ///
    /// @param[in] vendor The vendor tag for the SWP format.
    /// @param[in] format The container format version of the SWP.
    /// @return A unique pointer to the created lib::pkg::bin::SWP_Compose
    /// is returned on success.
    /// @throws std::runtime_error if the vendor/format pair is not supported.
    /// @throws std::runtime_error if a valid context cannot be acquired.
    /// @throw Any exception that might be thrown by the SWP_Compose
    /// constructor.
    ///
    virtual std::unique_ptr<lib::pkg::bin::SWP_Compose>
    swp_compose(const std::string& file,
                uint32_t vendor, uint32_t format) override;

    /// @brief Create a SWP processor for given base AuthTag.
    virtual std::unique_ptr<lib::pkg::bin::SWP_Process>
    swp_process(const lib::pkg::bin::AuthBlock& ablock,
                const std::string& outdir, const std::string& swpfile) override;

private:
    CtxCache ctx_cache_;

    std::unique_ptr<lib::pkg::bin::SWP_Compose>
    swp_compose_0102(const std::string& file);

    std::unique_ptr<lib::pkg::bin::SWP_Process>
    swp_process_0102(const lib::pkg::bin::AuthBlock&,
                     const std::string& outdir, const std::string& swpfile);
};

}    // namespace bin
}    // namespace pkg
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_APP_PKG_BIN__FACTORY_IMPL_H_
