#ifndef NAMED_SEMAPHORE_HPP
#define NAMED_SEMAPHORE_HPP

#include <errno.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <sys/stat.h>

namespace pipc
{
/**
 * @brief Posix named semaphore.
 *
 * @todo
 * Proper error reporting, if we use this class at the end.
 */
class NamedSemaphore
{
public:
    NamedSemaphore(unsigned int value, const char* name, mode_t mode = 0777)
    {
        name_ = name;
        sem_  = sem_open(name, O_CREAT, mode, value);
        if (sem_ == SEM_FAILED)
        {
            printf("sem_open error: %d\n", errno);
        }
    }

    ~NamedSemaphore()
    {
        if (sem_ != SEM_FAILED)
        {
            if (sem_close(sem_) != 0)
            {
                printf("sem_close error: %d\n", errno);
            }
            if (sem_unlink(name_) != 0)
            {
                printf("sem_unlink error: %d\n", errno);
            }
            sem_ = nullptr;
        }
    }

    void wait()
    {
        int ret;
        do
        {
            ret = sem_wait(sem_);
        } while ((ret == -1) && (errno == EINTR));
    }

    void post()
    {
        sem_post(sem_);
    }

private:
    sem_t* sem_{SEM_FAILED};
    const char* name_;
};

} // namespace pipc

#endif // NAMED_SEMAPHORE_HPP
