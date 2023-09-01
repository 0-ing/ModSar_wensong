/// @copyright 2022 Robert Bosch GmbH. All rights reserved.

#ifndef FLATCFG_H
#define FLATCFG_H

#include <mutex>
#include "ara/core/string.h"
#include "ara/core/string_view.h"
#include "ara/core/vector.h"
#include "ara/core/result.h"
#include "ara/core/map.h"

#include "flatcfg/flatcfg_error.h"

namespace flatcfg
{

/////////////
/// @brief   FlatCfg provides access to the configuration data of an application
/// @details FlatCfg manages the access to the configuration of the using application (= where this lib is included)
///          FlatCfg ensures that the parts of configuration are only accessible by the application/libs that are
///          allowed to access it.
///          The configuration data itself is stored as Flatbuffers which have to be handled by the application/libs.
class FlatCfg
{
public:
    /// @brief     Constructor
    /// @details   Default constructor is not allowed as the FC-name is needed
    FlatCfg() = delete;

    /// @brief     Constructor
    /// @details   Constructor for the FlatCfg class
    /// @param[in] fcName Name of the FC for which the FlatCfg is created
    FlatCfg(ara::core::String fcName);

    /// @brief     Destructor
    virtual ~FlatCfg() = default;

    /// @brief     Copying of FlatCfg objects is not allowed
    FlatCfg(const FlatCfg& obj) = delete;
    FlatCfg& operator=(const FlatCfg&) = delete;

    /// @brief     Move semantics, deleted because we have a mutex as a member
    FlatCfg(FlatCfg&& obj) = delete;
    FlatCfg& operator=(FlatCfg&&) = delete;

    /// @brief     Returns the available SWClusters for the requested FC
    /// @details   getSwClusterList searches the configuration path for the application
    ///            and returns all SWClusters for the requested fc.
    /// @return    Names of the SWClusters that are available for the fc,
    ///            error if more than one process is configured in the configuration path.
    virtual ara::core::Result<ara::core::Vector<ara::core::String>> getSwClusterList(void) noexcept;

    /// @brief     Load
    /// @param[in] SwCluster to load
    /// @details   Allocate memory and load the config file for the requested SWCluster
    ///            Memory is allocated and client have to take care about releasing when not needed
    /// @return    Shared pointer to FlatBuffer, error when file can't be loaded
    virtual ara::core::Result<std::shared_ptr<void>> load(const ara::core::String& SwClusterName) noexcept;

private:
    /// Name of the function cluster
    ara::core::String m_functionClusterName;

    /// Shared map which holds metadata for all SW Clusters
    ara::core::Map<ara::core::String, ara::core::String> m_SwClusterPathMap;

    /// Mutex to protect map against concurrent access
    mutable std::mutex m_SwClusterPathMapLock;

    /// Name of the environment variable that holds the path to the configuration files
    // Type is a char* as it is only used with getenv which expects char*
    const char* envVar_configPath = "ECUCFG_ENV_VAR_ROOTFOLDER";

    /// Wildcard pattern to match the configuration filenames (FC will be preponed later)
    const ara::core::String configFilePattern = ara::core::String("*__*_flatcfg[.]bin");

    /// Regex to extract the process name
    const ara::core::String configFileRegexProcName        // fc will be added later!
        = ara::core::String("(_([a-z0-9](_?[a-z0-9])*))?") // optional process name
        + ara::core::String("__(.*)")                      // SwCluster
        + ara::core::String("_flatcfg\\.bin");             // Postfix

    /// @brief     Get the path to the configuration files
    /// @details   This function determines the path to the configuration files and checks if it exists.
    ///            The path is read from the ENV-variable defined in FlatCfg::envVar_configPath.
    /// @return    Path to the configuration files,
    ///            error if it cannot be determined or does not exist.
    ara::core::Result<ara::core::String> getConfigPath(void) const noexcept;

    /// @brief     Get a list of all config filenames for the requested fc that are stored in the configPath
    /// @details   This functions reads all config filenames for the requested fc that are stored in the given path.
    /// @note      As the used glob only has limited filtering power, there still may be false positives which have
    ///            to be filtered out (files with incorrect names that are nonetheless matched by the wildcard pattern)
    /// @param[in] configPath Path in which the config files are searched.
    /// @return    Names of the configuration files that are available for the fc,
    ///            error if searching fails.
    ara::core::Result<ara::core::Vector<ara::core::String>>
    getConfigFiles(const ara::core::String& configPath) const noexcept;

    /// @brief     Checks if all configurations in the list belong to one process and returns the SWCluster names
    /// @details   This function checks the given list of filenames as follows:
    ///            - Filenames are conform to the rules
    ///            - Only one process is configured with the given files
    ///            - SWCluster is not empty
    ///            If the checks are successful a list of all SWClusters that are configured in the list is returned.
    /// @param[in] fileList List of files to be checked.
    /// @return    List of SWClusters for which a configuration was found,
    ///            error if a check failed
    ara::core::Result<ara::core::Vector<ara::core::String>>
    checkFilesAndGetSwClusterList(const ara::core::Vector<ara::core::String>& fileList) noexcept;
};

} // namespace flatcfg

#endif /* FLATCFG_H */
