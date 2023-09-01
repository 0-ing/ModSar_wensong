//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/mocks/ara_crypto/mock_ara_crypto.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks


#ifndef UCM_AAP_PROCESSING_VRTE_TESTS_VRTE_UT_MOCKS_ARA_CRYPTO_MOCK_ARA_CRYPTO_H_
#define UCM_AAP_PROCESSING_VRTE_TESTS_VRTE_UT_MOCKS_ARA_CRYPTO_MOCK_ARA_CRYPTO_H_

#include "ucm/mock/sequence.h"
#include "ara/core/result.h"
#include "ara/core/string.h"
#include "ara/core/vector.h"
#include "ucm/lib/ara/ara_types.h"
#include <ara/core/span.h>

namespace ara    {
namespace core   {

class InstanceSpecifier
{
public:
    InstanceSpecifier(StringView ) {}
    ~InstanceSpecifier() = default;
};
} // namespace core


namespace crypto {

using ReadOnlyMemRegion = ara::core::Span<const std::uint8_t>;

struct IOInterface
{
    using Uptr = std::unique_ptr<IOInterface>;

    virtual ~IOInterface() = default;
};

namespace cryp   {

class DigestService
        : protected ::bosch::vrte::ucm::mock::Sequence
{

public:
    using Uptr = std::unique_ptr<DigestService>;

    DigestService()          = default;
    virtual ~DigestService() = default;

    virtual std::size_t GetDigestSize() {
        return pop<std::size_t>();
    }
};

class HashFunctionCtx
        : protected ::bosch::vrte::ucm::mock::Sequence
{
public:

    using Uptr = std::unique_ptr<HashFunctionCtx>;

    HashFunctionCtx() = default;

    virtual ~HashFunctionCtx() = default;

    virtual ::ara::core::Result<void> Start () noexcept(false)
    {
        return ::ara::core::Result<void>();
    }

    virtual ::ara::core::Result<void>
    Update(ReadOnlyMemRegion) noexcept(false)
    {
        return ::ara::core::Result<void>();
    }

    virtual ::ara::core::Result<void>
    Process(ReadOnlyMemRegion) noexcept(false)
    {
        return ::ara::core::Result<void>();
    }

    virtual ::ara::core::Result<::ara::core::Vector<::ara::core::Byte>>
    Finish()
    {
        return pop<::ara::core::Result<
                ::ara::core::Vector<::ara::core::Byte>>>();
    }

    virtual ara::core::Result<::ara::core::Vector<::ara::core::Byte>>
    GetDigest()
    {
        return pop<ara::core::Result<
                ::ara::core::Vector<::ara::core::Byte>>>();
    }

    virtual DigestService::Uptr GetDigestService()
    {
        return pop<DigestService::Uptr>();
    }
};

class PublicKey
        : protected ::bosch::vrte::ucm::mock::Sequence
{

public:
    using Uptrc = std::unique_ptr<PublicKey>;

    PublicKey()          = default;
    virtual ~PublicKey() = default;
};

class VerifierPublicCtx
        : protected ::bosch::vrte::ucm::mock::Sequence
{
public:
    using Uptr = std::unique_ptr<VerifierPublicCtx>;

    virtual ~VerifierPublicCtx() = default;

    virtual ara::core::Result<bool>
    Verify(ReadOnlyMemRegion, ReadOnlyMemRegion) noexcept
    {
        return pop<ara::core::Result<bool>>();
    }

    virtual ara::core::Result<void>
    SetKey(const PublicKey& ) noexcept
    {
        return ::ara::core::Result<void>();
    }
};


struct CryptoProvider
        : protected ::bosch::vrte::ucm::mock::Sequence
{
    using AlgId = ::ara::core::StringView;
    using Uptr = std::unique_ptr<CryptoProvider>;

    virtual ~CryptoProvider() = default;

    virtual ara::core::Result<HashFunctionCtx::Uptr>
    CreateHashFunctionCtx(AlgId) noexcept
    {
        // work-around for pwi 24602
        return pop<ara::core::Result<HashFunctionCtx::Uptr>&&>();
    }

    virtual ara::core::Result<VerifierPublicCtx::Uptr>
    CreateVerifierPublicCtx(AlgId) noexcept
    {
        // work-around for pwi 24602
        return pop<ara::core::Result<VerifierPublicCtx::Uptr>&&>();
    }

    virtual ara::core::Result<PublicKey::Uptrc>
    LoadPublicKey(const IOInterface& ) noexcept
    {
        // work-around for pwi 24602
        return pop<ara::core::Result<PublicKey::Uptrc>&&>();
    }

    virtual AlgId ConvertToAlgId(::ara::core::StringView )
    {
        return "dummy";
    }

};

} // namespace cryp

namespace keys {

struct KeySlot
        : protected ::bosch::vrte::ucm::mock::Sequence
{
    using AlgId = ::ara::core::StringView;
    using Uptr = std::unique_ptr<KeySlot>;

    virtual ~KeySlot() = default;

    virtual ara::core::Result<IOInterface::Uptr>
    Open(bool , bool ) noexcept
    {
        return pop<ara::core::Result<IOInterface::Uptr>&&>();
    }
};

struct KeyStorageProvider
        : protected ::bosch::vrte::ucm::mock::Sequence
{
    using Uptr = std::unique_ptr<KeyStorageProvider>;

    virtual ~KeyStorageProvider() = default;

    virtual ara::core::Result<KeySlot::Uptr>
    LoadKeySlot(ara::core::InstanceSpecifier& ) noexcept
    {
        return pop<ara::core::Result<KeySlot::Uptr>&&>();
    }

};

} // namespace keys

inline cryp::CryptoProvider::Uptr
LoadCryptoProvider(const ara::core::InstanceSpecifier& ) noexcept
{
    return ::bosch::vrte::ucm::mock::Sequence::pop<
            cryp::CryptoProvider::Uptr>();
}

inline keys::KeyStorageProvider::Uptr
LoadKeyStorageProvider() noexcept
{
    return ::bosch::vrte::ucm::mock::Sequence::pop<
            keys::KeyStorageProvider::Uptr>();
}

} // namespace crypto
} // namespace ara

#endif // UCM_AAP_PROCESSING_VRTE_TESTS_VRTE_UT_MOCKS_ARA_CRYPTO_MOCK_ARA_CRYPTO_H_
