#ifndef PIPC_UTILS_SEMAPHORE_HPP
#define PIPC_UTILS_SEMAPHORE_HPP

#include "ErrorHandler.hpp"
#include "TimeSpec.hpp"

#include <semaphore.h>
#include <sys/stat.h>

namespace pipc
{
namespace utils
{
/**
 * @brief Posix unnamed semaphore.
 *
 * @todo
 * Proper error reporting, if we use this class at the end.
 */
class Semaphore
{
public:
    /**
     * @brief Construct a semaphore.
     *
     * @param value Initialized value
     * @param shared Flag whether the semaphore shall be shared among processes
     */
    Semaphore(unsigned int value, bool shared)
    {
        int pshared = (shared) ? 1 : 0;
        if (sem_init(&sem_, pshared, value) != 0)
        {
            ErrorHandler::CriticalError(ErrorType::kPosix, "sem_init");
        }
    }

    /**
     * @brief Destructor.
     *
     * Destroys the underlying posix semaphore.
     */
    ~Semaphore()
    {
        int ret = sem_destroy(&sem_);
        if (ret == -1)
        {
            ErrorHandler::CriticalError(ErrorType::kPosix, "sem_destroy");
        }
    }

    /** @brief Wait on the semaphore. */
    void wait()
    {
        int ret;
        do
        {
            ret = sem_wait(&sem_);
        } while ((ret == -1) && (errno == EINTR));
        if (ret == -1)
        {
            ErrorHandler::CriticalError(ErrorType::kPosix, "sem_wait");
        }
    }

    /**
     * @brief Wait on the semaphore with a time limit.
     *
     * The function is templated so it can take any way to express time.
     * Usually a std::chrono object is expected here.
     *
     * @param time : The maximum time to wait.
     */
    template<typename T>
    bool wait(T time)
    {
        TimeSpec tm;
        tm.incr(time);
        int ret;
        do
        {
            ret = sem_timedwait(&sem_, &tm.get());
        } while ((ret == -1) && (errno == EINTR));
        if (ret == 0)
        {
            return true;
        }
        else
        {
            if (errno != ETIMEDOUT)
            {
                ErrorHandler::CriticalError(ErrorType::kPosix, "sem_timedwait");
            }
            return false;
        }
    }

    void post()
    {
        int ret = sem_post(&sem_);
        if (ret == -1)
        {
            ErrorHandler::CriticalError(ErrorType::kPosix, "sem_post");
        }
    }

private:
    sem_t sem_;
};

} // namespace utils
} // namespace pipc

#endif // PIPC_UTILS_SEMAPHORE_HPP
