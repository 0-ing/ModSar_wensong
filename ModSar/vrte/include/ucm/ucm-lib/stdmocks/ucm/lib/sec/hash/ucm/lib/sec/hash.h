//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         src/ucm/lib/sec/hash.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_SEC_HASH_H_
#define UCM_AAP_LIBRARY_LIB_SEC_HASH_H_

#include "ucm/mock/sequence.h"

#include "ara/core/result.h"
#include "ara/core/vector.h"

#include <memory>
#include <string>
#include <type_traits>

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace sec   {


class Hash
    : virtual protected ucm::mock::Sequence
{

public:
    using size_type  = std::size_t;
    using value_type = ::ara::core::Byte;
    using Digest     = ::ara::core::Vector<value_type>;

    virtual ~Hash() = default;

    template<typename T, typename... U>
    static std::unique_ptr<Hash> make(U&&...u)
    {
        static_assert(std::is_base_of<Hash, T>::value, "");
        return std::make_unique<T>(static_cast<U&&>(u)...);
    }

    // retrieve result
    size_type digest_size()     { return pop<size_type>();     }
    Digest const& digest()      { return pop<Digest const&>(); }
    std::string digest_string() { return pop<std::string>();   }

    // primitive streaming api
    void init()                            { pop<void>(); }
    void start()                           { pop<void>(); }
    void process(void const*, std::size_t) { pop<void>(); }
    void end()                             { pop<void>(); }
    void fini()                            { pop<void>(); }

protected:
    Hash()                       = default;
    Hash(Hash const&)            = delete;
    Hash(Hash     &&) noexcept   = default;
    Hash& operator=(Hash const&) = delete;
    Hash& operator=(Hash     &&) = default;

    enum class State
    {
        uninitialized,
        initialized,
        started,
        processing,
        ended,
        digest
    } state {State::uninitialized};

    // implementation interface
    virtual void _init()                                 {}
    virtual void _start()                                {}
    virtual void _process(const void* data, std::size_t) { (void)(data); }
    virtual void _end()                                  {}
    virtual void _digest()                               {}
    virtual void _fini()                                 {}
    virtual size_type _digest_size()                     { return pop<size_type>(); }

    Digest digest_value_{};
};


}    // namespace sec
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_SEC_HASH_H_
