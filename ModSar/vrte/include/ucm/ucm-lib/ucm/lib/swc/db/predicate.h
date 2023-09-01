//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/db/predicate.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_UCM_LIB_SWC_DB__PREDICATE_H_
#define UCM_AAP_LIBRARY_UCM_LIB_SWC_DB__PREDICATE_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/swc/db/types.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {

class Predicate final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_swc_db__Predicate, CTor);
    FRIEND_TEST(Test_ucm_lib_swc_db__Predicate, AddRule);
    FRIEND_TEST(Test_ucm_lib_swc_db__Predicate, Compare1);
    FRIEND_TEST(Test_ucm_lib_swc_db__Predicate, Compare2);
    FRIEND_TEST(Test_ucm_lib_swc_db__Predicate, IRecord);
    FRIEND_TEST(Test_ucm_lib_swc_db__Predicate, HRecord);
    FRIEND_TEST(Test_ucm_lib_swc_db__Predicate, FRecord);
    FRIEND_TEST(Test_ucm_lib_swc_db__Predicate, SRecord);
#endif
public:

    explicit Predicate() = default;

    Predicate(Predicate     &&) = default;
    Predicate(Predicate const&) = default;

    Predicate& operator=(Predicate     &&) = default;
    Predicate& operator=(Predicate const&) = default;

    ~Predicate() = default;

    bool compare(const IRecord&) const;
    bool compare(const HRecord&) const;
    bool compare(const FRecord&) const;
    bool compare(const SRecord&) const;

    void add_rule(const Relation&, types::Unique&&);
    void add_rule(const Relation&, types::Cookie&&);
    void add_rule(const Relation&, types::TStamp&&);
    void add_rule(const Relation&, types::AState&&);
    void add_rule(const Relation&, types::Action&&);
    void add_rule(const Relation&, types::AError&&);
    void add_rule(const Relation&, types::SWName&&);
    void add_rule(const Relation&, types::FSRoot&&);
    void add_rule(const Relation&, types::FSType&&);
    void add_rule(const Relation&, types::SWDeps&&);
    void add_rule(const Relation&, types::Version&&);

    const auto& get_unique() const noexcept;
    const auto& get_cookie() const noexcept;
    const auto& get_tstamp() const noexcept;
    const auto& get_astate() const noexcept;
    const auto& get_action() const noexcept;
    const auto& get_aerror() const noexcept;
    const auto& get_swname() const noexcept;
    const auto& get_fsroot() const noexcept;
    const auto& get_fstype() const noexcept;
    const auto& get_swdeps() const noexcept;
    const auto& get_version() const noexcept;

    const auto& get_unique_rel() const noexcept;
    const auto& get_cookie_rel() const noexcept;
    const auto& get_tstamp_rel() const noexcept;
    const auto& get_astate_rel() const noexcept;
    const auto& get_action_rel() const noexcept;
    const auto& get_aerror_rel() const noexcept;
    const auto& get_swname_rel() const noexcept;
    const auto& get_fsroot_rel() const noexcept;
    const auto& get_fstype_rel() const noexcept;
    const auto& get_swdeps_rel() const noexcept;
    const auto& get_version_rel() const noexcept;

    const auto& get_unique_value() const noexcept;
    const auto& get_cookie_value() const noexcept;
    const auto& get_tstamp_value() const noexcept;
    const auto& get_astate_value() const noexcept;
    const auto& get_action_value() const noexcept;
    const auto& get_aerror_value() const noexcept;
    const auto& get_swname_value() const noexcept;
    const auto& get_fsroot_value() const noexcept;
    const auto& get_fstype_value() const noexcept;
    const auto& get_swdeps_value() const noexcept;
    const auto& get_version_value() const noexcept;

    bool get_unique_valid() const noexcept;
    bool get_cookie_valid() const noexcept;
    bool get_tstamp_valid() const noexcept;
    bool get_astate_valid() const noexcept;
    bool get_action_valid() const noexcept;
    bool get_aerror_valid() const noexcept;
    bool get_swname_valid() const noexcept;
    bool get_fsroot_valid() const noexcept;
    bool get_fstype_valid() const noexcept;
    bool get_swdeps_valid() const noexcept;
    bool get_version_valid() const noexcept;

private:
    std::pair<Relation, types::Unique>     unique_{};
    std::pair<Relation, types::Cookie>     cookie_{};
    std::pair<Relation, types::TStamp>     tstamp_{};
    std::pair<Relation, types::AState>     astate_{};
    std::pair<Relation, types::Action>     action_{};
    std::pair<Relation, types::AError>     aerror_{};
    std::pair<Relation, types::SWName>     swname_{};
    std::pair<Relation, types::FSRoot>     fsroot_{};
    std::pair<Relation, types::FSType>     fstype_{};
    std::pair<Relation, types::SWDeps>     swdeps_{};
    std::pair<Relation, types::Version>    version_{};
};

