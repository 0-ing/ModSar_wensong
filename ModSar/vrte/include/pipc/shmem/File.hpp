#ifndef PIPC_SHMEM_FILE_HPP
#define PIPC_SHMEM_FILE_HPP

#include "pipc/utils/ErrorHandler.hpp"
#include "pipc/utils/String.hpp"

#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

namespace pipc
{
namespace shmem
{
/**
 * @brief A generic file object in shmem.
 *
 * The file object acts as a posix wrapper for calls to open(), close() etc.
 *
 * @todo
 * Check out whether we can let the class Mapping own a File instead of doing
 * file-related operations manually.
 */
class File
{
    using ErrorType    = utils::ErrorType;
    using ErrorHandler = utils::ErrorHandler;

public:
    /** @brief The default constructor. */
    File() : path_(), size_(), fd_(-1)
    {
    }

    /** @brief The destructor. */
    ~File()
    {
        if (fd_ != -1)
        {
            close();
            unlink();
        }
    }

    /** @brief Get the underlying file descriptor. */
    int getFd()
    {
        return fd_;
    }

    /** @brief Get the file size. */
    size_t getSize()
    {
        return size_;
    }

    /**
     * @brief Create a new file.
     *
     * @return true if the creation was successful, false otherwise
     */
    bool create(const utils::String& path, mode_t mode, size_t size, bool exclusive = false)
    {
        path_        = path;
        size_        = size;
        bool success = false;
        int flags    = O_CREAT | O_RDWR;
        if (exclusive)
        {
            flags |= O_EXCL;
        }

        fd_ = open(path_.c_str(), flags, mode);
        if (fd_ >= 0)
        {
            auto ret = ftruncate(fd_, size_);
            if (ret == 0)
            {
                success = true;
            }
            else
            {
                ErrorHandler::Error(ErrorType::kPosix, "ftruncate in File::create");
            }
        }
        else
        {
            ErrorHandler::Error(ErrorType::kPosix, "open in File::create");
        }
        return success;
    }

    /** @brief Close the file. */
    void close()
    {
        static_cast<void>(::close(fd_));
    }

    /** @brief Unlink the file. */
    void unlink()
    {
        static_cast<void>(::unlink(path_.c_str()));
    }

    /** @brief Get the file path. */
    utils::String getPath() const
    {
        return path_;
    }

private:
    /** @brief The path of the file. */
    utils::String path_;
    /** @brief The size of the file. */
    size_t size_;
    /** @brief The file descriptor associated with the file. */
    int fd_;
    /** @brief Flag to check whether the file was created (=true) or just opened (=false). */
    bool created_;
};

} // namespace shmem
} // namespace pipc

#endif // PIPC_SHMEM_FILE_HPP
