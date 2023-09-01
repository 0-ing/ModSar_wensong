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
/// @ingroup bosch_vrte_ucm_lib_sec

#ifndef UCM_AAP_LIBRARY_LIB_SEC_HASH_H_
#define UCM_AAP_LIBRARY_LIB_SEC_HASH_H_

#include "ara/core/result.h"
#include "ara/core/vector.h"

#include <memory>
#include <string>
#include <type_traits>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

/// @addtogroup bosch_vrte_ucm_lib_sec
/// @{
	
	
namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace sec   {


class Hash
{
	
/// @class Array array.h ucm/lib/buf/array.h
/// @ingroup bosch_vrte_ucm_lib_buf
/// @brief Array based implementation of the flexible buffer model.
///
/// TODO:Description

#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_Lib_Sec_Hash, Simple);
    FRIEND_TEST(Test_Lib_Sec_Hash, Transitions);
    FRIEND_TEST(Test_Lib_Sec_Hash, Digest_String);
#endif

public:

    using size_type  = std::size_t;
    using value_type = ::ara::core::Byte;
    using Digest     = ::ara::core::Vector<value_type>;

    virtual ~Hash();

    template<typename T, typename... U>
    static std::unique_ptr<Hash> make(U&&...u)
    {
        static_assert(std::is_base_of<Hash, T>::value, "");
        return std::make_unique<T>(static_cast<U&&>(u)...);
    }

    // retrieve result
    size_type digest_size();
    Digest const& digest();
    std::string digest_string();

    // primitive streaming api
    void init();
    void start();
    void process(void const* data, std::size_t length);
    void end();
    void fini();

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
    virtual void _init()                                        = 0;
    virtual void _start()                                       = 0;
    virtual void _process(const void* data, std::size_t length) = 0;
    virtual void _end()                                         = 0;
    virtual void _digest()                                      = 0;
    virtual void _fini()                                        = 0;
    virtual size_type _digest_size()                            = 0;

    Digest digest_value_{};
};


}    // namespace sec
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY_LIB_SEC_HASH_H_
