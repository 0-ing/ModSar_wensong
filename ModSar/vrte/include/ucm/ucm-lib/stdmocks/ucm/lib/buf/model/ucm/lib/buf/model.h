//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocks/ucm/lib/buf/model.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_BUF__MODEL_H_
#define UCM_AAP_LIBRARY__UCM_LIB_BUF__MODEL_H_

#include "ucm/lib/buf/view.h"
#include "ucm/lib/buf/error.h"
#include "ucm/lib/buf/iterator.h"

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace buf   {

class Model : virtual protected ucm::mock::Sequence
{
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
    T mapviewnc(bool, const memory_offset&)
    {
        return pop<T>();
    }

    template<typename T,
        std::enable_if_t<std::is_pointer<T>::value, bool> = true>
    T mapview(bool, const memory_offset&)
    {
        return pop<T>();
    }

    std::size_t write(const void*, std::size_t) noexcept
    {
        return pop<std::size_t>();
    }

    std::size_t write(const void*, std::size_t, memory_offset) noexcept
    {
        return pop<std::size_t>();
    }

    Error save(utl::FileIO&) noexcept
    {
        return pop<Error>();
    }

    Error save(utl::FileIO&, memory_offset) noexcept
    {
        return pop<Error>();
    }

    Error save(utl::FileIO&, iofile_offset) noexcept
    {
        return pop<Error>();
    }

    Error save(utl::FileIO&, memory_offset, iofile_offset) noexcept
    {
        return pop<Error>();
    }

    Error load(utl::FileIO&) noexcept
    {
        return pop<Error>();
    }


    Error load(utl::FileIO&, std::size_t) noexcept
    {
        return pop<Error>();
    }

    Error fill(utl::FileIO&) noexcept
    {
        return pop<Error>();
    }

    Error fill(utl::FileIO&, std::size_t) noexcept
    {
        return pop<Error>();
    }

    std::size_t freespc() const noexcept
    {
        return pop<std::size_t>();
    }

    virtual void reset() noexcept {}

    virtual void clear() noexcept {}

    virtual bool resize(std::size_t) noexcept
    {
        return pop<bool>();
    }

    virtual std::size_t memsize() const noexcept
    {
        return pop<std::size_t>();
    }

    virtual std::size_t cursize() const noexcept
    {
        return pop<std::size_t>();
    }

    iterator viterator(memory_offset&) noexcept
    {
        std::size_t mb = pop<std::size_t>();
        std::size_t cb = pop<std::size_t>();
        return iterator(mb, cb);
    }


    virtual std::size_t nbviews() const noexcept = 0;

    virtual std::size_t nblocks() const noexcept = 0;

    virtual iterator end()   noexcept = 0;
    virtual iterator begin() noexcept = 0;

    virtual const_iterator end()   const noexcept = 0;
    virtual const_iterator begin() const noexcept = 0;

    virtual const_iterator cend()   const noexcept = 0;
    virtual const_iterator cbegin() const noexcept = 0;

    virtual View* view(const iterator&) noexcept = 0;

    virtual View* view(memory_offset) noexcept = 0;
};


}    // namespace buf
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_LIB_BUF__MODEL_H_
