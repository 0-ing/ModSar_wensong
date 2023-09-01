//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/deprule.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__DEPRULE_H_
#define UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__DEPRULE_H_

#include "ucm/mock/sequence.h"
#include "ucm/lib/swc/types.h"
#include "ucm/lib/swc/depunit.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {

class DepRule
        : virtual protected ucm::mock::Sequence
{

public:

    static const char *relation_cstr(const Relation&) noexcept {return pop<const char*>();}

    explicit DepRule(const Relation& rule, DepUnit&& unit)
        noexcept(std::is_nothrow_move_constructible<DepUnit>::value)
    : rule_{rule}
    , unit_(std::move(unit))
    {
    }

    DepRule(DepRule     &&) = default;
    DepRule(DepRule const&) = default;

    DepRule& operator=(DepRule     &&) = default;
    DepRule& operator=(DepRule const&) = default;

    ~DepRule() = default;

    bool compare(const DepUnit&) const noexcept {return pop<bool>();}

    const auto& rule() const noexcept;
    const auto& unit() const noexcept;
    const auto& swname() const noexcept;
    const auto& version() const noexcept;

private:
    Relation rule_;
    DepUnit  unit_;

    bool vcompare(const DepUnit&) const noexcept {return pop<bool>();}
};

inline std::ostream& operator<<(std::ostream&, const DepRule&) {return ucm::mock::Sequence::pop<std::ostream&>();}

inline bool operator<(const DepRule& , const DepRule& ) {return ucm::mock::Sequence::pop<bool>();}
inline bool operator>(const DepRule& , const DepRule& ) {return ucm::mock::Sequence::pop<bool>();}
inline bool operator<=(const DepRule& , const DepRule& ) {return ucm::mock::Sequence::pop<bool>();}
inline bool operator>=(const DepRule& , const DepRule& ) {return ucm::mock::Sequence::pop<bool>();}
inline bool operator==(const DepRule& , const DepRule& ) {return ucm::mock::Sequence::pop<bool>();}
inline bool operator!=(const DepRule& , const DepRule& ) {return ucm::mock::Sequence::pop<bool>();}

inline const auto& DepRule::rule() const noexcept
{
    return pop<Relation const&>();
}

inline const auto& DepRule::unit() const noexcept
{
    return pop<DepUnit const&>();
}

inline const auto& DepRule::swname() const noexcept
{
    return pop<std::string const&>();
}

inline const auto& DepRule::version() const noexcept
{
    return pop<Version const&>();
}

}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__DEPRULE_H_

