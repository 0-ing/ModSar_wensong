#ifndef SOMEIP_LOG_HPP
#define SOMEIP_LOG_HPP

#include "ara/log/logger.h"

namespace com
{
namespace someip
{
///
/// @brief Simple support class to get a logging instance
class Logger
{
public:
    /// @brief Static call to get a single static logger instance, which is instantiated once.
    /// @param ctxId            Context ID
    /// @param ctxDescription   Context description
    /// @return A usable Logger instance.
    static ara::log::Logger& GetInstance(std::string ctxId          = "SOIP",
                                         std::string ctxDescription = "Logger for SomeIP Libraries");
};

} // namespace someip
} // namespace com
#endif
