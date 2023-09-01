#ifndef S2S_LOG_HPP
#define S2S_LOG_HPP

#include "ara/log/logger.h"

namespace com
{
namespace s2s
{
///
/// @brief Simple support class to get a logging instance
class Logger
{
public:
    /**
     * @brief Static call to get a single static logger instance, which is instantiated once.
     * @param ctxId            Context ID
     * @param ctxDescription   Context description
     * @return A usable Logger instance.
     */
    static ara::log::Logger& GetInstance(std::string ctxId          = "STOS",
                                         std::string ctxDescription = "Logger for S2S Libraries");
};

} // namespace s2s
} // namespace com
#endif
