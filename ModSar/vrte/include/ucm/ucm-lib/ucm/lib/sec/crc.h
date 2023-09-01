//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         src/ucm/lib/sec/crc.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_SEC__CRC_H_
#define UCM_AAP_LIBRARY__UCM_LIB_SEC__CRC_H_

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#define UCM_CRC32_ITU_T_V42_SEED 0xFFFFFFFF


/// @brief Initialise the CRC calculations.
__attribute__((warn_unused_result, always_inline, optimize(3)))
inline uint32_t ucm_crc32_itu_t_v42_table_init(void)
{
    return UCM_CRC32_ITU_T_V42_SEED;
}

/// @brief Finish CRC updates and get the final result.
__attribute__((warn_unused_result, always_inline, optimize(3)))
inline uint32_t ucm_crc32_itu_t_v42_table_fini(uint32_t crc)
{
    return ~crc;
}

/// @brief Update the CRC checksum.
__attribute__((warn_unused_result, nonnull(2), optimize(3)))
uint32_t ucm_crc32_itu_t_v42_table_update(
        uint32_t crc, const void* data, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif // UCM_AAP_LIBRARY__UCM_LIB_SEC__CRC_H_
