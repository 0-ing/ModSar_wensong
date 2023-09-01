//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018-2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      libs/common/include/bosch/vrte/stm/eventloop.hpp
/// @brief     Event handling helper class.
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_EVENTLOOP_HPP_INCLUDED
#define BOSCH_VRTE_STM_EVENTLOOP_HPP_INCLUDED

#include "bosch/vrte/stm/event.hpp"
#include "bosch/vrte/stm/logging.hpp"
#include "bosch/vrte/stm/thread.hpp"

#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <string>

namespace bosch
{
namespace vrte
{
namespace stm
{

/// @brief All STM components that need to handle events from the EventHandler
///         can subclass CEventLoopBase to get an event-loop and queue.
///
/// In order to ease mocking classes for unit test, a class should inherit from
/// CEventLoopBase directly and not indirectly via its interface
/// (see below example).
///
/// Note: Only the acceptEvent() method of this class is thread-safe.
///       All other methods must be used from within the same thread context.
///
/// Example usage:
///
/// \code
/// class CComponentManager : public CIComponentManager
/// {
/// public:
///     CComponentManager()
///       : m_events(std::bind(&CComponentManager::handleEvent, this, std::placeholder::_1, std::placeholder::_2),
///                  CLogger::Context::CM, "CM")
///     {
///         m_events.start();
///     }
///
///     ~CComponentManager()
///     {
///         m_events.stop();
///     }
///
///     void acceptEvent(const uint64_t f_event) override {
///         m_events.push(f_event);
///     }
///
///     void acceptEvent(const uint64_t f_event, const std::string& f_data) {
///         m_events.push(f_event, f_data);
///     }
///
/// private:
///     void handleEvent(uint64_t f_event, const std::string& f_data) override
///     {
///         uint8_t  sender       = GetEventSender(f_event);
///         uint16_t stateMachine = GetEventStateMachine(f_event);
///         uint32_t data         = GetEventData(f_event);
///
///         // handle...
///     }
///
///     CEventLoop m_events;
/// }
/// \endcode
class CEventLoop
{
public:
    typedef std::function<void(uint64_t f_event, const std::string& f_data)> callback_t;

    /// @brief Constructor
    ///
    /// @param f_callback         Function to be called for every event in the loop.
    ///                           Note: The implementation of this method must be thread-safe,
    ///                                 because it is called from within the event-thread-context.
    /// @param f_logContext       Log context.
    /// @param f_name             The provided name will be used to label the threads
    ///                           also be appended to trace messages.
    /// @param f_pushTimeout      Maximum amount of time to wait for an event queue
    ///                           to make space for the next event before we accept
    ///                           that a component was not able to consume events
    ///                           faster than it received them and create an error trace.
    /// @param f_maxQueueElements Maximum number of events in the queue.
    ///                           This amount should be small, in order to find problems early,
    ///                           where events could not be consumed fast enough.
    CEventLoop(callback_t                f_callback,
               CLogger::Context          f_logContext,
               const std::string&        f_name,
               std::chrono::milliseconds f_pushTimeout      = std::chrono::seconds(10),
               uint32_t                  f_maxQueueElements = 10);

    /// @brief Destructor
    ///
    /// The destructor will unregister at the EventHandler, stop the event thread
    /// and close the queue.
    ~CEventLoop();

    /// @brief Start the event handling loop.
    void start();

    /// @brief Ignore all events from now on.
    ///
    /// This method can be called in the destructor of the subclass in order
    /// to avoid to still get calls to handleEvent() while already entered the
    /// destructor.
    void stop();

    /// @brief Ignore all incoming events.
    ///
    /// This method will make the event loop stop calling the callback
    /// function on incoming events. However, incoming events will still be
    /// removed from the queue in order to avoid any deadlocks.
    void ignoreEvents();

    /// @brief Push an event to this receivers event queue.
    ///
    /// Pushing may fail and create an error trace in case the event loop was full
    /// and the wait timed out.
    ///
    /// @param f_event         event to push
    /// @param f_data          optional string data for event
    void push(uint64_t f_event, const std::string& f_data = std::string());

private:
    /// @brief Event Loop Thread
    ///
    /// This thread will wait on events added to the event queue and call
    /// handleEvent() on every received event.
    ///
    /// When the EV_STOP_EVENT_THREAD event is received it will stop executing.
    void eventThread();

    /// @brief Internal event structure.
    struct Event
    {
        uint64_t    event;
        std::string data;
    };

    /// @brief Get the next event from queue.
    /// @param f_event          next event (if any)
    /// @return                 false if no further event in queue.
    ///                         (f_event is undefined in that case)
    bool nextEventFromQueue(Event& f_event);

    callback_t                m_callback;
    CLogger::Context          m_logContext;
    std::string               m_name;
    CThread                   m_thread;
    std::chrono::milliseconds m_pushTimeout;
    std::queue<Event>         m_queue;
    uint32_t                  m_queueMaxSize;
    std::mutex                m_queueMutex;
    std::condition_variable   m_condition;
};

}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_EVENTLOOP_HPP_INCLUDED
