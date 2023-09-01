//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/buf/array.h
/// @brief        Array based implementation of the flexible buffer model
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup bosch_vrte_ucm_lib_buf

#ifndef UCM_AAP_LIBRARY__UCM_LIB_BUF__ARRAY_H_
#define UCM_AAP_LIBRARY__UCM_LIB_BUF__ARRAY_H_

#include <array>
#include <cassert>
#include <type_traits>

#if defined(GOOGLE_TEST)
#include <gtest/gtest_prod.h>
#endif

#include "ucm/lib/buf/view.h"
#include "ucm/lib/buf/model.h"
#include "ucm/lib/buf/rw_view.h"

/// @addtogroup bosch_vrte_ucm_lib_buf
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace buf   {

/// @class Array array.h ucm/lib/buf/array.h
/// @ingroup bosch_vrte_ucm_lib_buf
/// @brief Array based implementation of the flexible buffer model.
///
/// The array based implementation of the flexible buffer Model allows the
/// programmer to create an underlying std::array of size _BSize and split it
/// into views of size _VSize. The size of the last view might be smaller than
/// the _VSize if it will overflow.
///
template<size_t _BSize,
         size_t _VSize = _BSize>
class Array final : public Model
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_buf__Array, TEST__CTor);
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    // Calculate the number buf::View objects
    constexpr static std::size_t vcount =
            _BSize / _VSize + (_BSize % _VSize > 0 ? 1 : 0);

    using type_array = std::array<value_type, _BSize>;
    using view_array = std::array<buf::RW_View,  vcount>;

    constexpr static std::size_t value_size() noexcept
    { return sizeof(value_type); }

    constexpr static std::size_t value_size(size_t items) noexcept
    { return value_size() * items; }

#endif // DOXYGEN_SHOULD_SKIP_THIS

public:
    /// @brief Construct a buf::Array
    ///
    explicit Array()
    {
        reset();
    }

    Array(Array     &&) = default;
    Array(Array const&) = delete;

    Array& operator=(Array     &&) = default;
    Array& operator=(Array const&) = delete;

    ~Array() = default;

    /// @brief Reset the buffer to an initial state.
    ///
    /// Reset the buffer to an initial state by re-creating the views defined
    /// on it.
    ///
    void reset() noexcept override
    {
        auto memptr = data8();

        for (std::size_t i = 0, sofar = 0, bleft = _BSize; i < vcount; ++i) {
            auto vsize = bleft > _VSize ? _VSize : bleft;
            bviews_[i] = RW_View(memptr + sofar, vsize, 0);
            bleft -= vsize;
            sofar += vsize;
        }
    }

    void clear() noexcept override
    {
        for (auto&& view : bviews_)
            view.clear();
    }

    bool resize(std::size_t) noexcept override
    { return false; }

    std::size_t memsize() const noexcept override
    { return _BSize; }

    std::size_t cursize() const noexcept override
    {
        std::size_t size = 0;
        for (auto&& view : bviews_) {
            if (view)
                size += view.cursize();
        }
        return size;
    }

    std::size_t nbviews() const noexcept override
    { return vcount; }

    std::size_t nblocks() const noexcept override
    { return 1; }

    iterator end() noexcept override
    { return iterator(nbviews(), nbviews()); }

    iterator begin() noexcept override
    { return iterator(nbviews(), 0); }

    const_iterator end() const noexcept override
    { return const_iterator(nbviews(), nbviews()); }

    const_iterator begin() const noexcept override
    { return const_iterator(nbviews(), 0); }

    const_iterator cend() const noexcept override
    { return end(); }

    const_iterator cbegin() const noexcept override
    { return begin(); }

    View* view(const iterator& iter) noexcept override
    {
        if (iter == end())
            return nullptr;
        else
            return &bviews_[iter.curblock()];
    }

    View* view(memory_offset offset) noexcept override
    {
        for (auto& view : bviews_) {
            if (offset >= view.memsize()) {
                offset -= view.memsize();
                continue;
            }
            return &view;
        }
        return nullptr;
    }

private:
    view_array bviews_{};
    type_array memory_{};

    constexpr void* data() noexcept
    { return static_cast<void*>(memory_.data()); }

    constexpr const void* data() const noexcept
    { return static_cast<const void*>(memory_.data()); }

    constexpr void* data(std::size_t offset) noexcept
    { return static_cast<void*>(data8(offset)); }

    constexpr const void* data(std::size_t offset) const noexcept
    { return static_cast<const void*>(data8(offset)); }

    constexpr std::uint8_t* data8(std::size_t offset = 0) noexcept
    { return static_cast<std::uint8_t*>(data()) + offset; }

    constexpr const std::uint8_t* data8(std::size_t offset = 0) const noexcept
    { return static_cast<const std::uint8_t*>(data()) + offset; }

};

}    // namespace buf
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_LIB_BUF__ARRAY_H_
