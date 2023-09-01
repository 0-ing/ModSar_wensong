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

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace utl {

class UniqueId final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_utl_UniqueId, CTor);
#endif

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

        explicit UUID() noexcept(true);
        explicit UUID(const std::string& value);
        ~UUID() = default;

        inline const uuid_type_t& bin_value() const noexcept
        {
            return bin_value_;
        }

        inline const std::string& str_value() const noexcept
        {
            return str_value_;
        }

        inline const std::string& string_id() const noexcept
        {
            return string_id_;
        }

        inline const char* c_str() const noexcept
        {
            if (str_value_.empty())
                return nullptr;
            else
                return str_value_.c_str();
        }

        inline auto& stime32() const noexcept
        {
            return stime32_;
        }

        inline auto& stime64() const noexcept
        {
            return stime64_;
        }

        inline std::string short_str() const noexcept
        {
            try {
                // use the first (low time) part for reasonable distinction
                return std::string(str_value_.begin(), str_value_.begin() + 4);
            }
            catch(...) {}
            return std::string();
        }

        static void to_binary(uuid_type_t& bin, const std::string& str);
        static std::string to_string(const uuid_type_t& bin);
        static std::string string_id(const uuid_type_t& bin);

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

    static UUID generate() noexcept(true);

    static std::uint32_t random() noexcept(true);

private:
    static std::uint8_t macaddr_[6];
    static std::atomic_uint_fast32_t counter_;

    static void
    gettime(std::uint_fast32_t*, std::uint_fast32_t*) noexcept(true);
    static UniqueId& instance() noexcept(true);
    UniqueId() noexcept(true);
};

inline bool operator==(const UniqueId::UUID& lhs, const UniqueId::UUID& rhs)
{
    const UniqueId::uuid_type_t& rhsbin = rhs.bin_value();
    const UniqueId::uuid_type_t& lhsbin = lhs.bin_value();

    for (unsigned i = 0; i < sizeof(UniqueId::uuid_type_t); i++)
        if (rhsbin[i] != lhsbin[i])
            return false;
    return true;
}

inline bool operator!=(const UniqueId::UUID& lhs, const UniqueId::UUID& rhs)
{
    return !(lhs == rhs);
}

inline std::ostream& operator<< (std::ostream &os,
                                 const UniqueId::uuid_type_t& uuid)
{
    os << UniqueId::UUID::to_string(uuid);
    return os;
}

}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_UTL_UNIQUE_ID_H_
