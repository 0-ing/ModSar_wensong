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

#include "ucm/mock/sequence.h"
#include "ucm/lib/types.h"
#include "ucm/lib/utl/object_locker.h"


namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace dev {

class MemSlot final
    : public utl::ObjectLocker
    , virtual protected ucm::mock::Sequence
{
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

    static const char* type_as_string(const Type&) noexcept { return mock::Sequence::pop<char const*>(); }

    static Type string_as_type(const std::string&) {return mock::Sequence::pop<Type>(); }

    static std::string print(const std::shared_ptr<MemSlot>&) noexcept { return mock::Sequence::pop<std::string>(); }

    explicit MemSlot(Specs&&) {}

    // copy semantics
    MemSlot(const MemSlot&) = delete;
    MemSlot& operator=(const MemSlot&) = delete;

    // move semantic
    MemSlot(MemSlot&&) noexcept = delete;
    MemSlot& operator=(MemSlot&&) = delete;

    virtual ~MemSlot() = default;

    const auto& type() const noexcept { return mock::Sequence::pop<Type const&>(); }
    const auto& sltid() const noexcept { return mock::Sequence::pop<id_type const&>(); }
    const auto& devid() const noexcept { return mock::Sequence::pop<id_type const&>(); }
    const auto& maxsize() const noexcept { return mock::Sequence::pop<usize_type const&>(); }
    const auto& cursize() const noexcept { return mock::Sequence::pop<usize_type const&>(); }
    const auto& address() const noexcept { return mock::Sequence::pop<usize_type const&>(); }
    const auto& swcgroup() const noexcept { return mock::Sequence::pop<std::string const&>(); }

    void settype_none() noexcept { mock::Sequence::pop<void>(); }
    void settype_active() noexcept { mock::Sequence::pop<void>(); }
    void settype_standby() noexcept { mock::Sequence::pop<void>(); }
    void settype_factory() noexcept { mock::Sequence::pop<void>(); }
    void setsize(const usize_type&) { mock::Sequence::pop<void>(); }
};

}    // namespace dev
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_DEV_MEMSLOT_H_
