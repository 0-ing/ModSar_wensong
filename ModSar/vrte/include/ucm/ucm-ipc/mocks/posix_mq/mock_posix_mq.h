//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/mocks/posix_mq/mock_posix_mq.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_IPC__TESTS_VRTE_UT_MOCKS_POSIX_MQ__MOCK_POSIX_MQ__H_
#define UCM_AAP_IPC__TESTS_VRTE_UT_MOCKS_POSIX_MQ__MOCK_POSIX_MQ__H_

#include <vector>

#include "ucm/mock/sequence.h"

std::size_t                  __mock_clock_gettime_idx =  0;
std::vector<int>             __mock_clock_gettime_ret = {0};
std::vector<struct timespec> __mock_clock_gettime_buf = {{}};
extern "C" {
int __real_clock_gettime(clockid_t clock_id, struct timespec *tp);

int __wrap_clock_gettime(clockid_t clock_id, struct timespec *tp)
{
    using namespace bosch::vrte::ucm::mock;

    if (Mock::mock(clock_gettime)) {
        if (__mock_clock_gettime_idx >= __mock_clock_gettime_ret.size())
            __mock_clock_gettime_idx = 0;
        if (not tp)
            std::terminate();
        auto tt = __mock_clock_gettime_buf.at(__mock_clock_gettime_idx);
        memcpy(tp, &tt, sizeof(*tp));
        return __mock_clock_gettime_ret.at(__mock_clock_gettime_idx++);
    }
    return __real_clock_gettime(clock_id, tp);
}
} // extern "C"

std::size_t                  __mock_mq_open_idx =  0;
std::vector<int>             __mock_mq_open_ret = {0};
std::vector<int>             __mock_mq_open_err = {0};
extern "C" {
mqd_t __real_mq_open(const char *name, int oflag, ...);

mqd_t __wrap_mq_open(const char *name, int oflag, ...)
{
    using namespace bosch::vrte::ucm::mock;

    if (Mock::mock(mq_open)) {
        if (__mock_mq_open_idx >= __mock_mq_open_ret.size())
            __mock_mq_open_idx = 0;
        if (not name)
            std::terminate();
        errno = __mock_mq_open_err.at(__mock_mq_open_idx);
        return  __mock_mq_open_ret.at(__mock_mq_open_idx++);
    }
    return __real_mq_open(name, oflag);
}
} // extern "C"

std::size_t                  __mock_mq_close_idx =  0;
std::vector<int>             __mock_mq_close_ret = {0};
std::vector<int>             __mock_mq_close_err = {0};
extern "C" {
int __real_mq_close(mqd_t mqdes);

int __wrap_mq_close(mqd_t mqdes)
{
    using namespace bosch::vrte::ucm::mock;

    if (Mock::mock(mq_close)) {
        if (__mock_mq_close_idx >= __mock_mq_close_ret.size())
            __mock_mq_close_idx = 0;
        errno = __mock_mq_close_err.at(__mock_mq_close_idx);
        return  __mock_mq_close_ret.at(__mock_mq_close_idx++);
    }
    return __real_mq_close(mqdes);
}
} // extern "C"


std::size_t                     __mock_mq_receive_idx;
std::vector<ssize_t>            __mock_mq_receive_ret{8};
std::vector<int>                __mock_mq_receive_err{8};
std::vector<struct ucm_ipcmsg>  __mock_mq_receive_buf{8};
extern "C" {
ssize_t __real_mq_receive(mqd_t mqdes, char *msg_ptr,
                          size_t msg_len, unsigned int *msg_prio);

ssize_t  __wrap_mq_receive(mqd_t mqdes, char *msg_ptr,
                           size_t msg_len, unsigned int *msg_prio)
{
    using namespace bosch::vrte::ucm::mock;

    if (Mock::mock(mq_receive)) {
        if (__mock_mq_receive_idx >= __mock_mq_receive_ret.size())
            __mock_mq_receive_idx = 0;
        auto msg = __mock_mq_receive_buf[__mock_mq_receive_idx];
        memcpy(msg_ptr, &msg, msg_len);
        errno = __mock_mq_receive_err.at(__mock_mq_receive_idx);
        return  __mock_mq_receive_ret.at(__mock_mq_receive_idx++);
    }
    return __real_mq_receive(mqdes, msg_ptr, msg_len, msg_prio);
}
} // extern "C"

std::size_t                     __mock_mq_timedreceive_idx;
std::vector<ssize_t>            __mock_mq_timedreceive_ret{8};
std::vector<int>                __mock_mq_timedreceive_err{8};
std::vector<struct ucm_ipcmsg>  __mock_mq_timedreceive_buf{8};
extern "C" {
ssize_t __real_mq_timedreceive(mqd_t mqdes, char *msg_ptr, size_t msg_len,
                               unsigned int *msg_prio, struct timespec *tp);

ssize_t  __wrap_mq_timedreceive(mqd_t mqdes, char *msg_ptr, size_t msg_len,
                                unsigned int *msg_prio, struct timespec *tp)
{
    using namespace bosch::vrte::ucm::mock;

    if (Mock::mock(mq_timedreceive)) {
        if (__mock_mq_timedreceive_idx >= __mock_mq_timedreceive_ret.size())
            __mock_mq_timedreceive_idx = 0;
        auto msg = __mock_mq_timedreceive_buf[__mock_mq_timedreceive_idx];
        memcpy(msg_ptr, &msg, msg_len);
        errno = __mock_mq_timedreceive_err.at(__mock_mq_timedreceive_idx);
        return  __mock_mq_timedreceive_ret.at(__mock_mq_timedreceive_idx++);
    }
    return __real_mq_timedreceive(mqdes, msg_ptr, msg_len, msg_prio, tp);
}
} // extern "C"

std::size_t                     __mock_mq_timedsend_idx;
std::vector<ssize_t>            __mock_mq_timedsend_ret{8};
std::vector<int>                __mock_mq_timedsend_err{8};
std::vector<struct ucm_ipcmsg>  __mock_mq_timedsend_buf{8};
extern "C" {
ssize_t __real_mq_timedsend(mqd_t mqdes, const char *msg_ptr,
                            size_t msg_len, unsigned int msg_prio,
                            const struct timespec *abs_timeout);

ssize_t  __wrap_mq_timedsend(mqd_t mqdes, const char *msg_ptr,
                             size_t msg_len, unsigned int msg_prio,
                             const struct timespec *abs_timeout)
{
    using namespace bosch::vrte::ucm::mock;

    if (Mock::mock(mq_timedsend)) {
        if (__mock_mq_timedsend_idx >= __mock_mq_timedsend_ret.size())
            __mock_mq_timedsend_idx = 0;
        auto msg = __mock_mq_timedsend_buf[__mock_mq_timedsend_idx];
        memcpy(&msg, msg_ptr, msg_len);
        errno = __mock_mq_timedsend_err.at(__mock_mq_timedsend_idx);
        return  __mock_mq_timedsend_ret.at(__mock_mq_timedsend_idx++);
    }
    return __real_mq_timedsend(mqdes, msg_ptr, msg_len, msg_prio, abs_timeout);
}
} // extern "C"


#endif // UCM_AAP_IPC__TESTS_VRTE_UT_MOCKS_POSIX_MQ__MOCK_POSIX_MQ__H_
