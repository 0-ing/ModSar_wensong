//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021-2022 by DENSO CORPORATION. All rights reserved.
//
// This file is property of DENSO CORPORATION. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/**
 * \file
 */

#ifndef SOMEIP_PAYLOAD_H
#define SOMEIP_PAYLOAD_H

#include <ara/core/vector.h>
#include <cstdint>

namespace ara
{
namespace com
{
namespace someip
{
class payload
{
public:
    payload();
    virtual ~payload();
    void set_payload(ara::core::Vector<uint8_t>* data)
    {
        m_payload = data;
    }
    ara::core::Vector<uint8_t>* get_payload()
    {
        return m_payload;
    }

private:
    ara::core::Vector<uint8_t>* m_payload;
};

} // namespace someip
} // namespace com
} // namespace ara

#endif
