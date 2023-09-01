//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocks/ucm/lib/buf/view.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_BUF__VIEW_H_
#define UCM_AAP_LIBRARY__UCM_LIB_BUF__VIEW_H_

#include "ucm/lib/buf/error.h"
#include "ucm/lib/buf/types.h"
#include "ucm/lib/utl/file_io.h"

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace buf   {

class View : virtual protected ucm::mock::Sequence
{
public:

    explicit View(std::size_t, std::size_t) noexcept
    {}

    View() noexcept = default;

    View(View     &&) = default;
    View(View const&) = default;

    View& operator=(View     &&) = default;
    View& operator=(View const&) = delete;

    virtual ~View() = default;

    void clear() noexcept {}

    void reset() noexcept {}

    explicit operator bool() const noexcept
    { return pop<bool>();  }

    std::size_t memsize() const noexcept { return pop<std::size_t>(); }
    std::size_t cursize() const noexcept { return pop<std::size_t>(); }
    std::size_t freespc() const noexcept { return pop<std::size_t>(); }

    template<typename T,
        std::enable_if_t<std::is_pointer<T>::value, bool> = true>
    T mapmem(const memory_offset&) noexcept
    {
        return nullptr;
    }

    template<typename T,
        std::enable_if_t<std::is_pointer<T>::value, bool> = true>
    const T mapmem(const memory_offset&) const noexcept
    {
        return nullptr;
    }

    const void *mapmem() const noexcept
    {
    	return nullptr;
    }

    const void *mapmem(const memory_offset&) const noexcept
    {
    	return pop<const void *>();
    }

    template<typename T,
        std::enable_if_t<std::is_pointer<T>::value, bool> = true>
    T mapcur(const memory_offset&) noexcept
    {
        return nullptr;
    }

    template<typename T,
        std::enable_if_t<std::is_pointer<T>::value, bool> = true>
    T mapcur(std::size_t, const memory_offset&) const noexcept
    {
        return nullptr;
    }

    std::size_t write(const void*, std::size_t) noexcept
    {
        return pop<std::size_t>();
    }

    std::size_t write(const void*,
                      std::size_t, const memory_offset&) noexcept
    {
        return pop<std::size_t>();
    }

    Error save(utl::FileIO&) noexcept
    {
        return pop<Error>();
    }

    Error save(utl::FileIO&, const iofile_offset&) noexcept
    {
        return pop<Error>();
    }

    Error save(utl::FileIO&, const memory_offset&) noexcept
    {
        return pop<Error>();
    }

    Error save(utl::FileIO&,
               const memory_offset&,
               const iofile_offset&) noexcept
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

    Error load(utl::FileIO&, std::size_t, off_t) noexcept
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

    Error fill(utl::FileIO&, std::size_t, off_t) noexcept
    {
        return pop<Error>();
    }

protected:
    virtual const void* mregion() const & noexcept = 0;

    virtual void* mregion() & noexcept = 0;
};


}    // namespace buf
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_LIB_BUF__VIEW_H_