inline const auto& Predicate::get_unique() const noexcept
{
    return unique_;
}

inline const auto& Predicate::get_cookie() const noexcept
{
    return cookie_;
}

inline const auto& Predicate::get_tstamp() const noexcept
{
    return tstamp_;
}

inline const auto& Predicate::get_astate() const noexcept
{
    return astate_;
}

inline const auto& Predicate::get_action() const noexcept
{
    return action_;
}

inline const auto& Predicate::get_aerror() const noexcept
{
    return aerror_;
}

inline const auto& Predicate::get_swname() const noexcept
{
    return swname_;
}

inline const auto& Predicate::get_fsroot() const noexcept
{
    return fsroot_;
}

inline const auto& Predicate::get_fstype() const noexcept
{
    return fstype_;
}

inline const auto& Predicate::get_swdeps() const noexcept
{
    return swdeps_;
}

inline const auto& Predicate::get_version() const noexcept
{
    return version_;
}

inline const auto& Predicate::get_unique_rel() const noexcept
{
    return std::get<0>(unique_);
}

inline const auto& Predicate::get_cookie_rel() const noexcept
{
    return std::get<0>(cookie_);
}

inline const auto& Predicate::get_tstamp_rel() const noexcept
{
    return std::get<0>(tstamp_);
}

inline const auto& Predicate::get_astate_rel() const noexcept
{
    return std::get<0>(astate_);
}

inline const auto& Predicate::get_action_rel() const noexcept
{
    return std::get<0>(action_);
}

inline const auto& Predicate::get_aerror_rel() const noexcept
{
    return std::get<0>(aerror_);
}

inline const auto& Predicate::get_swname_rel() const noexcept
{
    return std::get<0>(swname_);
}

inline const auto& Predicate::get_fsroot_rel() const noexcept
{
    return std::get<0>(fsroot_);
}

inline const auto& Predicate::get_fstype_rel() const noexcept
{
    return std::get<0>(fstype_);
}

inline const auto& Predicate::get_swdeps_rel() const noexcept
{
    return std::get<0>(swdeps_);
}

inline const auto& Predicate::get_version_rel() const noexcept
{
    return std::get<0>(version_);
}

inline const auto& Predicate::get_unique_value() const noexcept
{
    return std::get<1>(unique_).get_value();
}

inline const auto& Predicate::get_cookie_value() const noexcept
{
    return std::get<1>(cookie_).get_value();
}

inline const auto& Predicate::get_tstamp_value() const noexcept
{
    return std::get<1>(tstamp_).get_value();
}

inline const auto& Predicate::get_astate_value() const noexcept
{
    return std::get<1>(astate_).get_value();
}

inline const auto& Predicate::get_action_value() const noexcept
{
    return std::get<1>(action_).get_value();
}

inline const auto& Predicate::get_aerror_value() const noexcept
{
    return std::get<1>(aerror_).get_value();
}

inline const auto& Predicate::get_swname_value() const noexcept
{
    return std::get<1>(swname_).get_value();
}

inline const auto& Predicate::get_fsroot_value() const noexcept
{
    return std::get<1>(fsroot_).get_value();
}

inline const auto& Predicate::get_fstype_value() const noexcept
{
    return std::get<1>(fstype_).get_value();
}

inline const auto& Predicate::get_swdeps_value() const noexcept
{
    return std::get<1>(swdeps_).get_value();
}

inline const auto& Predicate::get_version_value() const noexcept
{
    return std::get<1>(version_).get_value();
}

inline bool Predicate::get_unique_valid() const noexcept
{
    return std::get<1>(unique_);
}

inline bool Predicate::get_cookie_valid() const noexcept
{
    return std::get<1>(cookie_);
}

inline bool Predicate::get_tstamp_valid() const noexcept
{
    return std::get<1>(tstamp_);
}

inline bool Predicate::get_astate_valid() const noexcept
{
    return std::get<1>(astate_);
}

inline bool Predicate::get_action_valid() const noexcept
{
    return std::get<1>(action_);
}

inline bool Predicate::get_aerror_valid() const noexcept
{
    return std::get<1>(aerror_);
}

inline bool Predicate::get_swname_valid() const noexcept
{
    return std::get<1>(swname_);
}

inline bool Predicate::get_fsroot_valid() const noexcept
{
    return std::get<1>(fsroot_);
}

inline bool Predicate::get_fstype_valid() const noexcept
{
    return std::get<1>(fstype_);
}

inline bool Predicate::get_swdeps_valid() const noexcept
{
    return std::get<1>(swdeps_);
}

inline bool Predicate::get_version_valid() const noexcept
{
    return std::get<1>(version_);
}

}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_UCM_LIB_SWC_DB__PREDICATE_H_
