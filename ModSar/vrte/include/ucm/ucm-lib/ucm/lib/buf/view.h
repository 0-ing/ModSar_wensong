//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/buf/view.h
/// @brief        Buffer view API.
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup bosch_vrte_ucm_lib_buf

#ifndef UCM_AAP_LIBRARY__UCM_LIB_BUF__VIEW_H_
#define UCM_AAP_LIBRARY__UCM_LIB_BUF__VIEW_H_

#if defined(GOOGLE_TEST)
#include <gtest/gtest_prod.h>
#endif

#include "ucm/lib/buf/error.h"
#include "ucm/lib/buf/types.h"
#include "ucm/lib/utl/file_io.h"


/// @addtogroup bosch_vrte_ucm_lib_buf
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace buf   {

/// @class View view.h ucm/lib/buf/view.h
/// @ingroup bosch_vrte_ucm_lib_buf
/// @brief Buffer view class.
///
/// The class defines a set of operations on a contiguous region of memory
/// possibly part of a UCM memory buffer. This level of abstraction is required
/// since UCM memory buffers are not necessarily contiguous - i.e. they can be
/// a set of disjoint memory chunks.
/// The operations defined by the class include:
/// - file to memory
/// - memory to file
/// - memory to memory
///
/// The memory managed by the buffer view should not be manipulated directly
/// (i.e. via a pointer), but for safety reasons always via the public API
/// provided by the class.
///
class View
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_buf__View, CTor1);
    FRIEND_TEST(Test__ucm_lib_buf__View, CTor2);
    FRIEND_TEST(Test__ucm_lib_buf__View, Copy1);
    FRIEND_TEST(Test__ucm_lib_buf__View, Save1);
    FRIEND_TEST(Test__ucm_lib_buf__View, Save2);
    FRIEND_TEST(Test__ucm_lib_buf__View, Save3);
    FRIEND_TEST(Test__ucm_lib_buf__View, Load1);
    FRIEND_TEST(Test__ucm_lib_buf__View, Fill1);
    FRIEND_TEST(Test__ucm_lib_buf__View, MapMem);
    FRIEND_TEST(Test__ucm_lib_buf__View, MapCur);
    FRIEND_TEST(Test__ucm_lib_buf__View, Write1);
    FRIEND_TEST(Test__ucm_lib_buf__View, Write2);
    FRIEND_TEST(Test__ucm_lib_buf__View, Write3);
#endif

    /// @brief The size of the maximum I/O block.
    ///
    constexpr static std::size_t iochunk = 4096;

protected:
    /// @brief Construct a View for a memory region.
    ///
    /// @param[in] arena The start of the controlled memory region.
    /// @param[in] msize Size of the controlled memory region.
    /// @param[in] csize Current size of the data in the memory region.
    ///
    explicit View(std::size_t msize, std::size_t csize) noexcept;

    /// @brief Construct a buffer View with invalid memory region.
    ///
    /// @note all unreferenced member variables are set to 0.
    ///
    View() noexcept = default;

    View(View     &&) = default;
    View(View const&) = default;

    View& operator=(View     &&) = default;
    View& operator=(View const&) = default;

