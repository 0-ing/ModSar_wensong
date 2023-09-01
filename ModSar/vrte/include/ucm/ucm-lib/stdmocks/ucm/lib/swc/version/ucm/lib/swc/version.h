//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/version.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__VERSION_H_
#define UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__VERSION_H_

#include <string>
#include <iostream>
#include <functional>

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {

class Version final
      : virtual protected ucm::mock::Sequence
{
public:
    using numconv_fn_type =
            std::function<void(
                    const std::string&,
                    unsigned long& major, unsigned long& minor,
                    unsigned long& patch, unsigned long& tweak)>;

    using tokconv_fn_type =
            std::function<std::string(
                    unsigned long major, unsigned long minor,
                    unsigned long patch, unsigned long tweak)>;

    using compare_fn_type =
            std::function<bool(
                    unsigned long major1, unsigned long minor1,
                    unsigned long patch1, unsigned long tweak1,
                    unsigned long major2, unsigned long minor2,
                    unsigned long patch2, unsigned long tweak2)>;

    struct Tuple
    {
        compare_fn_type eq{};
        compare_fn_type gt{};
        compare_fn_type lt{};
        compare_fn_type ge{};
        compare_fn_type le{};
        compare_fn_type ne{};
        tokconv_fn_type to_string{};
        numconv_fn_type to_number{};
    };

    explicit Version() {}

    explicit Version(std::string&& token)
    : token_(std::move(token))
    {
    }

    explicit Version(const std::string& token)
    : token_{token}
    {
    }

    Version(Version     &&) = default;
    Version(Version const&) = default;

    Version& operator=(Version     &&) = default;
    Version& operator=(Version const&) = default;

    virtual ~Version() = default;

    const auto& get_tuple() const noexcept;
    const auto& get_token() const noexcept;
    const auto& get_major() const noexcept;
    const auto& get_minor() const noexcept;
    const auto& get_patch() const noexcept;
    const auto& get_tweak() const noexcept;

private:
    Tuple           tuple_{};
    std::string     token_{};
    unsigned long   major_{0};
    unsigned long   minor_{0};
    unsigned long   patch_{0};
    unsigned long   tweak_{0};

    static void setup_tuple(Tuple&) noexcept {pop<void>();}

    static bool compare_eq(
            unsigned long, unsigned long,
            unsigned long, unsigned long,
            unsigned long, unsigned long,
            unsigned long, unsigned long) noexcept  {return pop<bool>();}

    static bool compare_gt(
            unsigned long, unsigned long,
            unsigned long, unsigned long,
            unsigned long, unsigned long,
            unsigned long, unsigned long) noexcept  {return pop<bool>();}

    static bool compare_lt(
            unsigned long, unsigned long,
            unsigned long, unsigned long,
            unsigned long, unsigned long,
            unsigned long, unsigned long) noexcept  {return pop<bool>();}

    static bool compare_ge(
            unsigned long, unsigned long,
            unsigned long, unsigned long,
            unsigned long, unsigned long,
            unsigned long, unsigned long) noexcept  {return pop<bool>();}

    static bool compare_le(
            unsigned long, unsigned long,
            unsigned long, unsigned long,
            unsigned long, unsigned long,
            unsigned long, unsigned long) noexcept  {return pop<bool>();}

    static bool compare_ne(
            unsigned long, unsigned long,
            unsigned long, unsigned long,
            unsigned long, unsigned long,
            unsigned long, unsigned long) noexcept  {return pop<bool>();}

    static void to_number(const std::string&,
                          unsigned long&, unsigned long&,
                          unsigned long&, unsigned long&)  { pop<void>();}

    static std::string to_string(
            unsigned long, unsigned long,
            unsigned long, unsigned long)  {return pop<std::string>();}

    static void validate(const std::string&) { pop<void>();}
};

inline std::ostream& operator<<(std::ostream&, const Version&) {return ucm::mock::Sequence::pop<std::ostream&>();}

inline bool operator<(const Version&, const Version&) {return ucm::mock::Sequence::pop<bool>();}
inline bool operator>(const Version&, const Version&) {return ucm::mock::Sequence::pop<bool>();}
inline bool operator<=(const Version&, const Version&) {return ucm::mock::Sequence::pop<bool>();}
inline bool operator>=(const Version&, const Version&) {return ucm::mock::Sequence::pop<bool>();}
inline bool operator==(const Version&, const Version&) {return ucm::mock::Sequence::pop<bool>();}
inline bool operator!=(const Version&, const Version&) {return ucm::mock::Sequence::pop<bool>();}

inline const auto& Version::get_tuple() const noexcept
{
    return pop<Tuple const&>();
}

inline const auto& Version::get_token() const noexcept
{
    return pop<std::string const&>();
}

inline const auto& Version::get_major() const noexcept
{
    return pop<unsigned long const&>();
}

inline const auto& Version::get_minor() const noexcept
{
    return pop<unsigned long const&>();
}

inline const auto& Version::get_patch() const noexcept
{
    return pop<unsigned long const&>();
}

inline const auto& Version::get_tweak() const noexcept
{
    return pop<unsigned long const&>();
}

}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__VERSION_H_

