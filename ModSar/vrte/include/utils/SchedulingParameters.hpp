//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
/// @file      SchedulingParameters.hpp
/// @brief     Declaration/Definition of SchedulingParameters
/// @author
//=============================================================================
#ifndef UTILS_SCHEDULINGPARAMETERS_HPP_INCLUDED
#define UTILS_SCHEDULINGPARAMETERS_HPP_INCLUDED

#include <pthread.h>
#include <sched.h>

#include "utils/StdReturnType.hpp"
#include "utils/Types.hpp"
#include "log/Log.hpp"

namespace exm
{
namespace utils
{
/// @class    SchedulingParameters
/// @brief    Class to hold the scheduling values (policy and priority)
class SchedulingParameters
{
public:
    /// @brief Constructor
    /// Intentionally initialized with wrong parameters, so that it must be set before use!
    SchedulingParameters()
        : sch_policy(-1), sch_param(), sch_configured(false)
    {
        sch_param.sched_priority = -1;
    }
    /// @brief Destructor
    ~SchedulingParameters() {}

    /// @brief No copy constructor needed.
    SchedulingParameters(const SchedulingParameters&) = delete;

    /// @brief Copy assignment operator
    SchedulingParameters& operator=(const SchedulingParameters& other)
    {
        if (this != &other)
        {
            this->sch_policy = other.sch_policy;
            this->sch_param = other.sch_param;
            this->sch_configured = other.sch_configured;
        }

        return *this;
    }

    /// @brief Function to set the scheduling values
    /// @param policy   Scheduling policy
    /// @param priority   Scheduling priority
    /// @return StdReturnType::OK on success
    StdReturnType Set_SchedulingParameters(Integer const policy, Integer const priority)
    {
        if (((policy != SCHED_FIFO) && (policy != SCHED_RR) && (policy != SCHED_OTHER)))
        {
            log::Log(Severity::WARN, "invalid scheduling policy");
            return StdReturnType::INVALID_ARGUMENTS;
        }
        if ((priority < GetPriorityMin(policy))
            || (priority > GetPriorityMax(policy)))
        {
            log::Log(Severity::WARN, "invalid scheduling priority");
            return StdReturnType::INVALID_ARGUMENTS;
        }

        sch_policy = policy;
        sch_param.sched_priority = priority;
        sch_configured = true;

        return StdReturnType::OK;
    }

    /// @brief Sets the default scheduling policy and priority.
    /// This will overtake the calling thread policy and priority.
    StdReturnType SetDefault()
    {
        struct sched_param defaultParam;
        Integer defaultPolicy = -1;
        defaultParam.sched_priority = -1;
        const Integer ret = pthread_getschedparam(pthread_self(), &defaultPolicy, &defaultParam);
        if (0 != ret)
        {
            return StdReturnType::GENERAL_ERROR;
        }

        return Set_SchedulingParameters(defaultPolicy, defaultParam.sched_priority);
    }

    /// @brief Function to return the scheduling policy
    /// @return Scheduling policy
    Integer Get_SchedulingPolicy() const { return sch_policy; }

    /// @brief Function to return the scheduling priority
    /// @return Pointer to the scheduling parameter struct (which holds the scheduling priority)
    const sched_param* Get_SchedulingPriority() const { return &sch_param; }

    /// @brief Function to check whether scheduling was configured for a Process
    /// @retval TRUE  Scheduling for Process is configured
    /// @retval FALSE  Scheduling for Process is NOT configured
    bool IsSchedulingConfigured() const { return sch_configured; }

    /// @brief  Function to get the minimum scheduling priority for a given scheduling policy
    /// @param  policy Scheduling policy
    /// @return Minimum scheduling priority
    static Integer GetPriorityMin(Integer const policy)
    {
        Integer retval = -1;

        switch (policy)
        {
            case SCHED_FIFO:
                retval = SCHED_FIFO_MIN;
                break;
            case SCHED_RR:
                retval = SCHED_RR_MIN;
                break;
            case SCHED_OTHER:
                retval = SCHED_OTHER_MIN;
                break;
            default:
                break;
        }

        return retval;
    }

    /// @brief  Function to get the maximum scheduling priority for a given scheduling policy
    /// @param  policy Scheduling policy
    /// @return Minimum scheduling priority
    static Integer GetPriorityMax(Integer const policy)
    {
        Integer retval = -1;

        switch (policy)
        {
            case SCHED_FIFO:
                retval = SCHED_FIFO_MAX;
                break;
            case SCHED_RR:
                retval = SCHED_RR_MAX;
                break;
            case SCHED_OTHER:
                retval = SCHED_OTHER_MAX;
                break;
            default:
                break;
        }

        return retval;
    }

private:
    /// @brief scheduling policy
    Integer sch_policy;

    /// @brief scheduling parameter object
    sched_param sch_param;

    /// @brief Flag that indicates whether scheduling of a Process was configure
    bool sch_configured;

    static const Integer SCHED_FIFO_MIN;
    static const Integer SCHED_RR_MIN;
    static const Integer SCHED_OTHER_MIN;

    static const Integer SCHED_FIFO_MAX;
    static const Integer SCHED_RR_MAX;
    static const Integer SCHED_OTHER_MAX;

};

} // namespace utils
} // namespace exm

#endif // UTILS_SCHEDULINGPARAMETERS_HPP_INCLUDED
