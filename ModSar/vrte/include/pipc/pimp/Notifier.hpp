#ifndef PIPC_PIMP_NOTIFIER_HPP
#define PIPC_PIMP_NOTIFIER_HPP

#include "pipc/e2e/IntegralWrapper.hpp"
#include "pipc/utils/ErrorHandler.hpp"
#include "pipc/utils/TimeSpec.hpp"

#include <semaphore.h>
#include <sys/stat.h>

namespace pipc
{
namespace pimp
{
/**
 * @brief Notifier class for PIMP sockets.
 *
 * The Notifier is used as a signalling mechanism to inform readers about available data.
 *
 * It consists of a posix unnamed semaphore and an internal count value, which is used
 * for a user-space optimization in case a kernel call can be omitted.
 * The Notifier additionally provides plausibilization mechanisms to ensure correct
 * functionality of the semaphore, in case an untrusted process has corrupted it.
 *
 * @todo
 * Just a skeleton, implement me.
 */
template<e2e::E2EProtection CountValueProtection>
class Notifier
{
    /** @brief IntegralWrapper used for internal count value. */
    using IntegralWrapper = typename IntegralWrapper<int, QueueStateProtection>::type;

public:
    /**
     * @brief Construct a Notifier.
     */
    Notifier()
    {
        if (sem_init(&sem_, 1, 0) != 0)
        {
            ErrorHandler::CriticalError(ErrorType::kPosix, "sem_init");
        }
    }

    /**
     * @brief Destructor.
     *
     * Destroys the underlying posix semaphore.
     */
    ~Notifier()
    {
        int ret = sem_destroy(&sem_);
        if (ret == -1)
        {
            ErrorHandler::CriticalError(ErrorType::kPosix, "sem_destroy");
        }
    }

    /** @brief Check the integrity of the notifier. */
    inline ReturnVal check()
    {
    }

    /** @brief Send a notification. */
    inline ReturnVal notify()
    {
    }

    /** @brief Wait for a notification. */
    inline ReturnVal wait()
    {
    }

private:
    /** @brief The internal count value. */
    std::atomic<IntegralWrapper> count_;
    /** @brief The posix semaphore struct. */
    sem_t sem_;
    /** @brief Abort flag to cancel threads waiting on corrupted semaphores. */
    bool abort_;
};

} // namespace pimp
} // namespace pipc

#endif // PIPC_PIMP_NOTIFIER_HPP
