//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/pkg/bin/service.h
/// @brief        Binary SWP processing service.
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_lib_pkg_bin

#ifndef UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__SERVICE_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__SERVICE_H_

#include <array>
#include <vector>
#include <memory>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/buf/array.h"
#include "ucm/lib/app/service.h"
#include "ucm/lib/sec/provider.h"
#include "ucm/lib/pkg/bin/handle.h"
#include "ucm/lib/pkg/bin/factory.h"

/// @addtogroup bosch_vrte_ucm_lib_pkg_bin
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace pkg   {
namespace bin   {

/// @class Service service.h ucm/lib/pkg/bin/service.h
/// @ingroup bosch_vrte_ucm_lib_pkg_bin
/// @brief Facade class for the binary SWP format processing.
///
/// The service provided by the SWP facility is started and stopped during
/// the standard UCM core module initialisation. Any factory registration
/// has to be done during the UCM modules initialisation phases and is not
/// allowed to happen once UCM is declared running.
///
class Service final : public app::Service
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_pkg_bin_service, setup_nolock);
    FRIEND_TEST(Test_ucm_lib_pkg_bin_service, startoff_nolock);
    FRIEND_TEST(Test_ucm_lib_pkg_bin_service, shutdown_nolock);
    FRIEND_TEST(Test_ucm_lib_pkg_bin_service, factory_not_found);
    FRIEND_TEST(Test_ucm_lib_pkg_bin_service, factory_found);
#endif

    using Base = app::Service;
    using ABlockBuff = buf::Array<AuthBlock::fixed_size()>;
public:
    /// @brief Construct the SWP Service object.
    ///
    /// @param sec_provider UCM wide security provider object.
    ///
    explicit Service(sec::Provider& sec_provider);

    Service(Service     &&) = delete;
    Service(Service const&) = delete;

    Service& operator=(Service     &&) = delete;
    Service& operator=(Service const&) = delete;

    ~Service() = default;

    /// @brief Feed data to the SWP processing context.
    ///
    /// @param[in] handle The context handle for the SWP service.
    /// @param[in] buff Buffer containing (part of) the SWP.
    /// @param[in] isize The size of the buffer.
    /// @param[out] osize Size of the data consumed from the buffer.
    /// @return ErrorValue::kSuccess if a valid AuthTag start is detected.
    /// @return ErrorValue::kContinuation if no sufficient data for the initial
    /// detection is available.
    /// @return Any other error which could happen during the processing.
    ///
    Error process_feed(const Handle& handle,
                       const void* buff, size_t isize, size_t& osize) noexcept;


    /// @brief Feed data to the authentication tag instance.
    ///
    Error process_load(const std::string& swpfile) noexcept;

    /// @brief Check if the authentication tag need more data.
    ///
    /// @return true, if the authentication tag buffer is ready.
    /// @return false, if the authentication tag buffer is NOT ready.
    ///
    static bool process_tag_ready(const Error&) noexcept;

    /// @brief Check if the authentication tag has an error condition.
    ///
    /// @return true, if the authentication tag has no error condition.
    /// @return false, if the authentication tag has error condition.
    ///
    static bool process_tag_check(const Error&) noexcept;

    /// @brief Create a binary SWP composer.
    ///
    /// @param[in] outdir Output directory to hold the extracted artefacts.
    /// @param[in] swpfile The file holding the binary SWP to be processed.
    /// @throws std::logic_error if the security module is not set correctly.
    /// @throws std::runtime_error if the service cannot find a suitable
    /// factory for the requested SWP_Process object.
    /// @throws std::runtime_error if the factory cannot create the requested
    /// SWP_Process object.
    ///
    std::unique_ptr<SWP_Process>
    swp_process(const std::string& outdir, const std::string& swpfile);

    /// @brief Create a binary SWP composer.
    ///
    /// The method creates a binary SWP composer for the specified vendor and
    /// container format fields.
    ///
    /// @param[in] file The output SWP file.
    /// @param[in] vendor The vendor tag for the SWP format.
    /// @param[in] format The container format version of the SWP.
    /// @return A unique pointer to the created SWP_Compose is returned on
    /// success.
    /// @throws std::logic_error if the security module is not set correctly.
    /// @throws std::runtime_error if the service cannot find a suitable
    /// factory for the requested SWP_Compose object.
    /// @throws std::runtime_error if the factory cannot create the requested
    /// SWP_Compose object.
    ///
    std::unique_ptr<SWP_Compose>
    swp_compose(const std::string& file, uint32_t vendor, uint32_t format);

    /// @brief Register a Factory which creates a SWP processor or composer.
    ///
    /// The method should be called only during the modules <b>setup</b> phase
    /// as there is no concurrent access protection in place.
    ///
    /// @param[in] factory A unique pointer to the base Factory class.
    /// @throws std::logic_error if the security module is not set correctly.
    /// @throws std::runtime_error if the maximum number of factories has been
    /// reached.
    ///
    void register_factory(std::unique_ptr<Factory>&& factory);

protected:
    bool setup_nolock()    noexcept override;
    bool startoff_nolock() noexcept override;
    bool shutdown_nolock() noexcept override;

private:
    /// @brief Reference to UCM wide security provider.
    sec::Provider& sec_provider_;

    /// @brief Initial buffer for the authentication tag.
    ABlockBuff tagbuff_{};

    /// @brief SWP service synchronisation mutex.
    ///
    /// The mutex is locked during:
    /// - SWP Factory registration.
    /// - SWP Factory selection.
    /// - Creation of a SWP_Process object.
    mutable std::mutex mutex_{};

    /// @brief An array to hold the SWP objects Factory instances.
    ///
    /// @note The array is limited to UCMS_MODULES_NUMBER as it is only logical
    /// one module to register only one Factory and deal internally how and
    /// with what parsers should be created.
    ///
    /// @note UCMS_MODULES_NUMBER is set at build time as CMake exported
    /// variable.
    ///
    std::array<std::unique_ptr<Factory>, UCMS_MODULES_NUMBER> factories_{};

    /// @brief Select a SWP Factory.
    ///
    Factory& factory(const AuthBlock&);

    /// @brief Select a SWP Factory.
    ///
    Factory& factory(uint32_t vendor, uint32_t format);
};

inline bool Service::process_tag_ready(const Error& err) noexcept
{
    return err == ErrorValue::kSuccess;
}

inline bool Service::process_tag_check(const Error& err) noexcept
{
    return err == ErrorValue::kSuccess or err == ucm::ErrorValue::kContinuation;
}

}    // namespace bin
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__SERVICE_H_