public:
    virtual ~View() = default;

    /// @brief Clear the memory contents setting it to 0.
    ///
    void clear() noexcept;

    /// @brief Reset the buffer view setting cursize_ = 0.
    ///
    void reset() noexcept;

    /// @brief Evaluate the View in boolean context.
    ///
    /// @returns true , if memory_ != nullptr
    /// @returns false, if memory_ == nullptr
    ///
    explicit operator bool() const noexcept;

    /// @brief Return the memory size of the controlled region.
    ///
    std::size_t memsize() const noexcept;

    /// @brief Return the current data size of the controlled region.
    ///
    std::size_t cursize() const noexcept;

    /// @brief Return the free space in the controlled region.
    ///
    std::size_t freespc() const noexcept;

    /// @brief Return a pointer of type T at the specified offset.
    ///
    /// @param[in] offset Offset from the start of the controlled region.
    /// @return Pointer to object of type T, if boundary check allows.
    /// @return nullptr, if boundary check shows there is possible overflow.
    ///
    /// Return a pointer of type T at the specified offset, performing a
    /// boundary check. If the object of type T will exceed the boundaries
    /// of the controlled region at the given offset nullptr is returned.
    ///
    /// @warning Use under caution - access past mregion() possible.
    ///
    template<typename T,
        std::enable_if_t<std::is_pointer<T>::value, bool> = true>
    T mapmem(const memory_offset& offset) noexcept
    {
        if (not this->operator bool())
            return nullptr;
        auto size = sizeof(typename std::remove_pointer<T>::type);
        if (size + offset > memsize_)
            return nullptr;
        else
            return static_cast<T>(data(offset()));
    }

    /// @brief Return a pointer of type T at the specified offset.
    ///
    /// @param[in] offset Offset from the start of the controlled region.
    /// @return Pointer to object of type T, if boundary check allows.
    /// @return nullptr, if boundary check shows there is possible overflow.
    ///
    /// Return a pointer of type T at the specified offset, performing a
    /// boundary check. If the object of type T will exceed the boundaries
    /// of the controlled region at the given offset nullptr is returned.
    ///
    /// @warning Use under caution - access past mregion() possible.
    ///
    template<typename T,
        std::enable_if_t<std::is_pointer<T>::value, bool> = true>
    const T mapmem(const memory_offset& offset) const noexcept
    {
        if (not this->operator bool())
            return nullptr;
        auto size = sizeof(typename std::remove_pointer<T>::type);
        if (size + offset > memsize_)
            return nullptr;
        else
            return static_cast<T>(data(offset()));
    }

    /// @brief Return a pointer to the mregion() member variable.
    ///
    /// @warning Use under caution - access past mregion() possible.
    ///
    const void *mapmem() const noexcept;

    /// @brief Return a pointer to the mregion() member variable.
    ///
    /// @warning Use under caution - access past mregion() possible.
    ///
    const void *mapmem(const memory_offset&) const noexcept;

    /// @brief Return a pointer of type T at the specified offset.
    ///
    /// @param[in] offset Offset from the start of the controlled region.
    /// @return const pointer to object of type T, if boundary check allows.
    /// @return nullptr, if boundary check shows there is possible overflow.
    ///
    /// Return a pointer of type T at the specified offset, performing a
    /// boundary check. If the given size will exceed the boundaries
    /// of the controlled region at the given offset nullptr is returned.
    /// If the pointer mapping is successful the cursize_ variable will be
    /// increased with the size of the type T.
    ///
    template<typename T,
        std::enable_if_t<std::is_pointer<T>::value, bool> = true>
    T mapcur(std::size_t size, const memory_offset& offset) noexcept
    {
        if (not this->operator bool())
            return nullptr;
        size_t osize = size + offset;
        if (osize > memsize_)
            return nullptr;
        if (cursize_ < osize)
            cursize_ = osize;
        return static_cast<T>(data(offset()));
    }

    /// @brief Return a pointer of type T at the specified offset.
    ///
    /// @param[in] offset Offset from the start of the controlled region.
    /// @return const pointer to object of type T, if boundary check allows.
    /// @return nullptr, if boundary check shows there is possible overflow.
    ///
    /// Return a pointer of type T at the specified offset, performing a
    /// boundary check. If the object of type T will exceed the boundaries
    /// of the controlled region at the given offset nullptr is returned.
    /// If the pointer mapping is successful the cursize_ variable will be
    /// increased with the size of the type T.
    ///
    template<typename T,
        std::enable_if_t<std::is_pointer<T>::value, bool> = true>
    T mapcur(const memory_offset& offset) noexcept
    {
        return mapcur<T>(sizeof(typename std::remove_pointer<T>::type), offset);
    }

    /// @brief Write at most min(size, cursize()) bytes to dst.
    ///
    /// @param[in] dst Destination for the copy operation.
    /// @param[in] size Size to be copied to from the view.
    /// @returns The number of bytes actually written to the destiation.
    ///
    std::size_t copy(void* dst, std::size_t size) noexcept;

    /// @brief Write at most min(size, cursize()) bytes to dst.
    ///
    /// @param[in] dst Destination for the copy operation.
    /// @param[in] size Size to be copied to from the view.
    /// @param[in] offset The offset within the destination memory.
    /// @returns The number of bytes actually written to the destiation.
    ///
    std::size_t copy(void* dst, std::size_t size,
                     const memory_offset& offset) noexcept;

    /// @brief Write at most maxsize_ - cursize_ bytes to memory_.
    ///
    /// After the write is performed, cursize_ is updated with the number of
    /// bytes written.
    ///
    /// @param[in] src Source for the copy operation.
    /// @param[in] size Size to be copied to to buffer.
    /// @returns The number of bytes actually written to the memory.
    ///
    /// @warning src must not overlap with the controlled memory region!
    ///
    std::size_t write(const void* src, std::size_t size) noexcept;

    /// @brief Write at most maxsize_ - cursize_ bytes to memory_.
    ///
    /// After the write is performed, cursize_ is updated with the number of
    /// bytes written, excess to the cursize_
    /// (i.e. cursize_ = offset + size)
    ///
    /// @param[in] src Source for the copy operation.
    /// @param[in] size Size to be copied to to buffer.
    /// @param[in] offset The offset within the destination memory.
    /// @returns The number of bytes actually written to the memory.
    ///
    std::size_t write(const void* src,
                      std::size_t size,
                      const memory_offset& offset) noexcept;


    /// @brief Write cur_size_ bytes to a file.
    ///
    /// @param[in] fio The file object for the write operation.
    /// @returns Error(ErrorValue::kSuccess) if write is successful.
    /// @returns Error(some_error_code) if write fails.
    ///
    Error save(utl::FileIO& fio) noexcept;

    /// @brief Write cur_size_ bytes to a file at offset offt
    ///
    /// @param[in] fio The file object for the write operation.
    /// @returns Error(ErrorValue::kSuccess) if write is successful.
    /// @returns Error(some_error_code) if write fails.
    ///
    Error save(utl::FileIO& fio, const iofile_offset& offset) noexcept;

    /// @brief Save cur_size_ bytes to a file.
    ///
    /// @param[in] fio The file object for the write operation.
    /// @param[in] offset Offset within the memory buffer.
    /// @returns Error(ErrorValue::kSuccess) if write is successful.
    /// @returns Error(some_error_code) if write fails.
    ///
    Error save(utl::FileIO& fio, const memory_offset& offset) noexcept;

    /// @brief Save cursize_ - moffset bytes to a file.
    ///
    /// @param[in] fio The file object for the write operation.
    /// @param[in] moffset Offset within the memory buffer.
    /// @param[in] foffset Offset of the file descriptor.
    /// @returns Error(ErrorValue::kSuccess) if write is successful.
    /// @returns Error(some_error_code) if write fails.
    ///
    Error save(utl::FileIO& fio,
               const memory_offset& moffset,
               const iofile_offset& foffset) noexcept;

    /// @brief Save cur_size_ bytes to a file.
    ///
    /// @param[in] fio The file object for the write operation.
    /// @param[in] size Size of the data to be written to.
    /// @param[in] moffset Offset within the memory buffer.
    /// @param[in] foffset Offset of the file descriptor.
    /// @returns Error(ErrorValue::kSuccess) if write is successful.
    /// @returns Error(some_error_code) if write fails.
    ///
    Error save(utl::FileIO& fio,
               std::size_t size,
               const memory_offset& moffset,
               const iofile_offset& foffset) noexcept;

    /// @brief Load at most maxsize_ - cursize_ bytes from a file.
    ///
    /// @param[in] fio The file object for the read operation.
    /// @returns Error(ErrorValue::kSuccess) if read is successful.
    /// @returns Error(some_error_code) if file read fails.
    ///
    Error load(utl::FileIO& fio) noexcept;

    /// @brief Load at most size bytes from a file.
    ///
    /// @param[in] fio The file object for the read operation.
    /// @param[in] size Bytes to load from the source file.
    /// @returns Error(ErrorValue::kSuccess) if read is successful.
    /// @returns Error(some_error_code) if file read fails.
    ///
    Error load(utl::FileIO& fio, std::size_t size) noexcept;

    /// @brief Load at most size bytes from a file at file offset offt.
    ///
    /// @param[in] fio The file object for the read operation.
    /// @param[in] size Bytes to load from the source file.
    /// @param[in] moffset Offset within the memory buffer.
    /// @param[in] foffset Offset of the file descriptor.
    /// @returns Error(ErrorValue::kSuccess) if read is successful.
    /// @returns Error(some_error_code) if file read fails.
    ///
    Error load(utl::FileIO& fio,
               std::size_t size, const iofile_offset& foffset) noexcept;

    /// @brief Load exactly maxsize_ - cursize_ bytes from file into buffer.
    ///
    /// @param[in] fio The file object for the read operation.
    /// @returns Error(ErrorValue::kSuccess) if read is successful.
    /// @returns Error(ErrorValue::kOverflow) if size > free space.
    /// @returns Error(ErrorValue::kUnderflow) if bytes read < size.
    /// @returns Error(some_error_code) if file read fails.
    ///
    Error fill(utl::FileIO& fio) noexcept;

    /// @brief Load exactly size bytes from file into buffer.
    ///
    /// @param[in] fio The file object for the read operation.
    /// @param[in] size The number of bytes to be loaded into buffer.
    /// @returns Error(ErrorValue::kSuccess) if read is successful.
    /// @returns Error(ErrorValue::kOverflow) if size > free space.
    /// @returns Error(ErrorValue::kUnderflow) if bytes read < size.
    /// @returns Error(some_error_code) if file read fails.
    ///
    Error fill(utl::FileIO& fio, std::size_t size) noexcept;

    /// @brief Load exactly size bytes from file into buffer.
    ///
    /// @param[in] fio The file object for the read operation.
    /// @param[in] size The number of bytes to be loaded into buffer.
    /// @param[in] offset The offset in the source file.
    /// @returns Error(ErrorValue::kSuccess) if read is successful.
    /// @returns Error(ErrorValue::kOverflow) if size > free space.
    /// @returns Error(ErrorValue::kUnderflow) if bytes read < size.
    /// @returns Error(some_error_code) if file read fails.
    ///
    Error fill(utl::FileIO& fio,
               std::size_t size, const iofile_offset& offset) noexcept;

