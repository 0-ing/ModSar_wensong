/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_UTILS_LOGGER_HPP
#define COM_UTILS_LOGGER_HPP

#include "ara/log/logger.h"

namespace com
{
namespace utils
{
/**
 * @brief Simple support class to create a logging instance singleton
 *
 * @TODO: This creates a single instance per process. Does the user know it will get a logger object? Is it configurable?
 */
class Logger
{
public:
    /**
     * @brief Static call to get a single static logger instance, which is instantiated once.
     *
     * @param ctxId             Context ID
     * @param ctxDescription    Context description
     * @return ara::log::Logger& A usable Logger instance.
     */
    static ara::log::Logger& GetInstance(ara::core::StringView ctxId          = "COM",
                                         ara::core::StringView ctxDescription = "Logger for COM Libraries");
};

} // namespace utils
} // namespace com

#endif // COM_UTILS_LOGGER_HPP
