//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/dev/image.h
/// @brief
/// @copyright    Robert Bosch GmbH 2019
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_LIBRARY_LIB_DEV_IMAGE_H_
#define UCM_LIBRARY_LIB_DEV_IMAGE_H_

#include <sys/types.h>

#include <array>
#include <memory>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif


#include "ucm/lib/dev/memslot.h"
#include "ucm/lib/utl/object_locker.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace dev {


class Image final : public utl::ObjectLocker
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_dev_Image, CTor);
    FRIEND_TEST(Test_ucm_lib_dev_Image, SetSlots);
    FRIEND_TEST(Test_ucm_lib_dev_Image, PrintSlots);
    FRIEND_TEST(Test_ucm_lib_dev_Image, Slot2Write);
#endif

public:
    constexpr static const id_type    imgid_invalid   = id_type_max;
    constexpr static const ssize_type maxsize_invalid = ssize_type_max;

    struct Specs
    {
        id_type     imgid_      {imgid_invalid};
        bool        mount_ro_   {true};
        bool        redundancy_ {true};
        std::string swcgroup_   {};
    };

    explicit Image(Specs&&);

    // copy semantics
    Image(const Image&) = delete;
    Image& operator=(const Image&) = delete;

    // move semantic
    Image(Image&&) noexcept = delete;
    Image& operator=(Image&&) = delete;

    ~Image() = default;

    auto& memslots() const noexcept;
    const auto& specs() const noexcept;
    const auto& imgid() const noexcept;
    const auto& mount_ro() const noexcept;
    const auto& redundancy() const noexcept;
    const auto& swcgroup() const noexcept;

    const std::shared_ptr<MemSlot>& slot2write();

    void setslots(std::array<std::shared_ptr<MemSlot>, 4>&&);

    std::string printslots() const noexcept;

private:
    Specs specs_;
    std::array<std::shared_ptr<MemSlot>, 4> memslots_{};

    static Specs&& check_specs(Specs&& specs);
};

inline auto& Image::memslots() const noexcept
{
    return memslots_;
}

inline const auto& Image::specs() const noexcept
{
    return specs_;
}

inline const auto& Image::imgid() const noexcept
{
    return specs_.imgid_;
}

inline const auto& Image::mount_ro() const noexcept
{
    return specs_.mount_ro_;
}

inline const auto& Image::redundancy() const noexcept
{
    return specs_.redundancy_;
}

inline const auto& Image::swcgroup() const noexcept
{
    return specs_.swcgroup_;
}

}    // namespace dev
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_LIBRARY_LIB_DEV_IMAGE_H_
