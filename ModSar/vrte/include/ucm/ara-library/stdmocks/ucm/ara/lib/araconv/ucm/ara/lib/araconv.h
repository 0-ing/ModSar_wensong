//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// \file         ucm/ara/lib/araconv.h
/// \brief
/// \copyright    Robert Bosch GmbH 2021
/// \author       dsh8cob
/// \version
/// \remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_LIB_ARACONV_H_
#define UCM_AAP_PKGMANAGER_ARA_LIB_ARACONV_H_

#include "ucm/lib/types.h"
#include "ucm/ara/api/aracom_includes.h"

#include "ucm/mock/sequence.h"

namespace bosch  {
namespace vrte   {
namespace ucm    {
namespace ara    {
namespace lib    {

using ARATypes = bosch::vrte::ucm::lib::ara::ARATypes;
using Status = ARATypes::PackageManagerStatusType;

/// \brief AraConv provides methods to coovert internal types to ara defined types and vice-versa.

class Araconv : virtual protected ucm::mock::Sequence
{

public:
    /// Default constructor
    Araconv() = default;
    
    /// Copy Semantics
    Araconv(Araconv     &&) = delete;
	
    /// Copy Semantics
    Araconv(Araconv const&) = delete;

    /// Move Semantics
    Araconv& operator=(Araconv     &&) = delete;
	
    /// Move Semantics
    Araconv& operator=(Araconv const&) = delete;
    
    /// Default virtual destructor
    virtual ~Araconv() = default;

    /// \brief Convert array to native type.
    /// \param [IN] Transfer ID array
    /// \return Transfer Id of native type
    static ARATypes::TransferIdType arraytonll(TransferIdType)
    {
        return pop<ARATypes::TransferIdType>();
    }
    
    /// \brief Convert native type to array type.
    /// \param [IN] Transfer ID native type
    /// \return Transfer Id of array type
    static TransferIdType nlltoarray(ARATypes::TransferIdType)
    {
        return pop<TransferIdType>();
    }
    
    /// \brief Convert status from enum to string.
    /// \param [IN] status of type enum class PackageManagerStatusType : std::uint8_t
    /// \return Status in the form of string
    static const char* status_cstr(const Status&)
    {
        return pop<char const*>();
    }
};

}    // namespace lib
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_PKGMANAGER_ARA_LIB_ARACONV_H_
