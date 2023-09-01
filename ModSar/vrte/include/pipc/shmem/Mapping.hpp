#ifndef SHMEM_MAPPING_HPP
#define SHMEM_MAPPING_HPP

#include "pipc/utils/String.hpp"
#include "pipc/utils/StringView.hpp"

#include <fcntl.h> /* For O_* constants */
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <unistd.h>

namespace pipc
{
namespace shmem
{
/**
 * @brief Wrapper for a POSIX shared memory mapping.
 *
 * Creates or opens a mapping in the process' address space based on a file
 * name.
 *
 * @todo
 * Provide a clear definition for "name" and "path" and translations (which is portable).
 * For now we prepend everything with a slash coming into this class.
 */
class Mapping
{
public:
    Mapping() noexcept : name_(), size_(), addr_(nullptr), fd_(), created_()
    {
    }

    /** @brief Constructor for immediate creation. */
    Mapping(const utils::StringView& name, mode_t mode = 0777, size_t size = 4096) noexcept
        : name_("/" + name), size_(size), addr_(nullptr)
    {
        create(mode, size);
    }

    /** @brief No copy operations. */
    Mapping(const Mapping&) = delete;
    Mapping& operator=(const Mapping&) = delete;

    /** @brief Move constructor. */
    Mapping(Mapping&& other) noexcept
        : name_(other.name_), size_(other.size_), addr_(other.addr_), created_(other.created_)
    {
        other.addr_ = nullptr;
    }

    /** @brief Move assignment operator. */
    Mapping& operator=(Mapping&& other) noexcept
    {
        if (this != &other)
        {
            name_       = other.name_;
            size_       = other.size_;
            addr_       = other.addr_;
            created_    = other.created_;
            other.addr_ = nullptr;
        }
        return *this;
    }

    /** @brief Get the underlying file descriptor. */
    int getFd()
    {
        return fd_;
    }

    /** @brief Get the name of the mapping. */
    const utils::String& getName() const
    {
        return name_;
    }

    /** @brief Set the name of the mapping separately. */
    void setName(const utils::StringView& name)
    {
        name_ = "/" + name;
    }

    /** @brief Create a new mapping with resetting the name. */
    int create(const char* name, mode_t mode, size_t size)
    {
        name_ = "/";
        name_ += name;
        return create(mode, size);
    }

    /** @brief Create a new mapping without resetting the name. */
    int create(mode_t mode, size_t size)
    {
        close();
        size_    = size;
        created_ = true;

        fd_ = shm_open(name_.c_str(), O_CREAT | O_RDWR, mode);
        if (fd_ >= 0)
        {
            auto ret = ftruncate(fd_, size);
            if (ret != 0)
            {
                std::cout << "ftruncate errno: " << errno << std::endl;
                ::close(fd_);
                return errno;
            }
            addr_ = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0);
            if (addr_ == MAP_FAILED)
            {
                std::cout << "mmap errno: " << errno << std::endl;
                addr_ = nullptr;
                ::close(fd_);
                return errno;
            }
            return 0;
        }
        else
        {
            std::cout << "shm_open errno: " << errno << std::endl;
            return errno;
        }
    }

    /** @brief Open a new mapping with resetting the name. */
    int open(const char* name, size_t size)
    {
        name_ = "/";
        name_ += name;
        return open(size);
    }

    /** @brief Open the mapping without resetting the name. */
    int open(size_t size)
    {
        close();
        size_    = size;
        created_ = false;

        fd_ = shm_open(name_.c_str(), O_RDWR, 0);
        if (fd_ >= 0)
        {
            addr_ = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0);
            if (addr_ == MAP_FAILED)
            {
                std::cout << "mmap errno: " << errno << std::endl;
                addr_ = nullptr;
                ::close(fd_);
                return errno;
            }
            return 0;
        }
        else
        {
            std::cout << "Mapping::open shm_open errno: " << errno << std::endl;
            return errno;
        }
    }

    /** @brief Close the mapping. */
    void close()
    {
        if (addr_)
        {
            ::close(fd_);
            munmap(addr_, size_);
            if (created_)
            {
                if (shm_unlink(name_.c_str()) == -1)
                {
                    perror("Mapping: shm_unlink");
                }
            }
            addr_ = nullptr;
        }
    }

    /** @brief Get the mapped address. */
    inline void* get() const noexcept
    {
        return addr_;
    }

    ~Mapping()
    {
        close();
    }

private:
    /** @brief Name of the associated file. */
    utils::String name_;
    /** @brief Size in Bytes of the mapping. */
    size_t size_;
    /** @brief Start address of the mapping. */
    void* addr_;
    /** @brief The underlying file descriptor. */
    int fd_;
    /** @brief Flag to check whether the file was created (false=open, true=create). */
    bool created_;
};

} // namespace shmem
} // namespace pipc

#endif // SHMEM_MAPPING_HPP
