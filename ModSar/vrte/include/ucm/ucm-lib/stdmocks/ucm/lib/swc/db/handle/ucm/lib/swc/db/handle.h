//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/db/handle.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_UCM_LIB_SWC_DB__HANDLE_H_
#define UCM_AAP_LIBRARY_UCM_LIB_SWC_DB__HANDLE_H_

#include <string>

#include "ucm/mock/sequence.h"
#include "ucm/lib/swc/db/mutex.h"
#include "ucm/lib/swc/db/query.h"
#include "ucm/lib/swc/db/result.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {


class Handle
        : virtual protected ucm::mock::Sequence
{
public:

    struct Tuple final
    {
        explicit Tuple(std::string&& name, std::string&& specs,
                       bool irecord, bool hrecord, bool frecord, bool srecord)
            noexcept(std::is_nothrow_constructible<bool>::value     &&
                     std::is_nothrow_move_constructible<std::string>::value)
        : name_{name}
        , specs_{specs}
        , irecord_enable_{irecord}
        , hrecord_enable_{hrecord}
        , frecord_enable_{frecord}
        , srecord_enable_{srecord}
        {
        }

        Tuple(Tuple     &&) = default;
        Tuple(Tuple const&) = default;

        Tuple& operator=(Tuple     &&) = default;
        Tuple& operator=(Tuple const&) = default;

        ~Tuple() = default;

        std::string name_;
        std::string specs_;
        bool irecord_enable_;
        bool hrecord_enable_;
        bool frecord_enable_;
        bool srecord_enable_;
    };

    explicit Handle(bool wlock, Mutex& mutex, const Tuple& tuple) noexcept
    : wlock_{wlock}
    , mutex_{mutex}
    , tuple_{tuple}
    {
    }

    Handle(Handle     &&) = default;
    Handle(Handle const&) = delete;

    Handle& operator=(Handle     &&) = default;
    Handle& operator=(Handle const&) = delete;

    virtual ~Handle() = default;

    const auto& name()  const noexcept;
    const auto& specs() const noexcept;

    bool has_irecord() const noexcept;
    bool has_hrecord() const noexcept;
    bool has_frecord() const noexcept;
    bool has_srecord() const noexcept;

    virtual void abort() noexcept = 0;

    virtual void commit() = 0;

    virtual Result do_query(Query&&) = 0;

protected:
    bool         wlock_{false};
    Mutex&       mutex_;
    const Tuple& tuple_;
};

inline const auto& Handle::name() const noexcept
{
    return pop<std::string const&>();
}

inline const auto& Handle::specs() const noexcept
{
    return pop<std::string const&>();
}

inline bool Handle::has_irecord() const noexcept
{
    return pop<bool>();
}

inline bool Handle::has_hrecord() const noexcept
{
    return pop<bool>();
}

inline bool Handle::has_frecord() const noexcept
{
    return pop<bool>();
}

inline bool Handle::has_srecord() const noexcept
{
    return pop<bool>();
}


}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_UCM_LIB_SWC_DB__HANDLE_H_
