//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/arc/factory.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       dsh8cob
/// @version
/// @remarks


#ifndef UCM_AAP_LIBRARY__UCM_LIB_ARC_FACTORY_H_
#define UCM_AAP_LIBRARY__UCM_LIB_ARC_FACTORY_H_

#include <memory>

#include "ucm/lib/arc/archive.h"
#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace arc   {

class Factory : virtual protected ucm::mock::Sequence
{
public:

    virtual ~Factory() = 0;

    virtual bool is_supported(std::string const&) noexcept
    {
        return pop<bool>();
    }

    virtual std::unique_ptr<Archive> archive(std::string const&)
    {
        return pop<std::unique_ptr<Archive>&&>();
    }

protected:

    explicit Factory() = default;

    Factory(      Factory&&) = default;
    Factory(const Factory &) = default;

    Factory& operator=(      Factory&&) = default;
    Factory& operator=(const Factory &) = default;

};

inline Factory::~Factory() = default;

}    // namespace arc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch


#endif // UCM_AAP_LIBRARY__UCM_LIB_ARC_FACTORY_H_
