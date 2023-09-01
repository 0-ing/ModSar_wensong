#ifndef PIPC_UTILS_FILE_PERMISSION_CONTROL_HPP
#define PIPC_UTILS_FILE_PERMISSION_CONTROL_HPP

#include "Permission.hpp"
#include "String.hpp"
#include "Vector.hpp"

#include <cstdint>
#include <grp.h>
#include <iostream>
#include <pwd.h>
#include <sys/acl.h>

namespace pipc
{
namespace utils
{
/**
 * @brief Class used to control file permissions.
 */
class FilePermissionControl
{
public:
    /**
     * @brief Id used for Standard Categories (USER, GROUP, OTHERS).
     */
    static constexpr uint32_t StandardId = 0xFFFFFFFF;

    /**
     * @brief Construct a new File Permission Control object using a file descriptor.
     *
     * @param fileDescriptor File descriptor. The descriptor should be opened with Read/Write permissions.
     */
    FilePermissionControl(const int32_t fileDescriptor) : m_fileDescriptor(fileDescriptor)
    {
    }

    /**
     * @brief Construct a new File Permission Control object using a file path.
     *
     * @param filePath Path of the file. The file should have Read/Write permissions.
     */
    FilePermissionControl(const utils::String filePath) : m_filePath(filePath)
    {
    }

    /**
     * @brief Copy constructor
     *
     * @param other
     */
    FilePermissionControl(const FilePermissionControl& other)
    {
        if (&other != this)
        {
            m_fileDescriptor = other.m_fileDescriptor;
            m_filePath       = other.m_filePath;
            m_permissions    = other.m_permissions;
        }
    }

    /**
     * @brief Move constructor
     *
     * @param other
     */
    FilePermissionControl(FilePermissionControl&& other)
    {
        if (&other != this)
        {
            m_fileDescriptor       = other.m_fileDescriptor;
            m_filePath             = std::move(other.m_filePath);
            m_permissions          = std::move(other.m_permissions);
            other.m_fileDescriptor = -1;
        }
    }

    /**
     * @brief Add a new permission entry to the entry list.
     *
     * If the entry already exists, any new permissions will be appended.
     *
     * @param category @ref Category
     * @param permission @ref Permission
     * @param id uid of the SPECIFIC_USER or gid of the SPECIFIC_GROUP. In case of USER, GROUP, OTHERS the value
     * should be left as @ref StandardId
     * @param validateId Set to true if validation should be performed on the @ref id (in case of SPECIFIC_USER or
     * SPECIFIC_GROUP)
     * @return true If the permission entry was added to the entry list
     * @return false The permission entry was not added to the entry list
     */
    bool addPermissionEntry(const acl_tag_t tag,
                            const Permission permission,
                            const uint32_t id     = StandardId,
                            const bool validateId = false)
    {
        // Check if the tag and id is already present in the entry list
        for (auto& entry : m_permissions)
        {
            if ((entry.tag == tag) && (entry.id == id))
            {
                entry.permission |= permission;
                return true;
            }
        }

        if (tag == ACL_USER || tag == ACL_GROUP)
        {
            if (validateId)
            {
                if (id == StandardId)
                {
                    std::cout << "For specific user or group, id is required!" << std::endl;
                    return false;
                }
                if (tag == ACL_USER && getpwuid(id) == nullptr)
                {
                    std::cout << "Specific user does not exist in the system!" << std::endl;
                    return false;
                }
                if (tag == ACL_GROUP && getgrgid(id) == nullptr)
                {
                    std::cout << "Specific group does not exist in the system!" << std::endl;
                    return false;
                }
            }
        }
        m_permissions.push_back({tag, permission, id});
        return true;
    }

