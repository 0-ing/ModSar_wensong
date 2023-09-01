//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/arc/service.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       dsh8cob
/// @version
/// @remarks


#ifndef UCM_AAP_LIBRARY_LIB_ARC_SERVICE_H_
#define UCM_AAP_LIBRARY_LIB_ARC_SERVICE_H_

#include <array>
#include <memory>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/app/service.h"
#include "ucm/lib/arc/factory.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace arc   {

/// @brief This is an interface to register and access archive factory

class Service final : public app::Service
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_arc__Service, Simple);
    FRIEND_TEST(Test__ucm_lib_arc__Service, SetupNolock);
    FRIEND_TEST(Test__ucm_lib_arc__Service, StartoffNolock);
    FRIEND_TEST(Test__ucm_lib_arc__Service, ShutdownNolock);
#endif

    using Base = app::Service;

public:

    explicit Service();

    Service(const Service& other) = delete;
    Service& operator=(const Service&) = delete;

    Service(Service&&) = delete;
    Service& operator=(Service&&) = delete;

    ~Service() = default;

    /// @brief Function to get archive pointer.
    /// @param[in] type archive type.
    /// @return Unique pointer to Archive.
    std::unique_ptr<Archive> archive(std::string const& type);

    /// @brief Function to register a archive factory.
    /// @param[in] factory A unique pointer to the base class of the Factory.
    void register_factory(std::unique_ptr<Factory>&& factory);

protected:
    bool setup_nolock()    noexcept override;
    bool startoff_nolock() noexcept override;
    bool shutdown_nolock() noexcept override;


private:

    /// @brief An array to hold the archive factories.
    /// The array is limited to UCMS_MODULES_NUMBER as it is only logical
    std::array<std::unique_ptr<Factory>, UCMS_MODULES_NUMBER> factories_{};

    /// @brief A helper method to select the appropriate Factory.
    /// Since different factories can create archive,
    /// the method selects the factory that should return the archive.
    /// @param[in] type archive type
    /// @return A reference to a factory in the factories_ array
    /// @throws std::runtime_error if no factory can be selected.
    Factory& select_archive_factory(std::string const&);
};


}    // namespace arc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_ARC_SERVICE_H_
