#ifndef PIPC_SHMEM_MAPPED_PTR_HPP
#define PIPC_SHMEM_MAPPED_PTR_HPP

#include "Mapping.hpp"
#include "pipc/utils/ErrorHandler.hpp"

namespace pipc
{
namespace shmem
{
/**
 * @brief A pointer with a memory mapping.
 *
 * The object of type T can be accessed through a memory mapping
 * with a given file name. This class acts as a smart pointer for it.
 */
template<typename T>
class MappedPtr
{
public:
    /** @brief Default constructor. */
    MappedPtr() = default;

    /** @brief Constructor with a given path name. */
    MappedPtr(const utils::StringView& name)
    {
        init(name);
    }

    /** @brief Initialize the mapped file with a given path name. */
    void init(const utils::StringView& name)
    {
        mapping_.setName(name);
    }

    /** @brief Create the mapped file and construct the object. */
    template<typename... Args>
    void create(mode_t mode = 0777, Args&&... args)
    {
        auto err = mapping_.create(mode, sizeof(T));
        if (err)
        {
            utils::ErrorHandler::CriticalError(utils::ErrorType::kGeneral, "Could not create the mapped file!");
        }
        new (mapping_.get()) T(std::forward<Args>(args)...);
    }

    /** @brief Create the mapped file with a manual size parameter and construct the object. */
    template<typename... Args>
    void create(mode_t mode, size_t size, Args&&... args)
    {
        auto err = mapping_.create(mode, size);
        if (err)
        {
            utils::ErrorHandler::CriticalError(utils::ErrorType::kGeneral,
                                               "Could not create the mapped file with size!");
        }
        new (mapping_.get()) T(std::forward<Args>(args)...);
    }

    /** @brief Open the mapped file, size can manually be overriden if required. */
    void open(size_t size = sizeof(T))
    {
        auto err = mapping_.open(size);
        if (err)
        {
            utils::ErrorHandler::CriticalError(utils::ErrorType::kGeneral, "Could not open the mapped file!");
        }
    }

    /** @brief Get operator. */
    inline T* get() const noexcept
    {
        return reinterpret_cast<T*>(mapping_.get());
    }

    /** @brief Dereference operations. */
    inline T& operator*() const noexcept
    {
        return *get();
    }
    inline T* operator->() const noexcept
    {
        return get();
    }

private:
    /** @brief The memory mapping. */
    Mapping mapping_;
};

} // namespace shmem
} // namespace pipc

#endif // PIPC_SHMEM_MAPPED_PTR_HPP
