//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/frecord.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__FRECORD_H_
#define UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__FRECORD_H_

#include <vector>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/swc/types.h"
#include "ucm/lib/swc/depunit.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {

class FRecord
{
#if defined(GOOGLE_TEST)
    friend class Test_ucm_lib_swc_Fileops;
    FRIEND_TEST(Test_ucm_lib_swc__FRecord, CTor);
    FRIEND_TEST(Test_ucm_lib_swc__FRecord, CTor2);
    FRIEND_TEST(Test_ucm_lib_swc__FRecord, CTor3);
    FRIEND_TEST(Test_ucm_lib_swc__FRecord, CTor4);
    FRIEND_TEST(Test_ucm_lib_swc__FRecord, CTor5);
    FRIEND_TEST(Test_ucm_lib_swc__FRecord, CTor6);
    FRIEND_TEST(Test_ucm_lib_swc__FRecord, MoveMembers1);
    FRIEND_TEST(Test_ucm_lib_swc__FRecord, MoveMembers2);
#endif

public:
    enum class Type : unsigned
    {
        kCurr, kNext, kRemove
    };

    explicit FRecord() = default;

    explicit FRecord(unique_type&&, unique_type&&, Type&&, DepUnit&&,
                     std::string&&, std::vector<std::string>&&)
        noexcept(std::is_nothrow_move_constructible<Type>::value        &&
                 std::is_nothrow_move_constructible<DepUnit>::value     &&
                 std::is_nothrow_move_constructible<unique_type>::value &&
                 std::is_nothrow_move_constructible<std::string>::value &&
                 std::is_nothrow_move_constructible<
                         std::vector<std::string>>::value);

    explicit FRecord(const unique_type&, const unique_type&,
                     const Type&, DepUnit&&, const std::string&,
                     std::vector<std::string>&&)
        noexcept(std::is_nothrow_move_constructible<Type>::value        &&
                 std::is_nothrow_move_constructible<DepUnit>::value     &&
                 std::is_nothrow_move_constructible<unique_type>::value &&
                 std::is_nothrow_move_constructible<std::string>::value &&
                 std::is_nothrow_move_constructible<
                         std::vector<std::string>>::value);

    explicit FRecord(const unique_type&, const unique_type&,
                     const Type&, DepUnit&&, std::string&&,
                     std::vector<std::string>&&)
        noexcept(std::is_nothrow_move_constructible<Type>::value        &&
                 std::is_nothrow_move_constructible<DepUnit>::value     &&
                 std::is_nothrow_move_constructible<unique_type>::value &&
                 std::is_nothrow_move_constructible<std::string>::value &&
                 std::is_nothrow_move_constructible<
                         std::vector<std::string>>::value);

    explicit FRecord(const unique_type&, const unique_type&,
                     const Type&, DepUnit&&, std::vector<std::string>&&)
        noexcept(std::is_nothrow_move_constructible<Type>::value        &&
                 std::is_nothrow_move_constructible<DepUnit>::value     &&
                 std::is_nothrow_move_constructible<unique_type>::value &&
                 std::is_nothrow_move_constructible<std::string>::value &&
                 std::is_nothrow_move_constructible<
                         std::vector<std::string>>::value);

    explicit FRecord(Type&&, DepUnit&&, std::string&&,
                     std::vector<std::string>&&)
        noexcept(std::is_nothrow_move_constructible<Type>::value        &&
                 std::is_nothrow_move_constructible<DepUnit>::value     &&
                 std::is_nothrow_move_constructible<unique_type>::value &&
                 std::is_nothrow_move_constructible<std::string>::value &&
                 std::is_nothrow_move_constructible<
                         std::vector<std::string>>::value);


    FRecord(FRecord     &&) = default;
    FRecord(FRecord const&) = default;

    FRecord& operator=(FRecord     &&) = default;
    FRecord& operator=(FRecord const&) = default;

    virtual ~FRecord() = default;

