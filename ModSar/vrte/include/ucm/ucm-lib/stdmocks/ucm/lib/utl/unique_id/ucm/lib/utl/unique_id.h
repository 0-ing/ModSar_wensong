//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/utl/unique_id.h
/// @brief
/// @copyright    Robert Bosch GmbH 2018
/// @author       Vesselin Mladenov
/// @version
/// @remarks


#ifndef UCM_AAP_LIBRARY_LIB_UTL_UNIQUE_ID_H_
#define UCM_AAP_LIBRARY_LIB_UTL_UNIQUE_ID_H_

#include <string>
#include <atomic>
#include <cstdint>

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace utl {

class UniqueId final
      : virtual protected ucm::mock::Sequence
{
public:
    using uuid_type_t = std::uint8_t[16];

    class UUID
    {
    public:
        // copy semantics
        UUID(const UUID&) = delete;
        UUID& operator=(const UUID&) = delete;

        // move semantic
        UUID(UUID&&) = default;
        UUID& operator=(UUID&&) = default;

        explicit UUID() noexcept(true) {};
        explicit UUID(const std::string& ) {};
        ~UUID() = default;

        inline const uuid_type_t& bin_value() const noexcept
        {
            return pop<uuid_type_t const&>();
        }

        inline const std::string& str_value() const noexcept
        {
            return pop<std::string const&>();
        }

        inline const std::string& string_id() const noexcept
        {
            return pop<std::string const&>();
        }

        inline const char* c_str() const noexcept
        {
            return pop<const char*>();
        }

        inline auto& stime32() const noexcept
        {
            return pop<std::uint32_t&>();
        }

        inline auto& stime64() const noexcept
        {
            return pop<std::uint64_t&>();
        }

        inline std::string short_str() const noexcept
        {
            {return pop<std::string>();}
        }

        static void to_binary(uuid_type_t&, const std::string&) { pop<void>();}
        static std::string to_string(const uuid_type_t&) {return pop<std::string>();}
        static std::string string_id(const uuid_type_t&) {return pop<std::string>();}

    private:
        uuid_type_t bin_value_;
        std::string str_value_{};
        std::string string_id_{};
        std::uint32_t stime32_{};
        std::uint64_t stime64_{};
    };

    // copy semantics
    UniqueId(const UniqueId&) = delete;
    UniqueId& operator=(const UniqueId&) = delete;

    // move semantic
    UniqueId(UniqueId&&) = delete;
    UniqueId& operator=(UniqueId&&) = delete;

    static UUID generate() noexcept(true) { return UUID(); };

    static std::uint32_t random() noexcept(true);

private:
    static std::uint8_t macaddr_[6];
    static std::atomic_uint_fast32_t counter_;

    static void
    gettime(std::uint_fast32_t*, std::uint_fast32_t*) noexcept(true) { pop<void>();}
    static UniqueId& instance() noexcept(true) {return pop<UniqueId&>();}
    UniqueId() noexcept(true) { pop<void>();}
};

inline bool operator==(const UniqueId::UUID&, const UniqueId::UUID&)
{
  return ucm::mock::Sequence::pop<bool>();
}

inline bool operator!=(const UniqueId::UUID&, const UniqueId::UUID&)
{
    return ucm::mock::Sequence::pop<bool>();
}

inline std::ostream& operator<< (std::ostream &os,
                                 const UniqueId::uuid_type_t&)
{
    return os;
}

}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_UTL_UNIQUE_ID_H_
