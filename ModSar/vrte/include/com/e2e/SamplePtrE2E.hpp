//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      SamplePtrE2E.hpp
/// @brief     Class for Sample Pointers
/// @copyright Robert Bosch GmbH 2021
/// @author    mtk2abt
//=============================================================================

#ifndef SAMPLE_PTR_E2E_HPP
#define SAMPLE_PTR_E2E_HPP

#include "ara/com/types.h"

namespace com
{
namespace e2e
{
/**
 * @brief SamplePtr class that is used in the someip serialize event receiver.
 * The purpose of this class is to hide the setting of Profile Check Status
 * from applications.
 * !!! Adding members to this class should be avoided as it could introduce
 * errors when moving objects. Members should be added to base class !!!
 */
template<typename SampleType>
class SamplePtrE2E : public ara::com::SamplePtr<SampleType>
{
public:
    using E2ECheckStatus = ara::com::e2e::ProfileCheckStatus;

    using ara::com::SamplePtr<SampleType>::SamplePtr; // Constructor Inheritance

    void SetProfileCheckStatus(E2ECheckStatus status)
    {
        this->checkStatus_ = status;
    }
};

} // namespace e2e
} // namespace com

#endif // SAMPLE_PTR_E2E_HPP
