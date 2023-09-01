// --------------------------------------------------------------------------
// |              _    _ _______     .----.      _____         _____        |
// |         /\  | |  | |__   __|  .  ____ .    / ____|  /\   |  __ \       |
// |        /  \ | |  | |  | |    .  / __ \ .  | (___   /  \  | |__) |      |
// |       / /\ \| |  | |  | |   .  / / / / v   \___ \ / /\ \ |  _  /       |
// |      / /__\ \ |__| |  | |   . / /_/ /  .   ____) / /__\ \| | \ \       |
// |     /________\____/   |_|   ^ \____/  .   |_____/________\_|  \_\      |
// |                              . _ _  .                                  |
// --------------------------------------------------------------------------
//
// All Rights Reserved.
// Any use of this source code is subject to a license agreement with the
// AUTOSAR development cooperation.
// More information is available at www.autosar.org.
//
// Disclaimer
//
// This work (specification and/or software implementation) and the material
// contained in it, as released by AUTOSAR, is for the purpose of information
// only. AUTOSAR and the companies that have contributed to it shall not be
// liable for any use of the work.
//
// The material contained in this work is protected by copyright and other
// types of intellectual property rights. The commercial exploitation of the
// material contained in this work requires a license to such intellectual
// property rights.
//
// This work may be utilized or reproduced without any modification, in any
// form or by any means, for informational purposes only. For any other
// purpose, no part of the work may be utilized or reproduced, in any form
// or by any means, without permission in writing from the publisher.
//
// The work has been developed for automotive applications only. It has
// neither been developed, nor tested for non-automotive applications.
//
// The word AUTOSAR and the AUTOSAR logo are registered trademarks.
// --------------------------------------------------------------------------
#ifndef ARA_DIAG_REENTRANCY_H_INCLUDED
#define ARA_DIAG_REENTRANCY_H_INCLUDED

#include <cstdint>
namespace ara {

namespace diag {

/**
 * @brief Specifies the reentrancy types
 *
 * @traceid{SWS_DM_00935}@tracestatus{draft}
 * @uptrace{RS_Diag_04166}
 */
enum class ReentrancyType : std::uint8_t
{
   kFully = 0x00,         ///< The code is fully reentrant
   kNot   = 0x01          ///< Not reentrant code
};

/**
 * @brief Specifies the reentrancy type of a DataIdentifier related port
 *
 * @traceid{SWS_DM_00936}@tracestatus{draft}
 * @uptrace{RS_Diag_04166}
 */
struct DataIdentifierReentrancyType
{
   /**
    * @brief Reentrancy type for Reads
    *
    * @traceid{SWS_DM_00937}@tracestatus{draft}
    * @uptrace{RS_Diag_04166}
    */
   ReentrancyType read;

   /**
    * @brief Reentrancy type for Writes
    *
    * @traceid{SWS_DM_00938}@tracestatus{draft}
    * @uptrace{RS_Diag_04166}
    */
   ReentrancyType write;

   /**
    * @brief Reentrancy type for Reads and Writes
    *
    * @traceid{SWS_DM_00939}@tracestatus{draft}
    * @uptrace{RS_Diag_04166}
    */
   ReentrancyType readWrite;
};

}     //namespace diag

} //namespace ara

#endif //ARA_DIAG_REENTRANCY_H_INCLUDED
