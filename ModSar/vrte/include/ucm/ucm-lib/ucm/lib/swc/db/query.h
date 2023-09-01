//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/db/query.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_UCM_LIB_SWC_DB__QUERY_H_
#define UCM_AAP_LIBRARY_UCM_LIB_SWC_DB__QUERY_H_

#include <bitset>
#include <functional>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/swc/error.h"
#include "ucm/lib/swc/db/result.h"
#include "ucm/lib/swc/db/predicate.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {


class Query final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_swc_db__Query, CTor);
    FRIEND_TEST(Test_ucm_lib_swc_db__Query, SetRecord);
    FRIEND_TEST(Test_ucm_lib_swc_db__Query, AddRuleset);
    FRIEND_TEST(Test_ucm_lib_swc_db__Query, Accsessors);
    FRIEND_TEST(Test_ucm_lib_swc_db__Query, CountVector);
    FRIEND_TEST(Test_ucm_lib_swc_db__Query, FilterObject);
    FRIEND_TEST(Test_ucm_lib_swc_db__Query, FilterVector1);
    FRIEND_TEST(Test_ucm_lib_swc_db__Query, FilterVector2);
#endif
public:
    enum class Type : unsigned
    {
        kCount, kSelect, kUpdate, kInsert, kRemove
    };

    explicit Query(const Type&)
        noexcept(std::is_nothrow_copy_assignable<Type>::value &&
                 std::is_nothrow_constructible<Result>::value &&
                 std::is_nothrow_constructible<
                     std::vector<std::vector<Predicate>>>::value);

    explicit Query(const Type&, Result&&)
        noexcept(std::is_nothrow_copy_assignable<Type>::value   &&
                 std::is_nothrow_move_assignable<Result>::value &&
                 std::is_nothrow_constructible<
                     std::vector<std::vector<Predicate>>>::value);

    Query(Query     &&) = default;
    Query(Query const&) = delete;

    Query& operator=(Query     &&) = default;
    Query& operator=(Query const&) = delete;

    ~Query() = default;

    template<class R,
        std::enable_if_t<
            std::is_same<R, IRecord>::value ||
            std::is_same<R, HRecord>::value ||
            std::is_same<R, SRecord>::value ||
            std::is_same<R, FRecord>::value, bool> = true
    >
    bool filter(const R& rec) const
    {
        bool retval = rulesets_.size() > 0 ? false : true;

        for (auto&& rset : rulesets()) {
            for (auto&& rule : rset) {
                retval = rule.compare(rec);
                if (not retval)
                    break;
            }
            if (retval)
                break;
        }

        return retval;
    }

    template<class R,
        std::enable_if_t<
            std::is_same<R, IRecord>::value ||
            std::is_same<R, HRecord>::value ||
            std::is_same<R, SRecord>::value ||
            std::is_same<R, FRecord>::value, bool> = true
    >
    std::vector<R> filter(const std::vector<R>& db) const
    {
        std::vector<R> retval;

        for (auto&& rec : db) {
            if (filter(rec))
                retval.push_back(rec);
        }

        return retval;
    }

    template<class R,
        std::enable_if_t<
            std::is_same<R, IRecord>::value ||
            std::is_same<R, HRecord>::value ||
            std::is_same<R, SRecord>::value ||
            std::is_same<R, FRecord>::value, bool> = true
    >
    std::vector<R> filter(std::vector<R>&& db) const
    {
        std::vector<R> retval;

        for (auto&& rec : db) {
            if (filter(rec))
                retval.push_back(std::move(rec));
        }

        return retval;
    }

    template<class R,
        std::enable_if_t<
            std::is_same<R, IRecord>::value ||
            std::is_same<R, HRecord>::value ||
            std::is_same<R, SRecord>::value ||
            std::is_same<R, FRecord>::value, bool> = true
    >
    unique_type count(const std::vector<R>& db) const
    {
        unique_type counter = 0;

        for (auto&& rec : db) {
            if (filter(rec))
                counter++;
        }

        return counter;
    }


    void add_ruleset(std::vector<Predicate>&&);
    void set_uniques(std::vector<unique_type>&&);

    void q_irecord(bool) noexcept;
    void q_hrecord(bool) noexcept;
    void q_frecord(bool) noexcept;
    void q_srecord(bool) noexcept;

    bool q_irecord() const noexcept;
    bool q_hrecord() const noexcept;
    bool q_frecord() const noexcept;
    bool q_srecord() const noexcept;

    const std::vector<std::vector<Predicate>>& rulesets() const noexcept;

    Type&                 type()     & noexcept;
    std::vector<IRecord>& irecords() & noexcept;
    std::vector<HRecord>& hrecords() & noexcept;
    std::vector<FRecord>& frecords() & noexcept;
    std::vector<SRecord>& srecords() & noexcept;
    std::vector<unique_type>& uniques() & noexcept;

    Type                  type()     && noexcept;
    std::vector<IRecord>  irecords() && noexcept;
    std::vector<HRecord>  hrecords() && noexcept;
    std::vector<FRecord>  frecords() && noexcept;
    std::vector<SRecord>  srecords() && noexcept;
    std::vector<unique_type>  uniques() && noexcept;

    const Type&                 type()     const & noexcept;
    const std::vector<IRecord>& irecords() const & noexcept;
    const std::vector<HRecord>& hrecords() const & noexcept;
    const std::vector<FRecord>& frecords() const & noexcept;
    const std::vector<SRecord>& srecords() const & noexcept;
    const std::vector<unique_type>& uniques() const & noexcept;

