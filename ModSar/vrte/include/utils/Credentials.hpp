//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2019 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
/// @file      Credentials.hpp
/// @brief     Declaration/Definition of Credentials
/// @author
//=============================================================================
#ifndef UTILS_CREDENTIALS_HPP_INCLUDED
#define UTILS_CREDENTIALS_HPP_INCLUDED

#include "utils/PrimaryConfig.hpp"
#include "utils/Try.hpp"
#include "utils/Types.hpp"
#include "utils/vector.hpp"
#include <unistd.h>

namespace exm
{
namespace utils
{
/// @brief public class which holds the credentials (UID, GID and supplementary groups) of a Process
class Credentials
{
public:
    typedef utils::vector<gid_t, MAX_SUPPLEMENTARY_GROUPS> Groups;

    /// @brief Constructor
    Credentials()
        : uid(0), gid(0), groups() {}

    /// @brief Destructor
    ~Credentials() {}

    /// @brief No copy constructor needed.
    Credentials(const Credentials&) = delete;

    /// @brief Copy assignment operator
    Credentials& operator=(const Credentials& other)
    {
        if (this != &other)
        {
            this->uid = other.uid;
            this->gid = other.gid;
            this->groups = other.groups;
        }

        return *this;
    }

    /// @brief Function to get the GID
    /// @return GID
    gid_t getGid() const { return gid; }

    /// @brief Function to get the UID
    /// @return UID
    uid_t getUid() const { return uid; }

    /// @brief Function to get the number of supplementary groups
    /// @return number of supplementary groups
    uint32_t getNgroups() const { return groups.size(); }

    /// @brief Function to get the vector of gids
    /// @return vector of gids
    Groups& getGlist()
    {
        return groups;
    }

    /// @brief Function to set the UID and GID (without using supplementary groups)
    /// @param uid_ UID
    /// @param gid_ GID
    void setCredentials(uid_t uid_, gid_t gid_)
    {
        uid = uid_;
        gid = gid_;
    }

    /// @brief Function to push the suppl group id provided to the existing vector of gids
    /// @param suppl_gid gid of suppl group
    /// @return StdReturnType::OK
    StdReturnType push_suppl_group(const gid_t suppl_gid)
    {
        return groups.try_push_back(suppl_gid);
    }

    /// @brief Function to all of the credentials
    /// @param uid_ UID
    /// @param gid_ GID
    /// @param ngroups_ number of supplementary groups
    /// @param[in] glist_ list of supplementary groups
    /// @return StdReturnType::GENERAL_ERROR if the provided array ptr is null, else StdReturnType::OK
    StdReturnType setCredentials(uid_t uid_, gid_t gid_, Integer ngroups_, const gid_t glist_[])
    {
        uid = uid_;
        gid = gid_;
        if (nullptr == glist_)
        {
            return StdReturnType::GENERAL_ERROR;
        }
        for (Integer i = 0; i < ngroups_; ++i)
        {
            TRY_MSG(push_suppl_group(glist_[i]), "Failed to push supplementary group");
        }
        return StdReturnType::OK;
    }

private:
    uid_t uid; ///< @brief UID
    gid_t gid; ///< @brief GID
    Groups groups;
};
} // namespace utils
} // namespace exm

#endif // UTILS_CREDENTIALS_HPP_INCLUDED