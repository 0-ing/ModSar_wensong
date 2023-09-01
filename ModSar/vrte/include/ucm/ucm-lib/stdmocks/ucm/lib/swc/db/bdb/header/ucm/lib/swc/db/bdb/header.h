//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         tests/VRTE_UT/mocks/ucm/lib/swc/db/bdb/irecord/ucm/lib/swc/db/bdb/header.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__HEADER_H_
#define UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__HEADER_H_

#include "ucm/lib/utl/file_io.h"
#include "ucm/lib/utl/cpputils.h"
#include "ucm/lib/swc/db/types.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {
namespace bdb   {

struct Header : virtual protected ucm::mock::Sequence
{
    static void io_wzero_pad(utl::FileIO&, size_t) {}
    static void io_rzero_pad(utl::FileIO&, size_t) {}

    static void io_wzero_ppad(utl::FileIO&, off_t, size_t) {}
    static void io_rzero_ppad(utl::FileIO&, off_t, size_t) {}

    static void io_load(utl::FileIO&, std::string& str, size_t)
    {
        const std::string& t_str = pop<const std::string&>();
        str += t_str;
    }

    static void io_save(utl::FileIO&, const std::string&, size_t) {}

    static void io_load(utl::FileIO&, void *const buff, size_t size, size_t)
    {
        const void *t_buff = pop<const void *>();
        size_t t_size = pop<size_t>();
        memcpy(buff, t_buff, std::min(t_size, size));
    }
    static void io_save(utl::FileIO&, const void*, size_t, size_t) {}

    static void io_pload(utl::FileIO&, off_t, void *const, size_t, size_t) {}
    static void io_psave(utl::FileIO&, off_t, const void*, size_t, size_t) {}

    struct Fields final
    {
        uint32_t    magic_;             // Magic number
        unique_type count_;             // Number of records
        unique_type unique_;            // First available unique
        tstamp_type created_;           // When the history file was created
        tstamp_type updated_;           // When the history file was updated
    } __attribute__((packed));

    constexpr static auto fields_size() noexcept;

    constexpr static auto fields_write_size() noexcept;

    constexpr static auto fields_zeropad_size() noexcept;

    explicit Header() {}

    explicit Header(const Fields&) {}

    Header(Header     &&) = default;
    Header(Header const&) = default;

    Header& operator=(Header     &&) = default;
    Header& operator=(Header const&) = default;

    ~Header() = default;

    void load(lib::utl::FileIO&) {}
    void save(lib::utl::FileIO&) {}

    void pload(lib::utl::FileIO&) {}
    void psave(lib::utl::FileIO&) {}


    Fields& fields() & noexcept;
    Fields  fields() && noexcept;
    const Fields& fields() const & noexcept;

private:
    Fields fields_{};
};

inline Header::Fields& Header::fields() & noexcept
{
    return fields_;
}

inline Header::Fields Header::fields() && noexcept
{
    return fields_;
}

inline const Header::Fields& Header::fields() const & noexcept
{
    return fields_;
}

constexpr inline auto Header::fields_size() noexcept
{
    return sizeof(Fields);
}

constexpr inline auto Header::fields_write_size() noexcept
{
    return utl::align_up(
            static_cast<uint32_t>(sizeof(Fields)),
            static_cast<uint32_t>(64));
}

constexpr inline auto Header::fields_zeropad_size() noexcept
{
    return fields_write_size() - fields_size();
}


}    // namespace bdb
}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__HEADER_H_
