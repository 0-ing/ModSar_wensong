//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/db/types.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_TYPES_H_
#define UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_TYPES_H_

#include <chrono>
#include <utility>
#include <type_traits>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/types.h"
#include "ucm/lib/utl/value_pair.h"

#include "ucm/lib/swc/types.h"
#include "ucm/lib/swc/version.h"
#include "ucm/lib/swc/deprule.h"
#include "ucm/lib/swc/irecord.h"
#include "ucm/lib/swc/hrecord.h"
#include "ucm/lib/swc/srecord.h"
#include "ucm/lib/swc/frecord.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {
namespace types {

namespace def {

struct Unique   { using type = unique_type; };
struct Cookie   { using type = unique_type; };
struct TStamp   { using type = tstamp_type; };

struct SWName
{
    using type = std::remove_cv<
            std::remove_reference<
                decltype(std::declval<DepUnit>().swname())>::type>::type;
};

struct FSRoot
{
    using type =  std::remove_cv<
            std::remove_reference<
                decltype(std::declval<FRecord>().fsroot())>::type>::type;
};

struct FSList
{
    using type = std::remove_cv<
            std::remove_reference<
                decltype(std::declval<FRecord>().fslist())>::type>::type;
};

struct FSType
{
    using type = std::remove_cv<
            std::remove_reference<
                decltype(std::declval<FRecord>().type())>::type>::type;
};

struct AState
{
    using type = std::remove_cv<
            std::remove_reference<
                decltype(std::declval<SRecord>().astate())>::type>::type;
};

struct Action
{
    using type = std::remove_cv<
            std::remove_reference<
                decltype(std::declval<HRecord>().action())>::type>::type;
};

struct AError
{
    using type = std::remove_cv<
            std::remove_reference<
                decltype(std::declval<HRecord>().aerror())>::type>::type;
};

struct Version
{
    using type = std::remove_cv<
            std::remove_reference<
                decltype(std::declval<DepUnit>().version())>::type>::type;
};

struct SWDeps
{
    using type = std::remove_cv<
            std::remove_reference<
                decltype(std::declval<IRecord>().deprules())>::type>::type;
};


}   // namespace def

using Unique    = utl::ValuePair<def::Unique,    def::Unique::type>;
using Cookie    = utl::ValuePair<def::Cookie,    def::Cookie::type>;
using TStamp    = utl::ValuePair<def::TStamp,    def::TStamp::type>;
using AState    = utl::ValuePair<def::AState,    def::AState::type>;
using Action    = utl::ValuePair<def::Action,    def::Action::type>;
using AError    = utl::ValuePair<def::AError,    def::AError::type>;
using SWName    = utl::ValuePair<def::SWName,    def::SWName::type>;
using FSRoot    = utl::ValuePair<def::FSRoot,    def::FSRoot::type>;
using SWDeps    = utl::ValuePair<def::SWDeps,    def::SWDeps::type>;
using FSList    = utl::ValuePair<def::FSList,    def::FSList::type>;
using FSType    = utl::ValuePair<def::FSType,    def::FSType::type>;
using Version   = utl::ValuePair<def::Version,   def::Version::type>;

}   // namespace types

}   // namespace db
}   // namespace swc
}   // namespace lib
}   // namespace ucm
}   // namespace vrte
}   // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_TYPES_H_
