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

#include "ucm/mock/sequence.h"
#include "ucm/lib/swc/types.h"
#include "ucm/lib/swc/depunit.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {

class FRecord
        : virtual protected ucm::mock::Sequence
{

public:
    enum class Type : unsigned
    {
        kCurr, kNext, kRemove
    };

    explicit FRecord() = default;

    explicit FRecord(unique_type&& unique, unique_type&& cookie, Type&& type, DepUnit&& swunit,
                     std::string&& fsroot, std::vector<std::string>&& fslist)
        noexcept(std::is_nothrow_move_constructible<Type>::value        &&
                 std::is_nothrow_move_constructible<DepUnit>::value     &&
                 std::is_nothrow_move_constructible<unique_type>::value &&
                 std::is_nothrow_move_constructible<std::string>::value &&
                 std::is_nothrow_move_constructible<
                         std::vector<std::string>>::value)
    : type_(std::move(type))
    , swunit_(std::move(swunit))
    , unique_(std::move(unique))
    , cookie_(std::move(cookie))
    , fsroot_(std::move(fsroot))
    , fslist_(std::move(fslist))
    {
    }

    explicit FRecord(const unique_type& unique, const unique_type& cookie,
                     const Type& type, DepUnit&& swunit, const std::string& fsroot,
                     std::vector<std::string>&& fslist)
        noexcept(std::is_nothrow_move_constructible<Type>::value        &&
                 std::is_nothrow_move_constructible<DepUnit>::value     &&
                 std::is_nothrow_move_constructible<unique_type>::value &&
                 std::is_nothrow_move_constructible<std::string>::value &&
                 std::is_nothrow_move_constructible<
                         std::vector<std::string>>::value)
    : FRecord(unique_type(unique), unique_type(cookie), Type(type),
              std::move(swunit), std::string(fsroot), std::move(fslist))
    {
    }

    explicit FRecord(const unique_type& unique, const unique_type& cookie,
                     const Type& type, DepUnit&& swunit, std::string&& fsroot,
                     std::vector<std::string>&& fslist)
        noexcept(std::is_nothrow_move_constructible<Type>::value        &&
                 std::is_nothrow_move_constructible<DepUnit>::value     &&
                 std::is_nothrow_move_constructible<unique_type>::value &&
                 std::is_nothrow_move_constructible<std::string>::value &&
                 std::is_nothrow_move_constructible<
                         std::vector<std::string>>::value)
    : FRecord(unique_type(unique), unique_type(cookie), Type(type),
              std::move(swunit), std::move(fsroot), std::move(fslist))
    {
    }

    explicit FRecord(const unique_type& unique, const unique_type& cookie,
                     const Type& type, DepUnit&& swunit, std::vector<std::string>&& fslist)
        noexcept(std::is_nothrow_move_constructible<Type>::value        &&
                 std::is_nothrow_move_constructible<DepUnit>::value     &&
                 std::is_nothrow_move_constructible<unique_type>::value &&
                 std::is_nothrow_move_constructible<std::string>::value &&
                 std::is_nothrow_move_constructible<
                         std::vector<std::string>>::value)
    : FRecord(unique_type(unique), unique_type(cookie), Type(type),
              std::move(swunit), std::string(""), std::move(fslist))
    {
    }

    explicit FRecord(Type&& type, DepUnit&& swunit, std::string&& fsroot,
                     std::vector<std::string>&& fslist)
        noexcept(std::is_nothrow_move_constructible<Type>::value        &&
                 std::is_nothrow_move_constructible<DepUnit>::value     &&
                 std::is_nothrow_move_constructible<unique_type>::value &&
                 std::is_nothrow_move_constructible<std::string>::value &&
                 std::is_nothrow_move_constructible<
                         std::vector<std::string>>::value)
    : FRecord(0, 0, std::move(type), std::move(swunit),
              std::move(fsroot), std::move(fslist))
    {
    }


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
    return os;
}

inline void FRecord::set_type(Type&&) noexcept
{
}

inline void FRecord::set_fsroot(std::string&&) noexcept
{
}

inline FRecord::Type& FRecord::type() & noexcept
{
    return pop<FRecord::Type&>();
}

inline DepUnit& FRecord::swunit() & noexcept
{
    return pop<DepUnit&>();
}

inline unique_type& FRecord::unique() & noexcept
{
    return pop<unique_type&>();
}

inline unique_type& FRecord::cookie() & noexcept
{
    return pop<unique_type&>();
}

inline std::string& FRecord::fsroot() & noexcept
{
    return pop<std::string&>();
}

inline std::vector<std::string>& FRecord::fslist() & noexcept
{
    return pop<std::vector<std::string>&>();
}

inline FRecord::Type FRecord::type() && noexcept
{
    return pop<FRecord::Type>();
}

inline DepUnit FRecord::swunit() && noexcept
{
    return pop<DepUnit>();
}

inline unique_type FRecord::unique() && noexcept
{
    return pop<unique_type>();
}

inline unique_type FRecord::cookie() && noexcept
{
    return pop<unique_type>();
}

inline std::string FRecord::fsroot() && noexcept
{
    return pop<std::string>();
}

inline std::vector<std::string> FRecord::fslist() && noexcept
{
    return pop<std::vector<std::string>>();
}

inline const FRecord::Type& FRecord::type() const & noexcept
{
    return pop<FRecord::Type const&>();
}

inline const unique_type& FRecord::unique() const & noexcept
{
    return pop<unique_type const&>();
}

inline const unique_type& FRecord::cookie() const & noexcept
{
    return pop<unique_type const&>();
}

inline const DepUnit& FRecord::swunit() const & noexcept
{
    return pop<DepUnit const&>();
}

inline const std::string& FRecord::fsroot() const & noexcept
{
    return pop<std::string const&>();
}

inline const std::vector<std::string>& FRecord::fslist() const & noexcept
{
    return pop<std::vector<std::string> const&>();
}

inline const auto& FRecord::swname() const noexcept
{
    return pop<std::string const&>();
}

inline const auto& FRecord::version() const noexcept
{
    return pop<Version const&>();
}

}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__FRECORD_H_

