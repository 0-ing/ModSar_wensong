// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      exceptions.hpp
/// @brief     Some legacy exceptions
/// @copyright Robert Bosch GmbH 2021
/// @author    crg2fe
//=============================================================================

#ifndef ARA_COM_EXCEPTIONS_HPP
#define ARA_COM_EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

namespace ara
{
namespace com
{
class ApplicationErrorException : public std::runtime_error
{
    using Exception = std::runtime_error;

public:
    ApplicationErrorException() : Exception("Application Error")
    {
    }

    virtual const char* what() const noexcept override = 0;
};

class ServiceNotAvailableException : public std::exception
{
private:
    std::string m_error;

public:
    ServiceNotAvailableException(std::string error) : m_error(error)
    {
    }

    const char* what() const noexcept
    {
        return m_error.c_str();
    }
};

} // namespace com

} // namespace ara

#endif /* ARA_COM_EXCEPTIONS_HPP */
