//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/db/bdb/header.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__HEADER_H_
#define UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__HEADER_H_

#include <arpa/inet.h>

#include <cstdint>
#include <type_traits>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

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

class Header final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__Header, CTor);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__Header, Load);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__Header, Save);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__Header, PLoad);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__Header, PSave);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__Header, IOLoad1);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__Header, IOLoad2);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__Header, IOSave1);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__Header, IOSave2);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__Header, IOPLoad);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__Header, IOPSave);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__Header, IORZeroPad);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__Header, IOWZeroPad);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__Header, IORZeroPPad);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__Header, IOWZeroPPad);
#endif

    constexpr static size_t   defalign      = sizeof(uint64_t);
    constexpr static uint32_t magic_ucm     = static_cast<uint32_t>(0x88311911);
    constexpr static uint32_t magic_ext     = static_cast<uint32_t>(0x88301911);

public:
    using datasz_type = std::uint64_t;

    static void io_wzero_pad(utl::FileIO&, size_t);
    static void io_rzero_pad(utl::FileIO&, size_t);

    static void io_wzero_ppad(utl::FileIO&, off_t, size_t);
    static void io_rzero_ppad(utl::FileIO&, off_t, size_t);

    static void io_load(utl::FileIO&, std::string&, size_t);
    static void io_save(utl::FileIO&, const std::string&, size_t);

    static void io_load(utl::FileIO&,
                        void *const buff, size_t bsize, size_t pad);
    static void io_save(utl::FileIO&,
                        const void *buff, size_t bsize, size_t pad);

    static void io_pload(utl::FileIO&, off_t,
                         void *const buff, size_t bsize, size_t pad);
    static void io_psave(utl::FileIO&, off_t,
                         const void *buff, size_t bsize, size_t pad);

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

    explicit Header();

    explicit Header(const Fields&);

    Header(Header     &&) = default;
    Header(Header const&) = default;

    Header& operator=(Header     &&) = default;
    Header& operator=(Header const&) = default;

    ~Header() = default;

    void load(lib::utl::FileIO&);
    void save(lib::utl::FileIO&);

    void pload(lib::utl::FileIO&);
    void psave(lib::utl::FileIO&);


    Fields& fields() & noexcept;
    Fields  fields() && noexcept;
    const Fields& fields() const & noexcept;

private:
    Fields fields_{};

    void clock_update() noexcept;

    static void fields_ntoh(const Fields&, Fields&) noexcept;
    static void fields_hton(const Fields&, Fields&) noexcept;
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
            static_cast<uint32_t>(defalign));
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
