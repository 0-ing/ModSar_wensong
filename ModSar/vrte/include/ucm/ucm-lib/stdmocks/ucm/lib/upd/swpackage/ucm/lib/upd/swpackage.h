//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/upd/swpackage.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       dsh8cob
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UPD_SWPACKAGE_H_
#define UCM_AAP_LIBRARY_LIB_UPD_SWPACKAGE_H_

#include "ucm/lib/pkg/mnf/model/manifest.h"
#include "ucm/error.h"
#include "ucm/mock/sequence.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace upd   {

class SWPackage : virtual protected ucm::mock::Sequence
{

public:

    SWPackage(const std::string&, const std::string&)
    {}

    SWPackage(SWPackage     &&) = delete;
    SWPackage(SWPackage const&) = delete;

    SWPackage& operator=(SWPackage     &&) = delete;
    SWPackage& operator=(SWPackage const&) = delete;

    virtual ~SWPackage() = 0;

    virtual Error swp_verify() noexcept { return pop<Error>(); }

    virtual Error swp_extract() noexcept { return pop<Error>(); }

    const std::string& manifest() const noexcept
    {
        return pop<std::string const&>();
    }

    const std::string& artefact(size_t) const noexcept
    {
        return pop<std::string const&>();
    }

protected:
    std::string              outpath_{};
    std::string              swpfile_{};
    std::string              manifest_ { };
    std::vector<std::string> artefacts_{};

    void sort_artefacts() {}

};

inline SWPackage::~SWPackage() = default;


}    // namespace upd
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UPD_SWPACKAGE_H_