protected:

    /// @brief Return a pointer to the mregion() member variable in const
    ///
    /// @warning Use under caution - access past mregion() possible.
    ///
    virtual const void* mregion() const & noexcept = 0;
    virtual void* mregion() & noexcept = 0;

private:
    std::size_t  memsize_{0};
    std::size_t  cursize_{0};


    bool valid() const noexcept;

    /// @brief Return a pointer to the controlled region.
    ///
    void* data() noexcept;

    /// @brief Return a pointer to the controlled region.
    ///
    const void* data() const noexcept;

    /// @brief Return a pointer to the controlled region at offset.
    ///
    std::uint8_t* data8(std::size_t offset = 0) noexcept;

    /// @brief Return a pointer to the controlled region.
    ///
    const std::uint8_t* data8(std::size_t offset = 0) const noexcept;

    /// @brief Return a pointer to the controlled region.
    ///
    void* data(std::size_t offset) noexcept;

    /// @brief Return a pointer to the controlled region.
    ///
    const void* data(std::size_t offset) const noexcept;
};

inline void View::reset() noexcept
{
    cursize_ = 0;
}

inline View::operator bool() const noexcept
{
    return mregion() and memsize_;
}

inline std::size_t View::memsize() const noexcept
{
    return memsize_;
}

inline std::size_t View::cursize() const noexcept
{
    return cursize_;
}

inline std::size_t View::freespc() const noexcept
{
    return memsize_ - cursize_;
}

inline void* View::data() noexcept
{
    return mregion();
}

inline const void* View::data() const noexcept
{
    return mregion();
}

inline std::uint8_t* View::data8(std::size_t offset) noexcept
{
    return static_cast<std::uint8_t*>(data()) + offset;
}

inline const std::uint8_t* View::data8(std::size_t offset) const noexcept
{
    return static_cast<const std::uint8_t*>(data()) + offset;
}

inline void* View::data(std::size_t offset) noexcept
{
    return static_cast<void*>(data8(offset));
}

inline const void* View::data(std::size_t offset) const noexcept
{
    return static_cast<const void*>(data8(offset));
}

inline const void *View::mapmem() const noexcept
{
    return mapmem<const std::uint8_t*>(0);
}

inline const void *View::mapmem(const memory_offset& offset) const noexcept
{
    return mapmem<const std::uint8_t*>(offset);
}

}    // namespace buf
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_LIB_BUF__VIEW_H_
