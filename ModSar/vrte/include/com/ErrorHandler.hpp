#ifndef COM_ERRORHANDLER_HPP
#define COM_ERRORHANDLER_HPP

#include <iostream>

namespace com
{
/**
 * @brief Class to receive errors and act upon them.
 *
 * This is a (first) wrapper to decide an action to be taken, once
 * an error has been detected. It is currently used to exit the
 * program in case of critical errors in normal code.
 */
class ErrorHandler
{
public:
    /**
     * @brief Callback for a critical error.
     *
     * The intent of this function is to have a hook for handling
     * critical errors. We currently print a description message and then
     * shut down the process.
     *
     * @param description Some textual description of ther error.
     */
    static void CriticalError(const char* description)
    {
        std::cerr << "Critical Error: " << description << std::endl;
        exit(1);
    }
};

} // namespace com

#endif // COM_ERRORHANDLER_HPP
