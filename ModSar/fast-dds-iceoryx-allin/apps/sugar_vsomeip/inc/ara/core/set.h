//==============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// The reproduction, distribution and utilization of this file as
// well as the communication of its contents to others without express
// authorization is prohibited. Offenders will be held liable for the
// payment of damages. All rights reserved in the event of the grant
// of a patent, utility model or design.
//==============================================================================

/// @file set.h
/// @brief Interface to class ara::core::Set
//==========================================================================

#ifndef ARA_CORE_SET_H_
#define ARA_CORE_SET_H_

#include <functional>
#include <set>
#include <memory>
#include <type_traits>

namespace ara {
namespace core {

template <class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key>>
using Set = std::set<Key, Compare, Allocator>;

}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_SET_H_