private:
    Type type_{};
    Result result_{};
    bool q_irecord_{false};
    bool q_hrecord_{false};
    bool q_frecord_{false};
    bool q_srecord_{false};
    std::vector<std::vector<Predicate>> rulesets_{};
};

inline void Query::q_irecord(bool flag) noexcept
{
    q_irecord_ = flag;
}

inline void Query::q_hrecord(bool flag) noexcept
{
    q_hrecord_ = flag;
}

inline void Query::q_frecord(bool flag) noexcept
{
    q_frecord_ = flag;
}

inline void Query::q_srecord(bool flag) noexcept
{
    q_srecord_ = flag;
}

inline bool Query::q_irecord() const noexcept
{
    return q_irecord_;
}

inline bool Query::q_hrecord() const noexcept
{
    return q_hrecord_;
}

inline bool Query::q_frecord() const noexcept
{
    return q_frecord_;
}

inline bool Query::q_srecord() const noexcept
{
    return q_srecord_;
}

inline const std::vector<std::vector<Predicate>>& Query::rulesets() const noexcept
{
    return rulesets_;
}

inline Query::Type& Query::type() & noexcept
{
    return type_;
}

inline std::vector<IRecord>& Query::irecords() & noexcept
{
    return result_.irecords();
}

inline std::vector<HRecord>& Query::hrecords() & noexcept
{
    return result_.hrecords();
}

inline std::vector<FRecord>& Query::frecords() & noexcept
{
    return result_.frecords();
}

inline std::vector<SRecord>& Query::srecords() & noexcept
{
    return result_.srecords();
}

inline std::vector<unique_type>& Query::uniques() & noexcept
{
    return result_.uniques();
}

inline Query::Type Query::type() && noexcept
{
    return std::move(type_);
}

inline std::vector<IRecord> Query::irecords() && noexcept
{
    return std::move(std::move(result_).irecords());
}

inline std::vector<HRecord> Query::hrecords() && noexcept
{
    return std::move(std::move(result_).hrecords());
}

inline std::vector<FRecord> Query::frecords() && noexcept
{
    return std::move(std::move(result_).frecords());
}

inline std::vector<SRecord> Query::srecords() && noexcept
{
    return std::move(std::move(result_).srecords());
}

inline std::vector<unique_type> Query::uniques() && noexcept
{
    return std::move(std::move(result_).uniques());
}

inline const Query::Type& Query::type() const & noexcept
{
    return type_;
}

inline const std::vector<unique_type>& Query::uniques() const & noexcept
{
    return result_.uniques();
}

inline const std::vector<IRecord>& Query::irecords() const & noexcept
{
    return result_.irecords();
}

inline const std::vector<HRecord>& Query::hrecords() const & noexcept
{
    return result_.hrecords();
}

inline const std::vector<FRecord>& Query::frecords() const & noexcept
{
    return result_.frecords();
}

inline const std::vector<SRecord>& Query::srecords() const & noexcept
{
    return result_.srecords();
}

}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_UCM_LIB_SWC_DB__QUERY_H_
