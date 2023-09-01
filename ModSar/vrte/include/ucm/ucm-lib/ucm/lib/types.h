//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/types.h
/// @brief
/// @copyright    Robert Bosch GmbH 2019
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_TYPES_H_
#define UCM_AAP_LIBRARY_LIB_TYPES_H_

#include <sys/types.h>

#include <chrono>
#include <limits>
#include <cstdint>
#include <cstddef>
#include <type_traits>

#include "ucm/lib/ara/ara_types.h"

namespace bosch {
namespace vrte  {
namespace ucm   {

using id_type =
        std::conditional<
            std::numeric_limits<
                lib::ara::ARATypes::TransferIdType>::is_integer,
            lib::ara::ARATypes::TransferIdType, std::uint_fast64_t>::type;

using asize_type = std::int_fast64_t;
using ssize_type = std::make_signed_t<asize_type>;
using usize_type = std::make_unsigned_t<asize_type>;

using ara_data_type     = lib::ara::ARATypes::ByteVectorType;
using ara_error_type    = lib::ara::ARATypes::ApplicationErrorsType;
using ara_cluster_state = lib::ara::ARATypes::SwClusterStateType;
using ara_package_state = lib::ara::ARATypes::SwPackageStateType;

using timestamp_clock = std::chrono::high_resolution_clock;
using timestamp_type  = timestamp_clock::time_point;

constexpr id_type    id_type_max    = std::numeric_limits<id_type>::max();
constexpr asize_type asize_type_max = std::numeric_limits<asize_type>::max();
constexpr asize_type asize_type_min = std::numeric_limits<asize_type>::min();
constexpr ssize_type ssize_type_max = std::numeric_limits<ssize_type>::max();
constexpr ssize_type ssize_type_min = std::numeric_limits<ssize_type>::min();
constexpr ssize_type usize_type_max = std::numeric_limits<usize_type>::max();
constexpr ssize_type usize_type_min = std::numeric_limits<usize_type>::min();

void runtime_types_check();

const char* ara_error_string(const ara_error_type&);


}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_TYPES_H_
