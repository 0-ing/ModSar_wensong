//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/app/service.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_lib_app


#ifndef UCM_AAP_LIBRARY__UCM_LIB_APP__SERVICE_H_
#define UCM_AAP_LIBRARY__UCM_LIB_APP__SERVICE_H_

#include <mutex>
#include <memory>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/cfg/table.h"

/// @addtogroup bosch_vrte_ucm_lib_pkg_bin
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace app   {

/// @class Service service.h ucm/lib/app/service.h
/// @ingroup bosch_vrte_ucm_lib_app
/// @brief Base class for all UCM components providing an indernal service
///
/// The class defines an API for any service class across UCM implementation,
/// as well as a simple life-cycle management mechanism for changing the state
/// of a service. It also provides to any Service the primordial cfg::Table
/// instance.
///
class Service
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_app__Service, CTor);
    FRIEND_TEST(Test__ucm_lib_app__Service, Setup);
    FRIEND_TEST(Test__ucm_lib_app__Service, Startoff);
    FRIEND_TEST(Test__ucm_lib_app__Service, Shutdown);
#endif
protected:
    /// @brief Protected class constructor.
    ///
    /// The constructor sets up class-wide name and logname helpers.
    /// The initial state of the service is as follows:
    /// - setup_flag_ = false
    /// - startoff_flag_ = false
    /// - shutdown_flag_ = true
    ///
    /// @param[in] name The name of the implemented service as it will appear
    /// in the logs. A good policy is to follow the pattern namespace::Service.
    ///
    /// @test The UT script should check if name_ and logname_ are non-empty
    /// strings when a non-empty name is passed as parameter.
    ///
    explicit Service(std::string name);

    Service(Service     &&) = delete;
    Service(Service const&) = delete;

    Service& operator=(Service     &&) = delete;
    Service& operator=(Service const&) = delete;

public:
    /// @brief The non-default destructor of the class.
    ///
    /// The destructor merely logs that the object is being destroyed. The rest
    /// of the resources reclamation goes as specified by C++ language standard.
    ///
    virtual ~Service();

    /// @brief Try to enter <b>setup</b> phase of the life-cycle.
    ///
    /// The method is called when the caller wants to put the Service in its
    /// <b>setup</b> state. The internal flags fixing the state of the Service
    /// are checked and if the logic allows setup_nolock is called in a
    /// synchronised context.
    ///
    /// @retval true if the state transition and execution of the setup_nolock
    /// is successful.
    /// @retval false if the state transition and execution of the setup_nolock
    /// is not done for some reason.
    /// @note Failure in setting a service up is considered fatal and UCM must
    /// not continue further, but terminate.
    ///
    /// @test The UT script should check that the underlying setup_nolock is not
    /// called if the setup_flag_ is raised.
    /// @test The UT script should check that the return value of the underlying
    /// setup_nolock is assigned to the setup_flag_ after its execution.
    bool setup() noexcept;

    /// @brief Try to enter <b>startoff</b> phase of the life-cycle.
    ///
    /// The method is called when the caller wants to put the Service in its
    /// <b>startoff</b> state. The internal flags fixing the state of the
    /// Service are checked and if the logic allows startoff_nolock is called
    /// in a synchronised context.
    ///
    /// @retval true if the state transition and execution of the
    /// startoff_nolock is successful.
    /// @retval false if the state transition and execution of the
    /// startoff_nolock is not done for some reason.
    /// @note Failure in starting off a service up is considered fatal and
    /// UCM must not continue further, but terminate.
    ///
    /// @test The UT script should check that the underlying startoff_nolock is
    /// not called if the setup_flag_ is not set or the startoff_flag_ is
    /// raised.
    /// @test The UT script should check that the return value of the underlying
    /// startoff_nolock is assigned to the staroff_flag_ after its execution.
    /// @test The UT script should check if the shutdown_flag_ is set to false
    /// if the service is started successfully.
    ///
    bool startoff() noexcept;

    /// @brief Shutdown the service.
    ///
    /// The Service is shutdown by checking the startoff/shutdown flags and
    /// taking actions depending on the state defined by them, in order to avoid
    /// re-entering one and the same state.
    /// The startoff_nolock/shutdown_nolock implementations in the derived class
    /// are called to perform the real action.
    ///
    bool shutdown() noexcept;

    /// @brief Pass the configuration table to the Service.
    ///
    void config(const cfg::Table* table) noexcept;

    /// @brief Return the Service name.
    ///
    const std::string& name() const noexcept;

protected:
    const cfg::Table* config_{nullptr};
    mutable std::mutex mutex_{};

    bool setup_flag() const noexcept;
    bool startoff_flag() const noexcept;
    bool shutdown_flag() const noexcept;

    virtual bool setup_nolock()    noexcept = 0;
    virtual bool startoff_nolock() noexcept = 0;
    virtual bool shutdown_nolock() noexcept = 0;

    const std::string& logname() const noexcept;

private:
    std::string name_;
    std::string logname_;
    bool setup_flag_{false};
    bool startoff_flag_{false};
    bool shutdown_flag_{true};
};

inline const std::string& Service::name() const noexcept
{
    return name_;
}

inline const std::string& Service::logname() const noexcept
{
    return logname_;
}

inline void Service::config(const cfg::Table* table) noexcept
{
    config_ = table;
}

inline bool Service::setup_flag() const noexcept
{
    return setup_flag_;
}

inline bool Service::startoff_flag() const noexcept
{
    return startoff_flag_;
}

inline bool Service::shutdown_flag() const noexcept
{
    return shutdown_flag_;
}


}    // namespace app
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_LIB_APP__SERVICE_H_
