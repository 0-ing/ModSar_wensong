//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/libtar/wrapper.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       hbe1lud
/// @version
/// @remarks

#ifndef UCM_AAP_PROCESSING_LIBTAR_WRAPPER_H_
#define UCM_AAP_PROCESSING_LIBTAR_WRAPPER_H_

#include <string>
#include <vector>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif


/// @addtogroup bosch_vrte_ucm_lib_ipc
/// @{
namespace bosch  {
namespace vrte   {
namespace ucm    {
namespace libtar {

class Wrapper final
{
public:
    struct Item
    {   /// File path 
        std::string path;       
        /// File size
        std::size_t size;
    };
    using List = std::vector<Item>;
    
    /// @brief Process tar archive and extract the path and size of the files in archive
    /// @param[in] tarfile Name of the tar archive 
    /// @return List containing path and size of the files in archive
    static List list(std::string tarfile);
    
    /// @brief Extract glob to root and close tarfile
    /// @param[in] tarfile Name of the tar archive 
    /// @param[in] glob  Input glob for processing 
    /// @param[out] root Output variable containing the root
    /// @return Void
    static void extract_glob(std::string tarfile, std::string root,
                                                  std::string glob);
};

}    // namespace libtar
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}
#endif // UCM_AAP_PROCESSING_LIBTAR_WRAPPER_H_
