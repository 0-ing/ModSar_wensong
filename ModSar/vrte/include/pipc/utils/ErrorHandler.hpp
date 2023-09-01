#ifndef PIPC_UTILS_ERROR_HANDLER_HPP
#define PIPC_UTILS_ERROR_HANDLER_HPP

#include "ErrorType.hpp"
#include "pipc/ReturnCode.hpp"

#include <iostream>

namespace pipc
{
namespace utils
{
/**
 * @brief Class to receive errors and act upon them.
 *
 * This is a (first) wrapper to decide an action to be taken, once
 * an error has been detected. It is currently used to exit the
 * program in case of critical errors in normal code.
 *
 * @todo
 * We don't have a clear concept on error handling yet,
 * this needs to be defined. Currently this class is mainly used for
 * wrapping any exit(1) calls to mock them in tests, and also to be able
 * to print debug messages for posix errors.
 *
 * Some ideas:
 * We could derive class-specific error handlers for more elegant
 * error handling in the code.
 * For example: Let there be an ErrorHandler for class pub_sub and additional
 * error sources like PublisherBase, which also receive the PublisherBase object.
 * Then we can easily change the handlers to print more or less detail and
 * prefix the messages with info like "PublisherBase: " in the error handler
 */
class ErrorHandler
{
public:
    /**
     * @brief Callback for a critical error.
     *
     * The intent of this function is to have a hook for handling
     * critical errors. We currently print a debug message and then
     * shut down the process.
     * @param type Error type. default is kGeneral.
     *      In case of POSIX errors, use kPosix
     * @param description Some additional textual description of ther error.
     *      In case of POSIX errors, use this value to specify the posix function that was called.
     *      Default is "unknown"
     * @param returnCode A returnCode that is available in the context of the error. Default is kGeneralError.
     */
    static void CriticalError(ErrorType type          = ErrorType::kGeneral,
                              const char* description = "unknown",
                              ReturnCode returnCode   = ReturnCode::kGeneralError)
    {
        switch (type)
        {
        case ErrorType::kGeneral:
        {
            std::cout << "General error with code " << ToString(returnCode) << ": " << description << std::endl;
            break;
        }
        case ErrorType::kPosix:
        {
            perror(description);
            break;
        }
        }
        exit(1);
    }

    /**
     * @brief Callback for an error.
     *
     * The intent of this function is to have a hook for handling
     * non-critical errors. We currently print a debug message.
     */
    static void Error(ErrorType type, const char* description)
    {
        switch (type)
        {
        case ErrorType::kGeneral:
        {
            std::cout << description << std::endl;
            break;
        }
        case ErrorType::kPosix:
        {
            perror(description);
            break;
        }
        }
    }
};

} // namespace utils
} // namespace pipc

#endif // PIPC_UTILS_ERROR_HANDLER_HPP
