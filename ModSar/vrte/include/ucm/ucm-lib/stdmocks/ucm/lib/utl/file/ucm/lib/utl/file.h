//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/utl/file.h
/// @brief
/// @copyright    Robert Bosch GmbH 2018
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UTL_FILE_H_
#define UCM_AAP_LIBRARY_LIB_UTL_FILE_H_

#include <string>
#include <cstdint>
#include <system_error>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace utl {


class File
      : virtual protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_File, Constructor1);
    FRIEND_TEST(Test_File, Constructor2);
    FRIEND_TEST(Test_File, SetFileName);
    FRIEND_TEST(Test_File, Rename);
    FRIEND_TEST(Test_File, Filename);
    FRIEND_TEST(Test_File, Suffix);

    FRIEND_TEST(Test_Loopdev, FileName);
    FRIEND_TEST(Test_Loopdev, FileSize1);
    FRIEND_TEST(Test_Loopdev, FileSize2);
#endif

public:
    static std::string suffix(const std::string&) { return pop<std::string>();}

    static bool exists(const char*) noexcept(true) { return pop<bool>();}
    static bool exists(const std::string&) noexcept(true) { return pop<bool>();}

    static bool compare(int, int, off_t)  { return pop<bool>();}
    static bool compare(const char*, const char*)  { return pop<bool>();}
    static bool compare(const std::string&, const std::string&)  { return pop<bool>();}

    // copy semantics
    File(const File&) = delete;
    File& operator=(const File&) = delete;

    // move semantic
    File(File&&) noexcept(true) = default;
    File& operator=(File&&) noexcept(true) = default;

    /// @brief Create an object of type @ref File, possibly creating the
    /// underlying file
    ///
    /// @param name Fully qualified file name (i.e. full path expected)
    /// @param autodel Whether to delete the underlying file automatically
    /// @throw May throw std::system_error exception
    ///
    /// @note
    /// If the underlying file does not exists, it is created when:
    /// 1. Its name is not empty
    /// 2. It does not exists
    /// 3. All path components of the file exist
    ///
    explicit File(const std::string& name, bool autodel = true) noexcept(false)
             :File(name.c_str(),autodel)
    {}

    /// @brief Create an object of type @ref File, possibly creating the
    /// underlying file
    ///
    /// @param name Fully qualified file name (i.e. full path expected)
    /// @param autodel Whether to delete the underlying file automatically
    /// @throw May throw std::system_error exception
    ///
    /// @note
    /// If the underlying file does not exists, it is created when:
    /// 1. Its name is not empty
    /// 2. It does not exists
    /// 3. All path components of the file exist
    ///
    explicit File(const char* name, bool autodel = true) noexcept(false)
             : autodel_(autodel)
             , filename_{name}
    {}

    /// @brief Create an initially empty object of type @ref File
    ///
    /// @param type The type of the file, so it has meaning in UCM context
    /// @param autodel Whether to delete the underlying file automatically
    ///
    /// @note
    /// If the underlying file does not exists, it is created when:
    /// 1. Its name is not empty
    /// 2. It does not exists
    /// 3. All path components of the file exist
    ///
    explicit File(bool autodel = true) noexcept(true)
             : autodel_(autodel)
             , filename_{}
    {}

    /// @brief Destroy and object of type @ref File
    ///
    /// @note
    /// If the autodel flag is set to @b true and the underlying file exists
    /// it is removed from the file system
    ///
    virtual ~File() {};

    inline const std::string& filename() const noexcept(true){return pop<std::string const&>();}

    ///
    /// @brief Set new filename unconditionally. std::rename file if exists
    ///
    /// @param newname The name to set
    ///
    /// @throw std::system_error if std::rename fails
    ///
    void filename(const char*) { pop<void>();}

    ///
    /// @brief Set new filename unconditionally. std::rename file if exists
    ///
    /// @param newname The name to set
    ///
    /// @throw std::system_error if std::rename fails
    ///
    void filename(const std::string&) { pop<void>();}

    /// @brief Try to remove the underlying file from the file system
    void remove() const noexcept(true) { pop<void>();}

    /// @brief Rename the @b oldname to @ref filename_
    ///
    /// @param oldname A fully qualified name of an existing file
    /// @throw May throw std::system_error exception
    ///
    void rename(const std::string& ) noexcept(false) { pop<void>();}

    /// @brief Rename the @b oldname to @ref filename_
    ///
    /// @param oldname A fully qualified name of an existing file
    /// @throw May throw std::system_error exception
    ///
    void rename(const char*) noexcept(false) { pop<void>();}

protected:
    /// @brief set the name of @ref File object
    ///
    /// @param newname The fully qualified file name to be set
    /// @throw May throw std::logic_error of the name is already set
    /// @throw May throw std::logic_error of the newname is empty
    /// @throw May throw std::logic_error of the newname is not full path
    void set_filename(const std::string&) noexcept(false) { pop<void>();}

    /// @brief set the name of @ref File object
    ///
    /// @param newname The fully qualified file name to be set
    /// @throw May throw std::logic_error if the name is already set
    /// @throw May throw std::logic_error if the new name is @b nullptr
    void set_filename(const char*) noexcept(false) { pop<void>();}

protected:
    bool autodel_;
    std::string filename_;

private:
    /// @brief Check if a filename is acceptable
    ///
    /// @param name The file name to be checked
    /// @throws std::logic_error if name is not OK
    static void check_filename(const char*) noexcept(false) { pop<void>();}

    /// @brief Try to create/open and close the file if it does not exists
    ///
    /// @throws std::system_error if file access fails
    void create_filename() noexcept(false) { pop<void>();}
};


}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_UTL_FILE_H_