    /**
     * @brief Takes the permission entry list and adds it to the file.
     * Atleast the standard permissions(USER, GROUP, OTHERS)
     * must be added to the entry list, in order for this method to be successful.
     *
     * @return true if all permissions were added to the file.
     * @return false if error occured.
     */
    bool writePermissionsToFile()
    {
        int numberOfEntries = static_cast<int>(m_permissions.size() + 1U);
        acl_t acl           = acl_init(numberOfEntries);

        PermissionEntry entry{ACL_MASK, Permission::kRead | Permission::kWrite, StandardId};
        if (!addAclEntry(acl, entry))
        {
            acl_free(acl);
            return false;
        }

        for (const auto& entry : m_permissions)
        {
            if (!addAclEntry(acl, entry))
            {
                acl_free(acl);
                return false;
            }
        }

        bool permissionsSet = false;
        if (acl_valid(acl) == 0)
        {
            if (m_fileDescriptor != -1)
            {
                permissionsSet = (acl_set_fd(m_fileDescriptor, acl) == 0);
            }
            else
            {
                permissionsSet = (acl_set_file(m_filePath.c_str(), ACL_TYPE_ACCESS, acl) == 0);
            }

            if (!permissionsSet)
            {
                std::cout << "Failed to set permissions! Errno: " << errno << std::endl;
            }
        }
        else
        {
            std::cout << "ACL is not valid! Errno: " << errno << std::endl;
        }

        acl_free(acl);

        return permissionsSet;
    }

private:
    struct PermissionEntry
    {
        acl_tag_t tag;
        Permission permission;
        uint32_t id;
    };

    /** @brief Add a PermissionEntry to the ACL. */
    bool addAclEntry(acl_t acl, const PermissionEntry& permissionEntry)
    {
        acl_entry_t aclEntry;
        if (acl_create_entry(&acl, &aclEntry) == -1)
        {
            std::cout << "Could not create new entry! Errno: " << errno << std::endl;
            return false;
        }

        if (acl_set_tag_type(aclEntry, permissionEntry.tag) == -1)
        {
            std::cout << "Could not set tag! Errno: " << errno << std::endl;
            return false;
        }

        // Check if we also need to pass a uid_t or gid_t.
        // HINT: uid_t and gid_t are not guaranteed to be the same type on all platforms.
        if (permissionEntry.tag == ACL_USER)
        {
            uid_t id = static_cast<uid_t>(permissionEntry.id);
            if (acl_set_qualifier(aclEntry, &id) == -1)
            {
                std::cout << "Could not set qualifier! Errno: " << errno << std::endl;
                return false;
            }
        }
        else if (permissionEntry.tag == ACL_GROUP)
        {
            gid_t id = static_cast<gid_t>(permissionEntry.id);
            if (acl_set_qualifier(aclEntry, &id) == -1)
            {
                std::cout << "Could not set qualifier! Errno: " << errno << std::endl;
                return false;
            }
        }

        acl_permset_t permSet;
        if (acl_get_permset(aclEntry, &permSet) == -1)
        {
            std::cout << "Could not get permset! Errno: " << errno << std::endl;
            return false;
        }

        if ((permissionEntry.permission & Permission::kRead) == Permission::kRead)
        {
            if (!addAclPermission(permSet, ACL_READ))
            {
                return false;
            }
        }

        if ((permissionEntry.permission & Permission::kWrite) == Permission::kWrite)
        {
            if (!addAclPermission(permSet, ACL_WRITE))
            {
                return false;
            }
        }

        return true;
    }

    /** @brief Add a permission to a permission set. */
    bool addAclPermission(acl_permset_t permset, acl_perm_t perm)
    {
        if (acl_add_perm(permset, perm) == -1)
        {
            std::cout << "Could not set permision! Errno: " << errno << std::endl;
            return false;
        }
        return true;
    }

    /** @brief The file descriptor, if the object was constructed using a fd. */
    int32_t m_fileDescriptor{-1};
    /** @brief The file path, if the object was constructed using a string. */
    utils::String m_filePath;
    /** @brief List of all permissions. */
    utils::Vector<PermissionEntry> m_permissions;
};

} // namespace utils
} // namespace pipc

#endif // PIPC_UTILS_FILE_PERMISSION_CONTROL_HPP
