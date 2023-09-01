//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/db/result.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_UCM_LIB_SWC_DB__RESULT_H_
#define UCM_AAP_LIBRARY_UCM_LIB_SWC_DB__RESULT_H_

#include <bitset>
#include <functional>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/swc/error.h"
#include "ucm/lib/swc/irecord.h"
#include "ucm/lib/swc/hrecord.h"
#include "ucm/lib/swc/frecord.h"
#include "ucm/lib/swc/srecord.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {


class Result final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_swc_db__Result, CTor);
    FRIEND_TEST(Test_ucm_lib_swc_db__Result, SetRecords);
#endif
public:
    explicit Result() = default;

    Result(Result     &&) = default;
    Result(Result const&) = delete;

    Result& operator=(Result     &&) = default;
    Result& operator=(Result const&) = delete;

    ~Result() = default;

    std::vector<IRecord>& irecords() & noexcept;
    std::vector<HRecord>& hrecords() & noexcept;
    std::vector<FRecord>& frecords() & noexcept;
    std::vector<SRecord>& srecords() & noexcept;
    std::vector<unique_type>& uniques()  & noexcept;

    std::vector<IRecord> irecords() && noexcept;
    std::vector<HRecord> hrecords() && noexcept;
    std::vector<FRecord> frecords() && noexcept;
    std::vector<SRecord> srecords() && noexcept;
    std::vector<unique_type> uniques()  && noexcept;

    const std::vector<IRecord>& irecords() const & noexcept;
    const std::vector<HRecord>& hrecords() const & noexcept;
    const std::vector<FRecord>& frecords() const & noexcept;
    const std::vector<SRecord>& srecords() const & noexcept;
    const std::vector<unique_type>& uniques()  const & noexcept;

    void add_record(IRecord&&);
    void add_record(HRecord&&);
    void add_record(FRecord&&);
    void add_record(SRecord&&);
    void add_unique(unique_type&&);

    void set_count(const unique_type&) noexcept;

    const unique_type& get_count() const noexcept;

    void set_uniques(std::vector<unique_type>&&)
        noexcept(std::is_nothrow_move_assignable<
                     std::vector<unique_type>>::value);

    void set_uniques(const std::vector<unique_type>&)
        noexcept(std::is_nothrow_copy_assignable<
                     std::vector<unique_type>>::value);

    void set_records(std::vector<IRecord>&&)
        noexcept(std::is_nothrow_move_assignable<
                     std::vector<IRecord>>::value);

    void set_records(std::vector<HRecord>&&)
        noexcept(std::is_nothrow_move_assignable<
                     std::vector<HRecord>>::value);

    void set_records(std::vector<FRecord>&&)
        noexcept(std::is_nothrow_move_assignable<
                     std::vector<FRecord>>::value);

    void set_records(std::vector<SRecord>&&)
        noexcept(std::is_nothrow_move_assignable<
                     std::vector<SRecord>>::value);

private:
    unique_type count_{0};
    std::vector<IRecord> irecords_{};
    std::vector<HRecord> hrecords_{};
    std::vector<FRecord> frecords_{};
    std::vector<SRecord> srecords_{};
    std::vector<unique_type> uniques_{};
};

inline void Result::set_count(const unique_type& value) noexcept
{
    count_ = value;
}

inline const unique_type& Result::get_count() const noexcept
{
    return count_;
}

inline std::vector<IRecord>& Result::irecords() & noexcept
{
    return irecords_;
}

inline std::vector<HRecord>& Result::hrecords() & noexcept
{
    return hrecords_;
}

inline std::vector<FRecord>& Result::frecords() & noexcept
{
    return frecords_;
}

inline std::vector<SRecord>& Result::srecords() & noexcept
{
    return srecords_;
}

inline std::vector<unique_type>& Result::uniques() & noexcept
{
    return uniques_;
}

inline std::vector<IRecord> Result::irecords() && noexcept
{
    return std::move(irecords_);
}

inline std::vector<HRecord> Result::hrecords() && noexcept
{
    return std::move(hrecords_);
}

inline std::vector<FRecord> Result::frecords() && noexcept
{
    return std::move(frecords_);
}

inline std::vector<SRecord> Result::srecords() && noexcept
{
    return std::move(srecords_);
}

inline std::vector<unique_type> Result::uniques() && noexcept
{
    return std::move(uniques_);
}

inline const std::vector<unique_type>& Result::uniques() const & noexcept
{
    return uniques_;
}

inline const std::vector<IRecord>& Result::irecords() const & noexcept
{
    return irecords_;
}

inline const std::vector<HRecord>& Result::hrecords() const & noexcept
{
    return hrecords_;
}

inline const std::vector<FRecord>& Result::frecords() const & noexcept
{
    return frecords_;
}

inline const std::vector<SRecord>& Result::srecords() const & noexcept
{
    return srecords_;
}


}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_UCM_LIB_SWC_DB__RESULT_H_
