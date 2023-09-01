//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/buf/model.h
/// @brief        Base class for UCM flexible buffers.
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup bosch_vrte_ucm_lib_buf

#ifndef UCM_AAP_LIBRARY__UCM_LIB_BUF__MODEL_H_
#define UCM_AAP_LIBRARY__UCM_LIB_BUF__MODEL_H_

#include <cstdint>
#include <cstddef>

#if defined(GOOGLE_TEST)
#include <gtest/gtest_prod.h>
#endif

#include "ucm/lib/buf/view.h"
#include "ucm/lib/buf/error.h"
#include "ucm/lib/buf/iterator.h"


/// @addtogroup bosch_vrte_ucm_lib_buf
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace buf   {

/// @class Model model.h ucm/lib/buf/model.h
/// @ingroup bosch_vrte_ucm_lib_buf
/// @brief Base class for UCM flexible buffers.
///
/// The class defines the API which a flexible buffer should implement.
/// UCM flexible buffers assume that:
/// - The underlying memory is not contiguous, i.e. it is segmented.
/// - end_address(segment[N]) != start_address(segment[N+1])
/// - sizeof(segment[N]) != sizeof(segment[N+1]
/// - count_of(segments) >= 0.
/// - In case count_of(segments) == 0 - only end iterators are returned.
/// - Memory regions of any two segments may overlap.
/// - Any copy within a buffer MUST be done only with memmove
/// - Direct access to the underlying memory arena is not possible.
/// - Access is done via buf::View objects obtained via buf::Iterator objects.
/// - Any non-const method invalidates the obtained iterators and views.
/// - A memory address offset within a buffer has no meaning.
///
/// While the underlying memory segments are disjoint the
/// buf::View/buf::Iterator approach allows the buffer to be treated logically
/// as if its memory is contiguous - i.e. an offset has a meaning with the
/// assumption that
/// offsetof(end_address(segment[N])) == offsetof(start_address(segment[N+1])).
/// Still the access if done only via buf::View objects, and one can access
/// the M<sup>th</sup> byte by obtaining the buf::View containing it.
///
///
/// @warning Concurrent operations on a buffer are not supported, so any access
/// to an object with this base type must be synchronised if needed.
///
class Model
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_buf__Model, TEST__CTor);
    FRIEND_TEST(Test__ucm_lib_buf__Model, TEST__Copy1);
    FRIEND_TEST(Test__ucm_lib_buf__Model, TEST__Save1);
    FRIEND_TEST(Test__ucm_lib_buf__Model, TEST__Save2);
    FRIEND_TEST(Test__ucm_lib_buf__Model, TEST__Load1);
    FRIEND_TEST(Test__ucm_lib_buf__Model, TEST__Load2);
    FRIEND_TEST(Test__ucm_lib_buf__Model, TEST__Fill1);
    FRIEND_TEST(Test__ucm_lib_buf__Model, TEST__Fill2);
    FRIEND_TEST(Test__ucm_lib_buf__Model, TEST__Write1);
    FRIEND_TEST(Test__ucm_lib_buf__Model, TEST__Write2);
    FRIEND_TEST(Test__ucm_lib_buf__Model, TEST__MapView);
    FRIEND_TEST(Test__ucm_lib_buf__Model, TEST__VIterator);
    FRIEND_TEST(Test__ucm_lib_buf__Model, TEST__MapViewNC);
#endif

protected:
    /// @brief Construct the base flexible UCM buffer object.
    explicit Model() noexcept = default;

    Model(Model     &&) noexcept = default;
    Model(Model const&) noexcept = delete;

    Model& operator=(Model     &&) noexcept = default;
    Model& operator=(Model const&) noexcept = delete;

