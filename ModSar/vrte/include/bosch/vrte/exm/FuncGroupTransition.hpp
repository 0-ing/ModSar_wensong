//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
/// @file      FuncGroupTransition.hpp
/// @brief     Declaration/Definition of FuncGroupTransition
/// @author    baetz
//=============================================================================
#ifndef _FUNCGROUPTRANSITION_HPP_INCLUDED
#define _FUNCGROUPTRANSITION_HPP_INCLUDED

namespace bosch
{
namespace vrte
{
namespace exm
{
/// @brief Helper class to handle pair of (FuncGroup, FuncGroupState) strings.
/// @warning Strings are not copied, but only referenced, so they need to remain valid.
class FuncGroupTransition
{
public:
    /// @brief Empty ctor for default initialization.
    FuncGroupTransition() :
            funcGroupName(nullptr), funcGroupStateName(nullptr)
    {
    }

    /// @brief Initializing ctor passing pointers to fgName and fgStateName.
    /// @param[in] funcGroupName_       Null-terminated C string identifying a function group.
    /// @param[in] funcGroupStateName_  Null-terminated C string identifying a function group state.
    FuncGroupTransition(const char* funcGroupName_,
            const char* funcGroupStateName_) :
            funcGroupName(funcGroupName_), funcGroupStateName(
                    funcGroupStateName_)
    {
    }
    const char* funcGroupName;      ///< Null-terminated C string identifying a function group.
    const char* funcGroupStateName; ///< Null-terminated C string identifying a function group state.
};

} //namespace exm
} //namespace vrte
} //namespace bosch

#endif // _FUNCGROUPTRANSITION_HPP_INCLUDED
