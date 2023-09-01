//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         src/ucm/lib/utl/iofn_store.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       hbe1lud
/// @version
/// @remarks


#ifndef UCM_AAP_LIBRARY_UCM_LIB_UTL_IOFN_STORE_H_
#define UCM_AAP_LIBRARY_UCM_LIB_UTL_IOFN_STORE_H_

#include <functional>
#include <map>

#include <assert.h>
#include <errno.h>
#include <unistd.h>     // close

#include "ucm/mock/sequence.h"
#include "ucm/lib/utl/cutils.h"

#ifdef GOOGLE_TEST
#include "gtest/gtest_prod.h"
#endif

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace utl   {

/// Adapt generic read, write and close functions to the "Universal I/O Model" 
struct IOFnStore
        : virtual protected ucm::mock::Sequence
{
protected:

    /// Holds user provided implementations of I/O functions
    struct Item
    {
        std::function<ssize_t(      void*, size_t)>  read{};
        std::function<ssize_t(const void*, size_t)>  write{};
        std::function<int()>                         close{};
    };

    static struct Store
        : std::map<int, Item>
    {
       ~Store();
    } store;

    static int open_dummy_file();

public:
    using RdFn = ssize_t (*)(int,       void*, size_t);
    using WrFn = ssize_t (*)(int, const void*, size_t);
    using ClFn = int (*)(int);

    /** Store user-defined read, write and close functions
     *
     * @return Dummy file descriptor as key to stored functions */
    template<typename RD, typename WR, typename CL>
    static int open(RD&& rd_, WR&& wr_, CL&& cl_) noexcept
    {
        int fd = open_dummy_file();
        if (fd < 0)
            return -1;

        // insert to map
        try {
            auto rv = store.emplace(fd, Item {
                    static_cast<RD&&>(rd_),
                    static_cast<WR&&>(wr_),
                    static_cast<CL&&>(cl_)});
            if (rv.second)
            {
                assert (rv.first->first == fd);
                return rv.first->first;
            }
        }
        catch(...) {
        }
        TEMP_FAILURE_RETRY(::close(fd));
        errno = EEXIST;
        return -1;
    }

    // Universal I/O Model functions
    static ssize_t read(int , void* , size_t ) noexcept  {return pop<ssize_t>();}
    static ssize_t write(int , const void* , size_t ) noexcept {return pop<ssize_t>();}
    static int close(int ) noexcept {return pop<int>();}
};

} // namespace utl
} // namespace lib
} // namespace ucm
} // namespace vrte
} // namespace bosch

#endif // UCM_AAP_LIBRARY_UCM_LIB_UTL_IOFN_STORE_H_
