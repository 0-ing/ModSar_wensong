#ifndef PIPC_LOGGER_HPP
#define PIPC_LOGGER_HPP

#define PIPC_LOG_LEVEL_OFF 0
#define PIPC_LOG_LEVEL_FATAL 1
#define PIPC_LOG_LEVEL_ERROR 2
#define PIPC_LOG_LEVEL_WARN 3
#define PIPC_LOG_LEVEL_INFO 4
#define PIPC_LOG_LEVEL_DEBUG 5
#define PIPC_LOG_LEVEL_VERBOSE 6

// Default log level is WARN, if nothing is set
#ifndef PIPC_MAX_LOG_LEVEL
#    define PIPC_MAX_LOG_LEVEL PIPC_LOG_LEVEL_WARN
#endif

#include <iostream>

namespace pipc
{
/**
 * @brief Logger interface for messages within PIPC.
 *
 * The logger interface can be redirected to forward log messages to
 * any logger implementation. By default PIPC compiles with
 * log messages directed towards std::cout.
 *
 * Logging can be configured to a max. level at compile time (to reduce the
 * size & runtime of the PIPC library).
 *
 * Logging can be additionally configured to a max. level at runtime, if the logger
 * implementation supports this. Note that the max. level set at runtime cannot
 * exceed the max. level set at compile time.
 *
 * @todo
 * Implement what is described, we start with minimal functionality:
 * Log to std::cout and set a max. level at compile time.
 */

/** @brief Stubbed logger with no real functionality.
 *
 * The StubLogger only consumes log messages, but does not forward them to a real logger.
 */
class StubLogger
{
public:
    /** @brief Sink for streamop calls with variables. */
    template<typename T>
    constexpr StubLogger& operator<<(T&)
    {
        return *this;
    }

    /** @brief Sink for streamop calls with variables. */
    template<typename T>
    constexpr StubLogger& operator<<(const T&)
    {
        return *this;
    }

    /** @brief Sink for streamop calls with functions (like std::endl). */
    constexpr StubLogger& operator<<(std::ostream& (*)(std::ostream&))
    {
        return *this;
    }

    /** @brief Get a pseudo-object of StubLogger. */
    constexpr static StubLogger& Get()
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

// TODO: Find solution for QNX to also print program name. program_invocation_short_name is only available on Linux.
#ifdef __QNX__
#    define program_invocation_short_name ""
#endif

/** @brief Logger for fatal severity. */
#if (PIPC_MAX_LOG_LEVEL >= PIPC_LOG_LEVEL_FATAL)
#    define PIPC_LOG_FATAL()                                                             \
        std::cout << "\033[1;31m[FATAL]\033[0m[" << program_invocation_short_name << "]" \
                  << "[" << pipc::short_file(__FILE__) << ", l. " << __LINE__ << "]: "
#else
#    define PIPC_LOG_FATAL() pipc::StubLogger::Get()
#endif

/** @brief Logger for error severity. */
#if (PIPC_MAX_LOG_LEVEL >= PIPC_LOG_LEVEL_ERROR)
#    define PIPC_LOG_ERROR()                                                             \
        std::cout << "\033[1;31m[ERROR]\033[0m[" << program_invocation_short_name << "]" \
                  << "[" << pipc::short_file(__FILE__) << ", l. " << __LINE__ << "]: "
#else
#    define PIPC_LOG_ERROR() pipc::StubLogger::Get()
#endif

/** @brief Logger for warn severity. */
#if (PIPC_MAX_LOG_LEVEL >= PIPC_LOG_LEVEL_WARN)
#    define PIPC_LOG_WARN()                                                                \
        std::cout << "\033[1;93m[WARNING]\033[0m[" << program_invocation_short_name << "]" \
                  << "[" << pipc::short_file(__FILE__) << ", l. " << __LINE__ << "]: "
#else
#    define PIPC_LOG_WARN() pipc::StubLogger::Get()
#endif

/** @brief Logger for info severity. */
#if (PIPC_MAX_LOG_LEVEL >= PIPC_LOG_LEVEL_INFO)
#    define PIPC_LOG_INFO()                                            \
        std::cout << "[INFO][" << program_invocation_short_name << "]" \
                  << "[" << pipc::short_file(__FILE__) << ", l. " << __LINE__ << "]: "
#else
#    define PIPC_LOG_INFO() pipc::StubLogger::Get()
#endif

/** @brief Logger for debug severity. */
#if (PIPC_MAX_LOG_LEVEL >= PIPC_LOG_LEVEL_DEBUG)
#    define PIPC_LOG_DEBUG()                                            \
        std::cout << "[DEBUG][" << program_invocation_short_name << "]" \
                  << "[" << pipc::short_file(__FILE__) << ", l. " << __LINE__ << "]: "
#else
#    define PIPC_LOG_DEBUG() pipc::StubLogger::Get()
#endif

/** @brief Logger for verbose severity. */
#if (PIPC_MAX_LOG_LEVEL >= PIPC_LOG_LEVEL_VERBOSE)
#    define PIPC_LOG_VERBOSE()                                            \
        std::cout << "[VERBOSE][" << program_invocation_short_name << "]" \
                  << "[" << pipc::short_file(__FILE__) << ", l. " << __LINE__ << "]: "
#else
#    define PIPC_LOG_VERBOSE() pipc::StubLogger::Get()
#endif

} // namespace pipc

#endif // PIPC_LOGGER_HPP
