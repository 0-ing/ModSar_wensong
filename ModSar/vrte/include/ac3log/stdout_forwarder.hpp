#ifndef AC3LOG_STDOUT_FORWARDER_HPP
#define AC3LOG_STDOUT_FORWARDER_HPP

#define STDOUT_LOG_LEVEL_OFF 0
#define STDOUT_LOG_LEVEL_FATAL 1
#define STDOUT_LOG_LEVEL_ERROR 2
#define STDOUT_LOG_LEVEL_WARN 3
#define STDOUT_LOG_LEVEL_INFO 4
#define STDOUT_LOG_LEVEL_DEBUG 5
#define STDOUT_LOG_LEVEL_VERBOSE 6

#ifndef STDOUT_MAX_LOG_LEVEL
#    define STDOUT_MAX_LOG_LEVEL STDOUT_LOG_LEVEL_ERROR
#endif

#include <iostream>

/** @brief Stubbed logger with no real functionality.
 *
 * The StubLogger only consumes log messages, but does not forward them to a real logger.
 */
class StubLogger
{
public:
    /** @brief Sink for streamop calls with variables. */
    template<typename T>
    inline StubLogger& operator<<(T&)
    {
        return *this;
    }

    /** @brief Sink for streamop calls with variables. */
    template<typename T>
    inline StubLogger& operator<<(const T&)
    {
        return *this;
    }

    /** @brief Sink for streamop calls with functions (like std::endl). */
    inline StubLogger& operator<<(std::ostream& (*)(std::ostream&))
    {
        return *this;
    }

    /** @brief Get a pseudo-object of StubLogger. */
    inline static StubLogger& Get()
    {
        StubLogger* tmp = nullptr;
        return *static_cast<StubLogger*>(tmp);
    }
};

/**
 * @brief Function which takes a substring of a __FILE__ macro.
 *
 * The string is reduced to show only the file name and the last folder.
 * Example: "abc/def/ghi" becomes "def/ghi"
 *
 * @todo
 * Still stores the full strings in memory, is that a problem?
 */
template<size_t N>
static constexpr const char* short_file(const char (&str)[N])
{
    size_t slashCount = 0;
    for (size_t pos = N - 1; pos > 0; pos--)
    {
        if (str[pos] == '/')
        {
            slashCount++;
            if (slashCount == 2)
            {
                return &str[pos + 1];
            }
        }
    }
    return str;
}

#define __SHORT_FILE__ short_file(__FILE__)

namespace iox_ac3log_adapter
{
// TODO: Find solution for QNX to also print program name. program_invocation_short_name is only available on Linux.
#ifdef __QNX__
#    define program_invocation_short_name ""
#endif

/** @brief Logger for fatal severity. */
#if (STDOUT_MAX_LOG_LEVEL >= STDOUT_LOG_LEVEL_FATAL)
#    define log_fatal()                                                                  \
        std::cout << "\033[1;31m[FATAL]\033[0m[" << program_invocation_short_name << "]" \
                  << "[" << __SHORT_FILE__ << ", l. " << __LINE__ << "]: "
#else
#    define log_fatal() StubLogger::Get()
#endif

/** @brief Logger for error severity. */
#if (STDOUT_MAX_LOG_LEVEL >= STDOUT_LOG_LEVEL_ERROR)
#    define log_error()                                                                  \
        std::cout << "\033[1;31m[ERROR]\033[0m[" << program_invocation_short_name << "]" \
                  << "[" << __SHORT_FILE__ << ", l. " << __LINE__ << "]: "
#else
#    define log_error() StubLogger::Get()
#endif

/** @brief Logger for warn severity. */
#if (STDOUT_MAX_LOG_LEVEL >= STDOUT_LOG_LEVEL_WARN)
#    define log_warn()                                                                     \
        std::cout << "\033[1;93m[WARNING]\033[0m[" << program_invocation_short_name << "]" \
                  << "[" << __SHORT_FILE__ << ", l. " << __LINE__ << "]: "
#else
#    define log_warn() StubLogger::Get()
#endif

/** @brief Logger for info severity. */
#if (STDOUT_MAX_LOG_LEVEL >= STDOUT_LOG_LEVEL_INFO)
#    define log_info()                                                 \
        std::cout << "[INFO][" << program_invocation_short_name << "]" \
                  << "[" << __SHORT_FILE__ << ", l. " << __LINE__ << "]: "
#else
#    define log_info() StubLogger::Get()
#endif

/** @brief Logger for debug severity. */
#if (STDOUT_MAX_LOG_LEVEL >= STDOUT_LOG_LEVEL_DEBUG)
#    define log_debug()                                                 \
        std::cout << "[DEBUG][" << program_invocation_short_name << "]" \
                  << "[" << __SHORT_FILE__ << ", l. " << __LINE__ << "]: "
#else
#    define log_debug() StubLogger::Get()
#endif

/** @brief Logger for verbose severity. */
#if (STDOUT_MAX_LOG_LEVEL >= STDOUT_LOG_LEVEL_VERBOSE)
#    define log_verbose()                                                 \
        std::cout << "[VERBOSE][" << program_invocation_short_name << "]" \
                  << "[" << __SHORT_FILE__ << ", l. " << __LINE__ << "]: "
#else
#    define log_verbose() StubLogger::Get()
#endif

} // namespace iox_ac3log_adapter

#endif // AC3LOG_STDOUT_FORWARDER_HPP
