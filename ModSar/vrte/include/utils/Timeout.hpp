//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      Timeout.hpp
/// @brief     Timeout class
/// @copyright Robert Bosch GmbH  2018
/// @author

#ifndef UTILS_TIMEOUT_HPP_INCLUDED
#define UTILS_TIMEOUT_HPP_INCLUDED

#include "utils/ITimeout.hpp"
#include "utils/ITimeoutNotificator.hpp"
#include "utils/Mutex.hpp"
#include "utils/StdReturnType.hpp"
#include "utils/Time.hpp"

namespace exm
{
namespace utils
{

/// @brief Internal interface to control the timeout server.
/// Allows timeout elements to safely interrupt the parent server class
/// when new actions come in.
class ITimeoutServices
{
public:
    /// @brief Destructor
    virtual ~ITimeoutServices()
    {
    } // Not covered: Deleting destructors of pure virtual base classes can not be called.

    /// @brief Locks the server so state changes in a Timeout object can be done safely.
    /// @return OK on success, an error code on failure.
    virtual StdReturnType Lock() = 0;

    /// @brief Unlocks the server after a state change in a Timeout object are done.
    /// @return OK on success, an error code on failure.
    virtual StdReturnType Unlock() = 0;

    /// @brief Interrupt the server, so it processes new inputs again.
    /// @return OK on success, an error code on failure.
    virtual StdReturnType InterruptServer() = 0;
};

/// @brief Interface to allow initializing and checking individual Timout objects from the server
/// side.
class ITimeoutController
{
public:
    /// @brief Destructor
    virtual ~ITimeoutController()
    {
    } // Not covered: Only the deleting destructor is not covered. We don't use the heap.

    /// @brief Constructor
    ITimeoutController() {}

    /// @brief Interface to initialize individual timeout objects.
    /// @param[in] services_ A reference to the TimeoutServer.
    virtual void init(ITimeoutServices& services_) = 0;

    /// @brief Allow a timeout object if it needs to fire and if is the current minimum.
    ///
    /// @param[in] now The time at which this request is issued.
    /// @param[inout] min_abs_time Inout value to accumulate the minimum remaining value over all
    /// timeout objects.
    /// @return OK in all cases but fatal errors.
    virtual StdReturnType Check(const Time& now, Time& min_abs_time) = 0;
};

/// @brief Realizes the timeout functionality
class Timeout : public utils::ITimeout, public utils::ITimeoutController
{
public:
    /// @brief Constructor
    Timeout();

    /// @brief Destructor
    virtual ~Timeout();

    /// @brief prevent copy construction
    /// @private
    Timeout(const Timeout&) = delete;

    /// @brief prevent copy assignment
    /// @private
    Timeout& operator=(const Timeout&) = delete;

    /// @brief Start a timeout
    /// @warning Do not pass a notification object with a shorter lifetime or at least make sure
    /// that 'Timeout' objects are not used anymore
    /// @param[in]  timeoutMs              Timeout in ms
    /// @param[in]  notification_          Timout notificator
    /// @param[in]  userData_              Pointer to userdata that will be passed to the
    /// notificator if the timeout fires.
    ///
    /// @return  StdReturnType
    /// @retval  OK              OK
    /// @retval  FATAL_ERROR     An unexpected error occurred.
    /// @retval  GENERAL_ERROR   Not possible to start this timeout object, because it is already
    /// started.
    virtual StdReturnType
    Start(uint32_t const timeoutMs, ITimeoutNotificator& notification_, void* const userData_);

    /// Cancel a timeout
    ///
    /// @return  StdReturnType
    /// @retval  OK              OK
    /// @retval  FATAL_ERROR     An unexpected error occurred.
    /// @retval  GENERAL_ERROR   Not possible to cancel this timeout object, because it is already
    /// cancelled.
    virtual StdReturnType Cancel();

private:
    ITimeoutServices* services; ///< Pointer to a server object for locking and unlocking.
    ITimeoutNotificator*
        notification; ///< Pointer to the object which is informed in case of a timeout.
    void* userData;   ///< Pointer to some user data which is passed in the notification call.
    Time target_time; ///< The absolute time at which the timeout shall fire.
    bool inUse;       ///< Flag to check if object is in use.

    /// @brief See interface description.
    /// @param services_ init value of timeout services
    virtual void init(ITimeoutServices& services_);

    /// @brief See interface description.
    /// @param now current time
    /// @param min_abs_time absolute time for timeout
    /// @return  StdReturnType
    /// @retval  OK              OK
    /// @retval  FATAL_ERROR     An unexpected error occurred.
    virtual StdReturnType Check(const Time& now, Time& min_abs_time);
};
/* class Timeout */

} /* namespace utils */
} /* namespace exm */
#endif