    void set_type(Type&&) noexcept;
    void set_fsroot(std::string&&) noexcept;

    Type&        type()   & noexcept;
    DepUnit&     swunit() & noexcept;
    unique_type& unique() & noexcept;
    unique_type& cookie() & noexcept;
    std::string& fsroot() & noexcept;
    std::vector<std::string>& fslist() & noexcept;

    Type        type()   && noexcept;
    DepUnit     swunit() && noexcept;
    unique_type unique() && noexcept;
    unique_type cookie() && noexcept;
    std::string fsroot() && noexcept;
    std::vector<std::string> fslist() && noexcept;

    const Type&        type()    const & noexcept;
    const DepUnit&     swunit()  const & noexcept;
    const unique_type& unique()  const & noexcept;
    const unique_type& cookie()  const & noexcept;
    const std::string& fsroot()  const & noexcept;
    const std::vector<std::string>& fslist()  const & noexcept;

    const auto& swname()  const noexcept;
    const auto& version() const noexcept;

protected:
    Type        type_{};
    DepUnit     swunit_{};
    unique_type unique_{};
    unique_type cookie_{};
    std::string fsroot_{};
    std::vector<std::string> fslist_{};
};

template<typename OS>
OS operator<<(OS&& os, FRecord const& rec)
{
    os << "FRecord(type[" << static_cast<unsigned>(rec.type()) << "], "
       << rec.swunit() << ", unique[" << rec.unique() << "], cookie["
       << rec.cookie() << "], fsroot[" << rec.fsroot() << "], fslist [";
    auto&& lst = rec.fslist();
    auto   len = lst.size();
    for (std::size_t i = 0; i < len; ++i) {
        os << lst[i];
        if (i + 1 < len)
            os << ", ";
    }
    os << "]";
    return static_cast<OS&&>(os);
}

inline void FRecord::set_type(Type&& type) noexcept
{
    type_ = std::move(type);
}

inline void FRecord::set_fsroot(std::string&& value) noexcept
{
    fsroot_ = std::move_if_noexcept(value);
}

inline FRecord::Type& FRecord::type() & noexcept
{
    return type_;
}

inline DepUnit& FRecord::swunit() & noexcept
{
    return swunit_;
}

inline unique_type& FRecord::unique() & noexcept
{
    return unique_;
}

inline unique_type& FRecord::cookie() & noexcept
{
    return cookie_;
}

inline std::string& FRecord::fsroot() & noexcept
{
    return fsroot_;
}

inline std::vector<std::string>& FRecord::fslist() & noexcept
{
    return fslist_;
}

inline FRecord::Type FRecord::type() && noexcept
{
    return type_;
}

inline DepUnit FRecord::swunit() && noexcept
{
    return std::move(swunit_);
}

inline unique_type FRecord::unique() && noexcept
{
    return std::move(unique_);
}

inline unique_type FRecord::cookie() && noexcept
{
    return std::move(cookie_);
}

inline std::string FRecord::fsroot() && noexcept
{
    return std::move(fsroot_);
}

inline std::vector<std::string> FRecord::fslist() && noexcept
{
    return std::move(fslist_);
}

inline const FRecord::Type& FRecord::type() const & noexcept
{
    return type_;
}

inline const unique_type& FRecord::unique() const & noexcept
{
    return unique_;
}

inline const unique_type& FRecord::cookie() const & noexcept
{
    return cookie_;
}

inline const DepUnit& FRecord::swunit() const & noexcept
{
    return swunit_;
}

inline const std::string& FRecord::fsroot() const & noexcept
{
    return fsroot_;
}

inline const std::vector<std::string>& FRecord::fslist() const & noexcept
{
    return fslist_;
}

inline const auto& FRecord::swname() const noexcept
{
    return swunit_.swname();
}

inline const auto& FRecord::version() const noexcept
{
    return swunit_.version();
}

}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__FRECORD_H_

