//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018-2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      libs/common/include/bosch/vrte/stm/thread.hpp
/// @brief     CThread class as facade for exm::Thread
/// @copyright Robert Bosch GmbH 2018-2021
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_THREAD_HPP_INCLUDED
#define BOSCH_VRTE_STM_THREAD_HPP_INCLUDED

#include "bosch/vrte/stm/logging.hpp"

#ifndef STM_USE_EXM_THREAD
#include <thread>
#else
// We assume that are building for QNX otherwise.
#include <bosch/vrte/exm/Thread.hpp>
#include <memory>
#endif

#include <string>

namespace bosch
{
namespace vrte
{
namespace stm
{

/// @brief Facade for the exm::Thread class.
class CThread
{
public:
    /// @brief Constructor
    /// @param f_ref    Reference for thread configuration.
    /// @param f_name   Thread name.
    CThread(const std::string& f_ref, const std::string& f_name)
        : m_ref(f_ref)
        , m_name(f_name)
    {
    }

    /// @brief Destructor
    /// Will join a running thread.
    ~CThread()
    {
        join();
    }

    /// @brief Start thread.
    /// @param f_fnc    Thread function.
    /// @param f_args   Thread function arguments.
    /// @return         true if thread started successfully.
    template <typename Function, typename... Args> bool start(Function&& f_fnc, Args&&... f_args);

    /// @brief Check if thread is running.
    /// @return         true if thread is running.
    bool isRunning() const;

    /// @brief Join thread.
    void join();

protected:
    std::string m_ref;
    std::string m_name;

#ifndef STM_USE_EXM_THREAD
    std::thread m_thread;
#else
    std::unique_ptr<exm::Thread> m_thread;
#endif
};

#ifndef STM_USE_EXM_THREAD

template <typename Function, typename... Args> inline bool CThread::start(Function&& f_fnc, Args&&... f_args)
{
    CLogger(CLogger::LogLevel::Verbose, CLogger::Context::ALL, __FILE__, __LINE__, __func__).getStream()
    << "Start thread name " << quote(m_name) << " by std::thread";
    m_thread = std::thread(std::forward<Function&&>(f_fnc), std::forward<Args&&>(f_args)...);
    pthread_setname_np(m_thread.native_handle(), m_name.c_str());
    return true;
}

inline bool CThread::isRunning() const
{
    return m_thread.joinable();
}

inline void CThread::join()
{
    if (m_thread.joinable())
    {
        m_thread.join();
    }
}

#else

template <typename Function, typename... Args> inline bool CThread::start(Function&& f_fnc, Args&&... f_args)
{
    CLogger(CLogger::LogLevel::Verbose, CLogger::Context::ALL, __FILE__, __LINE__, __func__).getStream()
    << "Start thread name " << quote(m_name) << " by exm::Thread";
    m_thread = std::move(std::unique_ptr<exm::Thread>(new exm::Thread(
        m_ref.c_str(), m_name.c_str(), static_cast<Function&&>(f_fnc), static_cast<Args&&>(f_args)...)));
    return m_thread->assertion() == ::exm::StdReturnType::OK;
}

inline bool CThread::isRunning() const
{
    return m_thread != nullptr;
}

inline void CThread::join()
{
    if (m_thread)
    {
        m_thread->join();
        m_thread.reset();
    }
}

#endif

}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // #ifndef BOSCH_VRTE_STM_THREAD_HPP_INCLUDED
