//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocks/ucm/lib/buf/array.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_BUF__ARRAY_H_
#define UCM_AAP_LIBRARY__UCM_LIB_BUF__ARRAY_H_

#include "ucm/lib/buf/error.h"
#include "ucm/lib/buf/model.h"
#include "ucm/lib/buf/types.h"
#include "ucm/lib/buf/rw_view.h"
#include "ucm/lib/utl/file_io.h"

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace buf   {

template<size_t _BSize,
         size_t _VSize = _BSize>
class Array final
    : public Model
    , virtual protected ucm::mock::Sequence
{
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
    explicit Array() = default;

    Array(Array     &&) = default;
    Array(Array const&) = delete;

    Array& operator=(Array     &&) = default;
    Array& operator=(Array const&) = delete;

    ~Array() = default;

    void reset() noexcept override {}

    void clear() noexcept override {}

    bool resize(std::size_t) noexcept override
    { return false; }

    std::size_t memsize() const noexcept override
    { return _BSize; }

    std::size_t cursize() const noexcept override
    { return pop<std::size_t>(); }

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

    View* view(const iterator&) noexcept override
    { return pop<View*>(); }

    View* view(memory_offset) noexcept override
    { return pop<View*>(); }
};


}    // namespace buf
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_LIB_BUF__ARRAY_H_
