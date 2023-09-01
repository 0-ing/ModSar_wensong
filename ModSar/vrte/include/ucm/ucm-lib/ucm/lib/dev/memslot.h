//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/dev/memslot.h
/// @brief
/// @copyright    Robert Bosch GmbH 2019
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_DEV_MEMSLOT_H_
#define UCM_AAP_LIBRARY_LIB_DEV_MEMSLOT_H_

#include <string>
#include <memory>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/types.h"
#include "ucm/lib/utl/object_locker.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace dev {

/// @brief The class describes a placeholder for a image.
/// A MemSlot is an placeholder on a memory device, slot is capable of
/// holding exactly one image. The MemSlot is unaware what image is - it
/// knows only part of which device it is, and eventually its size and location
/// within the memory device, if they have meaning for the particular case.
///
/// Each slot has a slot unique id (\ref suid_) for a lookup and reference key.
/// The slot unique id must be unique for all of the TargetProviders
class MemSlot final : public utl::ObjectLocker
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_dev_Memslot, CTor);
    FRIEND_TEST(Test_ucm_lib_dev_Memslot, Print);
    FRIEND_TEST(Test_ucm_lib_dev_Memslot, SetType);
    FRIEND_TEST(Test_ucm_lib_dev_Memslot, TypeAsIndex);
    FRIEND_TEST(Test_ucm_lib_dev_Memslot, TypeAsString);
    FRIEND_TEST(Test_ucm_lib_dev_Memslot, StringAsType);
#endif

public:
    constexpr static const id_type    sltid_invalid   = id_type_max;
    constexpr static const id_type    devid_invalid   = id_type_max;
    constexpr static const usize_type maxsize_invalid = usize_type_max;
    constexpr static const usize_type address_invalid = usize_type_max;

    enum class Type : unsigned
    {
        kNone,        // No specific designation
        kActive,      // Slot is in use by the ECU
        kStandby,     // Slot is not in use and ready to be written
        kFactory,     // Factory setting for the swcgroup
    };

    struct Specs
    {
        Type        type_     {Type::kNone};
        id_type     sltid_    {sltid_invalid};    // slot unique id
        id_type     devid_    {devid_invalid};    // containing device
        usize_type  maxsize_  {maxsize_invalid};  // max size of the slot
        usize_type  cursize_  {0};                // cur size of the slot's data
        usize_type  address_  {address_invalid};  // address on device
        std::string swcgroup_ {};                 // === Image.name
    };

    template<typename _T = std::size_t>
    static _T type_as_index(const Type& type) noexcept
    {
        return static_cast<_T>(type);
    }

    static const char* type_as_string(const Type& type) noexcept;

    static Type string_as_type(const std::string& name);

    static std::string print(const std::shared_ptr<MemSlot>&) noexcept;

    explicit MemSlot(Specs&&);

    // copy semantics
    MemSlot(const MemSlot&) = delete;
    MemSlot& operator=(const MemSlot&) = delete;

    // move semantic
    MemSlot(MemSlot&&) noexcept = delete;
    MemSlot& operator=(MemSlot&&) = delete;

    virtual ~MemSlot() = default;

    const auto& type() const noexcept;
    const auto& sltid() const noexcept;
    const auto& devid() const noexcept;
    const auto& maxsize() const noexcept;
    const auto& cursize() const noexcept;
    const auto& address() const noexcept;
    const auto& swcgroup() const noexcept;

    void settype_none() noexcept;
    void settype_active() noexcept;
    void settype_standby() noexcept;
    void settype_factory() noexcept;
    void setsize(const usize_type&);

private:
    Specs specs_;

    static Specs&& check_specs(Specs&& specs);
};

inline const auto& MemSlot::sltid() const noexcept
{
    return specs_.sltid_;
}

inline const auto& MemSlot::devid() const noexcept
{
    return specs_.devid_;
}

inline const auto& MemSlot::maxsize() const noexcept
{
    return specs_.maxsize_;
}

inline const auto& MemSlot::cursize() const noexcept
{
    return specs_.cursize_;
}

inline const auto& MemSlot::address() const noexcept
{
    return specs_.address_;
}

inline const auto& MemSlot::type() const noexcept
{
    return specs_.type_;
}

inline const auto& MemSlot::swcgroup() const noexcept
{
    return specs_.swcgroup_;
}

inline void MemSlot::settype_none() noexcept
{
    specs_.type_ = Type::kNone;
}

inline void MemSlot::settype_active() noexcept
{
    specs_.type_ = Type::kActive;
}

inline void MemSlot::settype_standby() noexcept
{
    specs_.type_ = Type::kStandby;
}

inline void MemSlot::settype_factory() noexcept
{
    specs_.type_ = Type::kFactory;
}

}    // namespace dev
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_DEV_MEMSLOT_H_
