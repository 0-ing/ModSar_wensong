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


#include "ucm/mock/sequence.h"
#include "ucm/lib/swc/db/types.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {

class Predicate final
      : virtual protected ucm::mock::Sequence
{

public:

    explicit Predicate() = default;

    Predicate(Predicate     &&) = default;
    Predicate(Predicate const&) = default;

    Predicate& operator=(Predicate     &&) = default;
    Predicate& operator=(Predicate const&) = default;

    ~Predicate() = default;

    bool compare(const IRecord&) const {return pop<bool>();}
    bool compare(const HRecord&) const {return pop<bool>();}
    bool compare(const FRecord&) const {return pop<bool>();}

    void add_rule(const Relation&, types::Unique&&) { pop<void>();}
    void add_rule(const Relation&, types::Cookie&&) { pop<void>();}
    void add_rule(const Relation&, types::TStamp&&) { pop<void>();}
    void add_rule(const Relation&, types::AState&&) { pop<void>();}
    void add_rule(const Relation&, types::AError&&) { pop<void>();}
    void add_rule(const Relation&, types::SWName&&) { pop<void>();}
    void add_rule(const Relation&, types::FSRoot&&) { pop<void>();}
    void add_rule(const Relation&, types::FSType&&) { pop<void>();}
    void add_rule(const Relation&, types::SWDeps&&) { pop<void>();}
    void add_rule(const Relation&, types::Version&&) { pop<void>();}

    const auto& get_unique() const noexcept;
    const auto& get_cookie() const noexcept;
    const auto& get_tstamp() const noexcept;
    const auto& get_astate() const noexcept;
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
    std::pair<Relation, types::AError>     aerror_{};
    std::pair<Relation, types::SWName>     swname_{};
    std::pair<Relation, types::FSRoot>     fsroot_{};
    std::pair<Relation, types::FSType>     fstype_{};
    std::pair<Relation, types::SWDeps>     swdeps_{};
    std::pair<Relation, types::Version>    version_{};
};

inline const auto& Predicate::get_unique() const noexcept
{
    return pop<std::pair<Relation, types::Unique> const&>();
}

inline const auto& Predicate::get_cookie() const noexcept
{
    return pop<std::pair<Relation, types::Cookie> const&>();
}

inline const auto& Predicate::get_tstamp() const noexcept
{
    return pop<std::pair<Relation, types::TStamp> const&>();
}

inline const auto& Predicate::get_astate() const noexcept
{
    return pop<std::pair<Relation, types::AState> const&>();
}

inline const auto& Predicate::get_aerror() const noexcept
{
    return pop<std::pair<Relation, types::AError> const&>();
}

inline const auto& Predicate::get_swname() const noexcept
{
    return pop<std::pair<Relation, types::SWName> const&>();
}

inline const auto& Predicate::get_fsroot() const noexcept
{
    return pop<std::pair<Relation, types::FSRoot> const&>();
}

inline const auto& Predicate::get_fstype() const noexcept
{
    return pop<std::pair<Relation, types::FSType> const&>();
}

inline const auto& Predicate::get_swdeps() const noexcept
{
    return pop<std::pair<Relation, types::SWDeps> const&>();
}

inline const auto& Predicate::get_version() const noexcept
{
    return pop<std::pair<Relation, types::Version> const&>();
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
