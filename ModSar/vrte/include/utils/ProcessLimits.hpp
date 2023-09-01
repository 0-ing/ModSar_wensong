//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
/// @file      ProcessLimits.hpp
/// @brief     Declaration/Definition of ProcessLimits
/// @author    Yohan Pistor
//=============================================================================
#ifndef UTILS_PROCESSLIMITS_HPP
#define UTILS_PROCESSLIMITS_HPP

#include "utils/PrimaryConfig.hpp"
#include "utils/vector.hpp"

namespace exm
{

namespace utils
{

/// @brief class defining a process limit.
///
class ProcessLimit
{
public:
    typedef uint64_t LimitValue;

    enum class LimitType : uint8_t
    {
        INVALID = 0,    ///< Invalid type
        CPU,            ///< Maximum amount of CPU time
        STACK,          ///< The maximum size of process stack
        ADDRESSSPACE,   ///< Mapped address space
        HEAP,           ///< Process heap memory size
    };

    /// @brief Default Constructor
    ProcessLimit()
        : type(LimitType::INVALID), value(0U) {}

    /// @brief Constructor
    ProcessLimit(LimitType type_, LimitValue value_)
        : type(type_), value(value_) {}

    /// @brief Destructor
    virtual ~ProcessLimit() {};

    /// @brief Copy constructor
    ProcessLimit(const ProcessLimit& other)
        : type(other.type), value(other.value) {}

    /// @brief Copy assignment operator
    ProcessLimit& operator=(const ProcessLimit& other)
    {
        if (this != &other)
        {
            this->type = other.type;
            this->value = other.value;
        }

        return *this;
    }

    /// @brief Checks against a defined limit type
    /// @param[in] type_ Type to be checked
    /// @return true Limit is of defined type
    bool IsOfType(LimitType type_) const { return (type_ == type); }

    /// @brief Gets the process limit value
    /// @return LimitValue Value of the limit
    LimitValue GetLimitValue() const { return value; }

    /// @brief Gets the process limit type
    /// @return LimitType Type of the limit
    LimitType GetLimitType() const { return type; }

private:
    LimitType type;   ///< Type of the process limit
    LimitValue value; ///< Value of the process limit
};

class ProcessLimits
{
public:
    /// @brief Constructor
    ProcessLimits()
        : limits() {}

    /// @brief Destructor
    virtual ~ProcessLimits() {};

    /// @brief No copy constructor needed.
    ProcessLimits(const ProcessLimits&) = delete;

    /// @brief copy assignment operator
    ProcessLimits& operator=(const ProcessLimits& other)
    {
        if (this != &other)
        {
            this->limits = other.limits;
        }

        return *this;
    }

    /// @brief Pushes a process limit
    /// @param[in] plimit Process limit
    /// @return OK on success, GENERAL_ERROR on failures
    StdReturnType PushLimit(const utils::ProcessLimit& plimit);

    /// @brief Gets the process limit for a given type
    /// @param[in]  type_ Process limit type
    /// @param[out] value_ Value of the process limit
    /// @return OK on Success, INVALID_STATE if limit is not set
    StdReturnType GetLimitByType(ProcessLimit::LimitType type_, ProcessLimit::LimitValue& value_) const;

private:
    /// @brief Checks whether a specific type of limit is already set
    /// @param[in] type_ Process limit type
    /// @return true Limit is already set
    bool IsLimitAlreadySet(ProcessLimit::LimitType type_) const;

    /// @brief Vector to hold process limits
    vector<ProcessLimit, MAX_PROCESS_LIMITS> limits;
};

} // namespace utils
} // namespace exm

#endif