public:
    using value_type                = std::uint8_t;
    using iterator                  = Iterator;
    using const_iterator            = Iterator;

    virtual ~Model() = default;

    template<typename T,
        std::enable_if_t<std::is_pointer<T>::value, bool> = true>
    T mapviewnc(bool alloc, const memory_offset& offset)
    {
        auto vptr = view(offset);
        if (not vptr)
            throw std::runtime_error("BufferView invalid");
        if (alloc)
            return vptr->template mapcur<T>(offset);
        else
            return vptr->template mapmem<T>(offset);
    }

    template<typename T,
        std::enable_if_t<std::is_pointer<T>::value, bool> = true>
    T mapview(bool alloc, const memory_offset& offset)
    {
        auto vptr = mapviewnc<T>(alloc, offset);
        if (not vptr)
            throw std::runtime_error("Failed to map fields to the buffer");
        return vptr;
    }

    /// @brief Write no more than size bytes to the buffer.
    ///
    /// The operation is performed at the first available position in the
    /// buffer, i.e. at position cursize() < memsize() of a buf::View, obtained
    /// via buf::Iterator.
    ///
    /// @param[in] data Pointer to the source memory location.
    /// @param[in] size Size of the source memory location to write.
    /// @return The bytes actually written to the buffer.
    ///
    std::size_t write(const void* data, std::size_t size) noexcept;

    /// @brief Write no more than size bytes to the buffer at offset.
    ///
    /// The operation is performed at location offset in the buffer.
    /// If the last location written exceeds cursize() it is updated
    /// accordingly. The update must be performed internally by the concrete
    /// buffer implementing the model.
    ///
    /// @param[in] data Pointer to the source memory location.
    /// @param[in] size Size of the source memory location to write.
    /// @param[in] offset Memory offset within the buffer boundaries.
    /// @return The bytes actually written to the buffer.
    ///
    std::size_t write(const void* data,
                      std::size_t size, memory_offset offset) noexcept;

    /// @brief Write cur_size_ bytes to a file.
    Error save(utl::FileIO& fio) noexcept;

    /// @brief Write size bytes to a file.
    Error save(utl::FileIO& fio, memory_offset offt) noexcept;

    /// @brief Write size bytes to a file.
    Error save(utl::FileIO& fio, iofile_offset offt) noexcept;

    /// @brief Write size bytes to a file.
    Error save(utl::FileIO& fio,
               memory_offset moffset,
               iofile_offset foffset) noexcept;

    /// @brief Load up to max_size_ - cur_size_ bytes from a file.
    Error load(utl::FileIO& fio) noexcept;

    /// @brief Load up to size bytes from file.
    Error load(utl::FileIO& fio, std::size_t size) noexcept;

    /// @brief Load size bytes from file.
    Error fill(utl::FileIO& fio) noexcept;

    /// @brief Load size bytes from file.
    Error fill(utl::FileIO& fio, std::size_t size) noexcept;

    /// @brief Return the free space in the buffer.
    std::size_t freespc() const noexcept;

    /// @brief Reset the buffer to its initial state.
    virtual void reset() noexcept = 0;

    /// @brief Clear the buffer contents setting it to 0
    virtual void clear() noexcept = 0;

    /// @brief Try to resize the buffer to a certain minimum size.
    virtual bool resize(std::size_t) noexcept = 0;

    /// @brief Return the total size of the buffer.
    virtual std::size_t memsize() const noexcept = 0;

    /// @brief Return the current size of the buffer.
    virtual std::size_t cursize() const noexcept = 0;

    /// @brief Return the number of buffer views.
    virtual std::size_t nbviews() const noexcept = 0;

    /// @brief Return the number of the underlying blocks.
    virtual std::size_t nblocks() const noexcept = 0;

    virtual iterator end()   noexcept = 0;
    virtual iterator begin() noexcept = 0;

    virtual const_iterator end()   const noexcept = 0;
    virtual const_iterator begin() const noexcept = 0;

    virtual const_iterator cend()   const noexcept = 0;
    virtual const_iterator cbegin() const noexcept = 0;

    /// @brief Return a view of the buffer based on the iterator.
    ///
    /// @param[in] iter Iterator to get the view for.
    /// @return A valid view of the buffer, on success.
    /// @return A nullptr value, on error.
    ///
    /// @note The programmer must check the return value before performing
    /// any operations on the return value.
    virtual View* view(const iterator& iter) noexcept = 0;

    virtual View* view(memory_offset offset) noexcept = 0;

    /// @brief Return an iterator corresponding to the buffer offset.
    ///
    /// @param[in,out] offset Offset from the start of the memory arena.
    /// @returns An iterator corresponding to the buffer offset.
    /// @returns An end iterator if the offset exceeds the memory arena size.
    ///
    /// @note the offset is updated, so that it contains the relative offset
    /// from the start of the corresponding to the returned iterator buf::View.
    iterator viterator(memory_offset& offset) noexcept;

};

inline std::size_t Model::freespc() const noexcept
{
    return memsize() - cursize();
}

/// @brief Copy no more than size bytes from src to dst.
///
/// Copy no more than size bytes from src reading at offset srcoff to dst,
/// writing at offset dstoff.
///
/// @param[in] dst Destination buffer.
/// @param[in] src Source buffer.
/// @param[in] size The number of bytes to copy.
/// @param[in] dstoff The memory offset in the destination buffer.
/// @param[in] srcoff The memory offset in the source buffer.
/// @returns The bytes actually copied.
///
std::size_t copy(Model& dst, Model& src, std::size_t size,
                 memory_offset dstoff, memory_offset srcoff);

}    // namespace buf
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_LIB_BUF__MODEL_H_
