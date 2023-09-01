//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         src/ucm/lib/aec/archive.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_ARC_ARCHIVE_H_
#define UCM_AAP_LIBRARY_LIB_ARC_ARCHIVE_H_

#include <mutex>
#include <memory>
#include <string>
#include <vector>

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace arc   {


class Archive
    : virtual protected ucm::mock::Sequence
{
public:
    struct Item
    {
        std::string path;
        std::size_t size;
    };
    using List = std::vector<Item>;

    template<typename T, typename... U>
    static std::unique_ptr<Archive> make(U&&...)
    {
        return pop<std::unique_ptr<Archive>>();
    }

    virtual ~Archive() = 0;

    void open(std::string const&) { return pop<void>(); }
    void root(std::string const&) { return pop<void>(); }
    void close() { return pop<void>(); }

    List list() { return pop<List>(); }
    void extract() { return pop<void>(); }
    void extract(std::string const&) { return pop<void>(); }
    std::string root() { return pop<std::string>(); }
    std::size_t size() { return pop<std::size_t>(); }

protected:

    Archive()                          = default;
    Archive(Archive const&)            = default;
    Archive(Archive     &&) noexcept   = default;
    Archive& operator=(Archive const&) = default;
    Archive& operator=(Archive     &&) = default;

    enum class State
    {
        uninitialized,
        opened,
        done
    } state {State::uninitialized};

    // interface implementation
    virtual void _open()                      {};
    virtual void _close()                     {};
    virtual void _extract(std::string const&) {};

    virtual List _list() { return pop<List>(); };

    static std::string realpath_(std::string const&)
    {
        return pop<std::string>();
    }

    std::string root_ {};
    std::string path_ {};
    std::mutex  mutex_{};
};

inline Archive::~Archive() = default;


} // namespace arc
} // namespace lib
} // namespace ucm
} // namespace vrte
} // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_ARC_ARCHIVE_H_
