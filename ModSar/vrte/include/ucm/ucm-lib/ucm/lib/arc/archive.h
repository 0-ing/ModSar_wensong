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

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace arc   {


class Archive
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_Lib_Arc_Archive, Simple);
#endif

public:
    struct Item
    {
        std::string path;
        std::size_t size;
    };
    using List = std::vector<Item>;

    template<typename T, typename... U>
    static std::unique_ptr<Archive> make(U&&... u)
    {
        return std::unique_ptr<Archive>(new T(static_cast<U&&>(u)...));
    }

    virtual ~Archive();

    void open(std::string const&);
    void root(std::string const&);
    void close();

    List list();
    void extract();
    void extract(std::string const&);
    std::string root();
    std::size_t size();

protected:
    Archive()                          = default;
    Archive(Archive const&)            = delete;
    Archive(Archive     &&) noexcept   = delete;
    Archive& operator=(Archive const&) = delete;
    Archive& operator=(Archive     &&) = delete;

    enum class State
    {
        uninitialized,
        opened,
        done
    } state {State::uninitialized};

    // interface implementation
    virtual void _open()                      = 0;
    virtual List _list()                      = 0;
    virtual void _close()                     = 0;
    virtual void _extract(std::string const&) = 0;

    static std::string realpath_(std::string const&);

    std::string root_ {};
    std::string path_ {};
    std::mutex  mutex_{};
};


} // namespace arc
} // namespace lib
} // namespace ucm
} // namespace vrte
} // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_ARC_ARCHIVE_H_
