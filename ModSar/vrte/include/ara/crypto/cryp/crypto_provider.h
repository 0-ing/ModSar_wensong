// --------------------------------------------------------------------------
// |              _    _ _______     .----.      _____         _____        |
// |         /\  | |  | |__   __|  .  ____ .    / ____|  /\   |  __ \       |
// |        /  \ | |  | |  | |    .  / __ \ .  | (___   /  \  | |__) |      |
// |       / /\ \| |  | |  | |   .  / / / / v   \___ \ / /\ \ |  _  /       |
// |      / /__\ \ |__| |  | |   . / /_/ /  .   ____) / /__\ \| | \ \       |
// |     /________\____/   |_|   ^ \____/  .   |_____/________\_|  \_\      |
// |                              . _ _  .                                  |
// --------------------------------------------------------------------------
//
// All Rights Reserved.
// Any use of this source code is subject to a license agreement with the
// AUTOSAR development cooperation.
// More information is available at www.autosar.org.
//
// Disclaimer
//
// This work (specification and/or software implementation) and the material
// contained in it, as released by AUTOSAR, is for the purpose of information
// only. AUTOSAR and the companies that have contributed to it shall not be
// liable for any use of the work.
//
// The material contained in this work is protected by copyright and other
// types of intellectual property rights. The commercial exploitation of the
// material contained in this work requires a license to such intellectual
// property rights.
//
// This work may be utilized or reproduced without any modification, in any
// form or by any means, for informational purposes only. For any other
// purpose, no part of the work may be utilized or reproduced, in any form
// or by any means, without permission in writing from the publisher.
//
// The work has been developed for automotive applications only. It has
// neither been developed, nor tested for non-automotive applications.
//
// The word AUTOSAR and the AUTOSAR logo are registered trademarks.
// --------------------------------------------------------------------------

/// @file
/// @brief Adaptive Autosar Crypto Stack. Cryptographic API. CryptoProvider interface definition.

#ifndef ARA_CRYPTO_CRYP_CRYPTO_PROVIDER_H_
#define ARA_CRYPTO_CRYP_CRYPTO_PROVIDER_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/common/crypto_error_domain.h"
#include "ara/crypto/cryp/auth_cipher_ctx.h"
#include "ara/crypto/common/io_interface.h"
#include "ara/crypto/common/volatile_trusted_container.h"
#include "ara/crypto/common/mem_region.h"
#include "ara/crypto/common/serializable.h"
#include "ara/crypto/cryp/cryobj/crypto_primitive_id.h"
#include "ara/crypto/cryp/key_agreement_private_ctx.h"
#include "ara/crypto/cryp/random_generator_ctx.h"
#include "ara/crypto/cryp/symmetric_block_cipher_ctx.h"
#include "ara/crypto/cryp/symmetric_key_wrapper_ctx.h"
#include "ara/crypto/cryp/stream_cipher_ctx.h"
#include "ara/crypto/cryp/message_authn_code_ctx.h"
#include "ara/crypto/cryp/hash_function_ctx.h"
#include "ara/crypto/cryp/key_derivation_function_ctx.h"
#include "ara/crypto/cryp/encryptor_public_ctx.h"
#include "ara/crypto/cryp/decryptor_private_ctx.h"
#include "ara/crypto/cryp/signer_private_ctx.h"
#include "ara/crypto/cryp/verifier_public_ctx.h"
#include "ara/crypto/cryp/key_encapsulator_public_ctx.h"
#include "ara/crypto/cryp/key_decapsulator_private_ctx.h"
#include "ara/crypto/cryp/sig_encode_private_ctx.h"
#include "ara/crypto/cryp/msg_recovery_public_ctx.h"
#include "ara/crypto/cryp/cryobj/signature.h"

#include "ara/core/result.h"
#include "ara/core/string.h"

namespace ara
{
namespace crypto
{
namespace cryp
{

//- @interface CryptoProvider
///
/// @traceid{SWS_CRYPT_20700}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02305}
/// @uptrace{RS_CRYPTO_02307}
/// @uptrace{RS_CRYPTO_02401}
/// @brief Crypto Provider is a "factory" interface of all supported Crypto Primitives and a "trusted environmet" for
///           internal communications between them.
///       All Crypto Primitives should have an actual reference to their parent Crypto Provider.
///       A Crypto Provider can be destroyed only after destroying of all its daughterly Crypto Primitives.
///       Each method of this interface that creates a Crypto Primitive instance is non-constant, because any such
///       creation increases a references counter of the Crypto Primitive.
///

class CryptoProvider
{

public:
    /// @traceid{SWS_CRYPT_20701}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02109}
    /// @brief Shared smart pointer of the interface.
	using Uptr = std::unique_ptr<CryptoProvider>;

    /// @traceid{SWS_CRYPT_20703}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02005}
    /// @uptrace{RS_CRYPTO_02006}
    /// @brief A short alias for Algorithm ID type definition.
    using AlgId = CryptoPrimitiveId::AlgId;

    /// @traceid{SWS_CRYPT_20710}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02107}
    /// @brief Destructor.
    virtual ~CryptoProvider() noexcept = default;

    /// @traceid{SWS_CRYPT_30216}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Copy-assign another CryptoProvider to this instance.
    /// @param other  the other instance
    /// @returns *this, containing the contents of @a other
    CryptoProvider& operator=(const CryptoProvider& other) = default;

    /// @traceid{SWS_CRYPT_30217}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Move-assign another CryptoProvider to this instance.
    /// @param other  the other instance
    /// @returns *this, containing the contents of @a other
    CryptoProvider& operator=(CryptoProvider&& other) = default;

    CryptoProvider(const CryptoProvider& other) = default;
    CryptoProvider(CryptoProvider&& other) = default;
    CryptoProvider() = default;

    /// @traceid{SWS_CRYPT_20711}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02308}
    /// @brief Convert a common name of crypto algorithm to a correspondent vendor specific binary algorithm ID.
    /// @param[in] primitiveName  the unified name of the crypto primitive (see "Crypto Primitives Naming Convention"
    ///            for more details)
    /// @returns vendor specific binary algorithm ID or @c kAlgIdUndefined if a primitive with provided name is not
    ///          supported
    /// @threadsafety{Thread-safe}
    virtual AlgId ConvertToAlgId(ara::core::StringView primitiveName) const noexcept = 0;

    /// @traceid{SWS_CRYPT_20712}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02308}
    /// @brief Convert a vendor specific binary algorithm ID to a correspondent common name of the crypto algorithm.
    /// @param[in] algId  the vendor specific binary algorithm ID
    /// @returns the common name of the crypto algorithm (see "Crypto Primitives Naming Convention" for more details)
    /// @error CryptoErrorDomain::kUnknownIdentifier  if @c algId argument has an unsupported value
    /// @threadsafety{Thread-safe}
    virtual ara::core::Result<ara::core::String> ConvertToAlgName(AlgId algId) const noexcept = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /// @traceid{SWS_CRYPT_20721}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02003}
    /// @uptrace{RS_CRYPTO_02101}
    /// @uptrace{RS_CRYPTO_02102}
    /// @uptrace{RS_CRYPTO_02107}
    /// @uptrace{RS_CRYPTO_02108}
    /// @uptrace{RS_CRYPTO_02111}
    /// @uptrace{RS_CRYPTO_02115}
    /// @brief Allocate a new symmetric key object and fill it by a new randomly generated value.
	///      Any serializable (i.e. savable/non-session or exportable) key must generate own COUID!
    ///      By default Crypto Provider should use an internal instance of a best from all supported RNG (ideally TRNG).
    /// @param[in] algId  the identifier of target symmetric crypto algorithm
    /// @param[in] allowedUsage  the flags that define a list of allowed transformations' types in which the target key
    ///            can be used (see constants in scope of @c RestrictedUseObject)
    /// @param[in] isSession  the "session" (or "temporary") attribute of the target key (if @c true)
    /// @param[in] isExportable  the exportability attribute of the target key (if @c true)
    /// @returns smart unique pointer to the created symmetric key object

    /// @error CryptoErrorDomain::kUnknownIdentifier  if @c algId has an unsupported value
    /// @error CryptoErrorDomain::kIncompatibleArguments  if @c allowedUsage argument is incompatible with
    ///                target algorithm @c algId (note: it is an optional error condition for this method)
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<SymmetricKey::Uptrc> GenerateSymmetricKey(AlgId algId,
    	AllowedUsageFlags allowedUsage,
        bool isSession = true,
        bool isExportable = false
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_20722}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02003}
    /// @uptrace{RS_CRYPTO_02101}
    /// @uptrace{RS_CRYPTO_02102}
    /// @uptrace{RS_CRYPTO_02107}
    /// @uptrace{RS_CRYPTO_02108}
    /// @uptrace{RS_CRYPTO_02111}
    /// @uptrace{RS_CRYPTO_02115}
    /// @brief Allocate a new private key context of correspondent type and generates the key value randomly.
	///     A common COUID should be shared for both private and public keys.
    ///      Any serializable (i.e. savable/non-session or exportable) key must generate own COUID!
    /// @param[in] algId  the identifier of target public-private key crypto algorithm
    /// @param[in] allowedUsage  the flags that define a list of allowed transformations' types in which the target key
    ///            can be used (see constants in scope of @c RestrictedUseObject)
    /// @param[in] isSession  the "session" (or "temporary") attribute for the target key (if @c true)
    /// @param[in] isExportable  the exportability attribute of the target key (if @c true)
    /// @returns smart unique pointer to the created private key object

    /// @error CryptoErrorDomain::kUnknownIdentifier  if @c algId has an unsupported value
    /// @error CryptoErrorDomain::kIncompatibleArguments  if @c allowedUsage argument is incompatible with
    ///                target algorithm @c algId (note: it is an optional error condition for this method)
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<PrivateKey::Uptrc> GeneratePrivateKey(AlgId algId,
    	AllowedUsageFlags allowedUsage,
        bool isSession = false,
        bool isExportable = false
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_20723}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02007}
    /// @brief Generate a random Secret Seed object of requested algorithm.
    /// @param[in] algId  the identifier of target crypto algorithm
    /// @param[in] allowedUsage  the lags that define a list of allowed transformations' types in which the target seed
    ///            can be used (see constants in scope of @c RestrictedUseObject)
    /// @param[in] isSession  the "session" (or "temporary") attribute of the target seed (if @c true)
    /// @param[in] isExportable  the exportability attribute of the target seed (if @c true)
    /// @returns unique smart pointer to generated @c SecretSeed object
    /// @error CryptoErrorDomain::kUnknownIdentifier  if @c algId has an unsupported value
    /// @error CryptoErrorDomain::kIncompatibleArguments  if @c allowedUsage argument is incompatible with
    ///                target algorithm @c algId (note: it is an optional error condition for this method)
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<SecretSeed::Uptrc> GenerateSeed(AlgId algId,
        SecretSeed::Usage allowedUsage,
        bool isSession = true,
        bool isExportable = false
    ) noexcept = 0;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /// @traceid{SWS_CRYPT_20724}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02005}
    /// @uptrace{RS_CRYPTO_02006}
    /// @brief Return required buffer size for serialization of an object in specific format.
    /// @param[in] cryptoObjectType  the type of the target object
    /// @param[in] algId  the Crypto Provider algorithm ID of the target object
    /// @param[in] formatId  the Crypto Provider specific identifier of the output format
    /// @returns size required for storing of the object serialized in the specified format
    /// @error CryptoErrorDomain::kUnknownIdentifier  if any argument has an unsupported value
    /// @error CryptoErrorDomain::kIncompatibleArguments  if any pair of the arguments are incompatible
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<std::size_t> GetSerializedSize(CryptoObjectType cryptoObjectType,
        AlgId algId,
        Serializable::FormatId formatId = Serializable::kFormatDefault
    ) const noexcept = 0;

    /// @traceid{SWS_CRYPT_20725}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02005}
    /// @uptrace{RS_CRYPTO_02006}
    /// @brief Return minimally required capacity of a key slot for saving of the object's payload.
	///      Returned value does not take into account the object's meta-information properties,
    ///       but their size is fixed and common for all crypto objects independently from their actual type.
    ///       During an allocation of a @c TrustedContainer, Crypto Providers (and %Key Storage Providers) reserve
    ///       space for an object's meta-information automatically, according to their implementation details.
    /// @param[in] cryptoObjectType  the type of the target object
    /// @param[in] algId  a CryptoProvider algorithm ID of the target object
    /// @returns minimal size required for storing of the object in a @c TrustedContainer (persistent or volatile)

    /// @error CryptoErrorDomain::kUnknownIdentifier  if any argument has an unsupported value
    /// @error CryptoErrorDomain::kIncompatibleArguments  if the arguments are incompatible
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<std::size_t> GetPayloadStorageSize(CryptoObjectType cryptoObjectType, AlgId algId)
        const noexcept = 0;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /// @traceid{SWS_CRYPT_20726}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02005}
    /// @uptrace{RS_CRYPTO_02006}
    /// @brief Allocate a Volatile (virtual) Trusted Container according to directly specified capacity.
    ///      The Volatile Trusted Container can be used for execution of the import operations.
    ///       Current process obtains the "Owner" rights for allocated Container.
    ///       If <tt>(capacity == 0)</tt> then the capacity of the container will be selected automatically according to
    ///       a maximal size of supported crypto objects.
    ///      A few volatile (temporary) containers can coexist at same time without any affecting each-other.
	/// @param[in] capacity  the capacity required for this volatile trusted container (in bytes)
    /// @returns unique smart pointer to an allocated volatile trusted container
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<VolatileTrustedContainer::Uptr> AllocVolatileContainer(std::size_t capacity = 0)
        noexcept = 0;

    /// @traceid{SWS_CRYPT_20727}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02005}
    /// @uptrace{RS_CRYPTO_02006}
    /// @brief Allocate a Volatile (virtual) Trusted Container according to indirect specification of a minimal
    ///           required capacity for hosting of any listed object.
	///      The Volatile Trusted Container can be used for execution of the import operations.
    ///      Current process obtains the "Owner" rights for allocated Container.
    ///      Real container capacity is calculated as a maximal storage size of all listed objects.
    /// @param[in] theObjectDef  the list of objects that can be stored to this volatile trusted container
    /// @returns unique smart pointer to an allocated volatile trusted container

    /// @error CryptoErrorDomain::kInvalidArgument  if unsupported combination of object type and
    ///                algorithm ID presents in the list
    /// @threadsafety{Thread-safe}
    virtual ara::core::Result<VolatileTrustedContainer::Uptr> AllocVolatileContainer(std::pair<AlgId, CryptoObjectType> theObjectDef)
        noexcept = 0;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /// @traceid{SWS_CRYPT_20728}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02105}
    /// @uptrace{RS_CRYPTO_02112}
    /// @brief Export a crypto object in a secure manner.
	///      if <tt>(serialized.empty() == true)</tt> then the method returns required size only, but content of the
    ///       @c transportContext stays unchanged!
    ///      Only an exportable and completed object (i.e. that have a UUID) can be exported!
    /// @param[in] object  the crypto object for export
    /// @param[in] transportContext  the symmetric key wrap context initialized by a transport key (allowed usage:
    ///            @c kAllowKeyExporting)
    /// @returns the wrapped crypto object data
    ///
    /// @error CryptoErrorDomain::kIncompatibleObject  if the object cannot be exported due to IsExportable() returning flase
    /// @error CryptoErrorDomain::kIncompleteArgState  if the @c transportContext is not initialized
    /// @error CryptoErrorDomain::kIncompatibleObject  if a key loaded to the @c transportContext doesn't
    ///                have required attributes (note: it is an optional error condition for this method)
    /// @threadsafety{Thread-safe}
    virtual ara::core::Result<ara::core::Vector<ara::core::Byte>> ExportSecuredObject(const CryptoObject& object,
        SymmetricKeyWrapperCtx& transportContext
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_20729}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02105}
    /// @uptrace{RS_CRYPTO_02112}
    /// @brief Export securely an object directly from an IOInterface (i.e. without an intermediate creation of
    ///           a crypto object).
	///       if <tt>(serialized == nullptr)</tt> then the method returns required size only, but content of
    ///       the @c transportContext stays unchanged.
    ///       This method can be used for re-exporting of just imported object but on another transport key.
    /// @param[in] container  the IOInterface that refers an object for export
    /// @param[in] transportContext  the symmetric key wrap context initialized by a transport key (allowed usage:
    ///            @c kAllowKeyExporting)
    /// @param[out] serialized  the output buffer for the serialized object
    /// @returns actual capacity required for the serialized data
    /// @error CryptoErrorDomain::kEmptyContainer  if the @c container is empty
    /// @error CryptoErrorDomain::kInsufficientCapacity  if size of the @c serialized buffer is not enough
    ///                for saving the output data
    /// @error CryptoErrorDomain::kIncompleteArgState  if the @c transportContext is not initialized
    /// @error CryptoErrorDomain::kIncompatibleObject  if a key loaded to the @c transportContext doesn't
    ///                have required attributes (note: it is an optional error condition for this method)
    /// @error CryptoErrorDomain::kModifiedResource if the underlying resource has been modified after 
    ///                 the IOInterface has been opened, i.e., the IOInterface has been invalidated.
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<ara::core::Vector<ara::core::Byte>> ExportSecuredObject(const IOInterface& container,
        SymmetricKeyWrapperCtx& transportContext
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_20730}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02105}
    /// @uptrace{RS_CRYPTO_02112}
    /// @brief Import securely serialized object to the persistent or volatile storage represented
    /// by an IOInterface for following
    ///           processing.
    /// @param[out] container  the IOInterface for storing of the imported object
    /// @param[in] serialized  the memory region that contains a securely serialized object that
    /// should be imported to
    ///            the IOInterface
    /// @param[in] transportContext  the symmetric key wrap context initialized by a transport key
    /// (allowed usage:
    ///            @c kAllowKeyImporting)
    /// @param[in] isExportable  the exportability attribute of the target object
    /// @param[in] expectedObject  the expected object type (default value @c
    /// CryptoObjectType::kUnknown means without check)
    /// @error CryptoErrorDomain::kUnexpectedValue  if the @c serialized contains incorrect data
    /// @error CryptoErrorDomain::kBadObjectType  if <tt>(expectedObject !=
    /// CryptoObjectType::kUnknown)</tt>,
    ///                but the actual object type differs from the expected one
    /// @error CryptoErrorDomain::kIncompleteArgState  if the @c transportContext is not initialized
    /// @error CryptoErrorDomain::kIncompatibleObject  if a key loaded to the @c transportContext
    /// doesn't
    ///                have required attributes (note: it is an optional error condition for this
    ///                method)
    /// @error CryptoErrorDomain::kInsufficientCapacity  if capacity of the @c container is not
    /// enough to
    ///                save the deserialized object
    /// @error CryptoErrorDomain::kModifiedResource if the underlying resource has been modified
    /// after
    ///                 the IOInterface has been opened, i.e., the IOInterface has been invalidated.
    /// @error CryptoErrorDomain::kUnreservedResource  if the IOInterface is not opened writeable.
    /// @threadsafety{Thread-safe}
    /// @attention The api signature has been changed from standard Autosar as per the following
    /// ticket: https://jira.autosar.org/browse/AR-109723
    virtual ara::core::Result<ara::core::Optional<ara::core::Vector<ara::core::Byte>>> 
    ImportSecuredObject(
    	IOInterface& container,
        ReadOnlyMemRegion serialized,
        SymmetricKeyWrapperCtx& transportContext,
        bool isExportable = false,
        CryptoObjectType expectedObject = CryptoObjectType::kUndefined) noexcept = 0;

    /// @traceid{SWS_CRYPT_20731}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02105}
    /// @uptrace{RS_CRYPTO_02112}
    /// @brief Export publicly an object from a IOInterface (i.e. without an intermediate creation
    /// of a crypto
    ///           object).
    /// @param[in] container  the IOInterface that contains an object for export
    /// @param[out] serialized  the output buffer for the serialized object
    /// @param[in] formatId  the CryptoProvider specific identifier of the output format
    /// @returns actual capacity required for the serialized data
    /// @error CryptoErrorDomain::kEmptyContainer  if the container is empty
    /// @error CryptoErrorDomain::kUnexpectedValue  if the container contains a secret crypto object
    /// @error CryptoErrorDomain::kInsufficientCapacity  if <tt>(serialized.empty() == false)</tt>,
    ///                but its capacity is not enough for storing result
    /// @error CryptoErrorDomain::kModifiedResource if the underlying resource has been modified
    /// after
    ///                 the IOInterface has been opened, i.e., the IOInterface has been invalidated.
    /// @threadsafety{Thread-safe}

    virtual ara::core::Result<ara::core::Vector<ara::core::Byte>> ExportPublicObject(const IOInterface& container,
        Serializable::FormatId formatId = Serializable::kFormatDefault
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_20732}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02105}
    /// @uptrace{RS_CRYPTO_02112}
    /// @brief Import publicly serialized object to a storage location pointed to by an IOInterface for following
    ///           processing (without allocation of a crypto object).
	///       If <tt>(expectedObject != CryptoObjectType::kUnknown)</tt> and an actual object type differs from the expected
    ///       one then this method fails.
    ///       If the @c serialized contains incorrect data then this method fails
    /// @param[out] container  the IOInterface for storing of the imported object
    /// @param[in] serialized  the memory region that contains a securely serialized object that should be imported to
    ///            the IOInterface
    /// @param[in] expectedObject  the expected object type (default value @c CryptoObjectType::kUnknown means without check)

    /// @error CryptoErrorDomain::kUnexpectedValue  if the @c serialized contains incorrect data
    /// @error CryptoErrorDomain::kBadObjectType  if <tt>(expectedObject != CryptoObjectType::kUnknown)</tt>,
    ///                but the actual object type differs from the expected one
    /// @error CryptoErrorDomain::kInsufficientCapacity  if capacity of the @c container is not enough to
    ///                save the de-serialized object
    /// @error CryptoErrorDomain::kModifiedResource if the underlying resource has been modified after 
    ///                 the IOInterface has been opened, i.e., the IOInterface has been invalidated.
    /// @error CryptoErrorDomain::kUnreservedResource  if the IOInterface is not opened writable.
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<void> ImportPublicObject(IOInterface& container,
        ReadOnlyMemRegion serialized,
        CryptoObjectType expectedObject = CryptoObjectType::kUndefined
    ) noexcept = 0;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /// @traceid{SWS_CRYPT_20733}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02001}
    /// @uptrace{RS_CRYPTO_02002}
    /// @uptrace{RS_CRYPTO_02005}
    /// @uptrace{RS_CRYPTO_02006}
    /// @brief Load any crypto object from the IOInterface provided.
    /// @param[in] container  the IOInterface that contains the crypto object for loading
    /// @returns unique smart pointer to the created object
    /// @error CryptoErrorDomain::kEmptyContainer  if the container is empty
    /// @error CryptoErrorDomain::kResourceFault  if the container content is damaged
    /// @error CryptoErrorDomain::kModifiedResource if the underlying resource has been modified after 
    ///                 the IOInterface has been opened, i.e., the IOInterface has been invalidated.
    /// @error CryptoErrorDomain::kIncompatibleObject  if the underlying resource belongs to another, 
    ///                 incompatible CryptoProvider
    /// @note This method is one of the "binding" methods between a CryptoProvider and the %Key Storage Provider.
    /// @threadsafety{Thread-safe}
    virtual ara::core::Result<CryptoObject::Uptrc> LoadObject(const IOInterface& container
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_20762}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02001}
    /// @uptrace{RS_CRYPTO_02002}
    /// 
    /// @brief Load a symmetric key from the IOInterface provided.
    /// @param[in] container  the IOInterface that contains the crypto object for loading
    /// @returns unique smart pointer to the SymmetricKey
    /// @error CryptoErrorDomain::kEmptyContainer  if the container is empty
    /// @error CryptoErrorDomain::kResourceFault  if the container content is damaged
    /// @error CryptoErrorDomain::kModifiedResource if the underlying resource has been modified after 
    ///                 the IOInterface has been opened, i.e., the IOInterface has been invalidated.
    /// @error CryptoErrorDomain::kIncompatibleObject  if the underlying resource belongs to another, 
    ///                 incompatible CryptoProvider
    virtual ara::core::Result<SymmetricKey::Uptrc> LoadSymmetricKey(const IOInterface& container
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_20763}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02001}
    /// @uptrace{RS_CRYPTO_02002}
    /// 
    /// @brief Load a public key from the IOInterface provided.
    /// @param[in] container  the IOInterface that contains the crypto object for loading
    /// @returns unique smart pointer to the PublicKey
    /// @error CryptoErrorDomain::kEmptyContainer  if the container is empty
    /// @error CryptoErrorDomain::kResourceFault  if the container content is damaged
    /// @error CryptoErrorDomain::kModifiedResource if the underlying resource has been modified after 
    ///                 the IOInterface has been opened, i.e., the IOInterface has been invalidated.
    /// @error CryptoErrorDomain::kIncompatibleObject  if the underlying resource belongs to another, 
    ///                 incompatible CryptoProvider
    virtual ara::core::Result<PublicKey::Uptrc> LoadPublicKey(const IOInterface& container
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_20764}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02001}
    /// @uptrace{RS_CRYPTO_02002}
    /// 
    /// @brief Load a private key from the IOInterface provided.
    /// @param[in] container  the IOInterface that contains the crypto object for loading
    /// @returns unique smart pointer to the PrivateKey
    /// @error CryptoErrorDomain::kEmptyContainer  if the container is empty
    /// @error CryptoErrorDomain::kResourceFault  if the container content is damaged
    /// @error CryptoErrorDomain::kModifiedResource if the underlying resource has been modified after 
    ///                 the IOInterface has been opened, i.e., the IOInterface has been invalidated.
    /// @error CryptoErrorDomain::kIncompatibleObject  if the underlying resource belongs to another, 
    ///                 incompatible CryptoProvider    
    virtual ara::core::Result<PrivateKey::Uptrc> LoadPrivateKey(const IOInterface& container
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_20765}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02001}
    /// @uptrace{RS_CRYPTO_02002}
    /// 
    /// @brief Load secret seed from the IOInterface provided.
    /// @param[in] container  the IOInterface that contains the crypto object for loading
    /// @returns unique smart pointer to the SecretSeed
    /// @error CryptoErrorDomain::kEmptyContainer  if the container is empty
    /// @error CryptoErrorDomain::kResourceFault  if the container content is damaged
    /// @error CryptoErrorDomain::kModifiedResource if the underlying resource has been modified after 
    ///                 the IOInterface has been opened, i.e., the IOInterface has been invalidated.
    /// @error CryptoErrorDomain::kIncompatibleObject  if the underlying resource belongs to another, 
    ///                 incompatible CryptoProvider
    virtual ara::core::Result<SecretSeed::Uptrc> LoadSecretSeed(const IOInterface& container
    ) noexcept = 0;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    /// @traceid{SWS_CRYPT_20741}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02206}
    /// @brief Create a Random Number Generator (RNG) context.
    /// @param[in] algId  identifier of target RNG algorithm. If no algId is given, the default RNG is returned
    /// @param[in] initialize  indicates whether the returned context shall be initialized (i.e., seeded) by the stack
    /// @returns unique smart pointer to the created RNG context
    /// @error CryptoErrorDomain::kUnknownIdentifier  if @c algId argument has an unsupported value or 
    ///                if <tt>(algId == kAlgIdDefault)</tt> and the CryptoProvider does not provide any 
    ///                RandomGeneratorCtx
    /// @error CryptoErrorDomain::kBusyResource  if <tt>(initialize == true)</tt> but the context currently 
    ///                cannot be seeded (e.g., due to a lack of entropy)
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<RandomGeneratorCtx::Uptr> CreateRandomGeneratorCtx(AlgId algId = kAlgIdDefault,
        bool initialize = true
    ) noexcept = 0;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /// @traceid{SWS_CRYPT_20742}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02201}
    /// @brief Create a symmetric block cipher context.
    /// @param[in] algId  identifier of the target crypto algorithm
    /// @returns unique smart pointer to the created context
    /// @error CryptoErrorDomain::kUnknownIdentifier  if @c algId argument has an unsupported value
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<SymmetricBlockCipherCtx::Uptr> CreateSymmetricBlockCipherCtx(AlgId algId
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_20743}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02104}
    /// @uptrace{RS_CRYPTO_02208}
    /// @brief Create a symmetric key-wrap algorithm context.
    /// @param[in] algId  identifier of the target crypto algorithm
    /// @returns unique smart pointer to the created context
    /// @error CryptoErrorDomain::kInvalidArgument  if @c algId argument specifies a crypto algorithm
    ///                different from symmetric key-wrapping
    /// @error CryptoErrorDomain::kUnknownIdentifier  if @c algId argument has an unsupported value
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<SymmetricKeyWrapperCtx::Uptr> CreateSymmetricKeyWrapperCtx(AlgId algId
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_20744}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02201}
    /// @brief Create a symmetric stream cipher context.
    /// @param[in] algId  identifier of the target crypto algorithm
    /// @returns unique smart pointer to the created context
    /// @error CryptoErrorDomain::kInvalidArgument  if @c algId argument specifies a crypto algorithm
    ///                different from symmetric stream cipher
    /// @error CryptoErrorDomain::kUnknownIdentifier  if @c algId argument has an unsupported value
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<StreamCipherCtx::Uptr> CreateStreamCipherCtx(AlgId algId
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_20745}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02207}
    /// @uptrace{RS_AP_00144}
    /// @brief Create a symmetric authenticated cipher context.
    /// @param[in] algId  identifier of the target crypto algorithm
    /// @returns unique smart pointer to the created context
    /// @error CryptoErrorDomain::kInvalidArgument  if @c algId argument specifies a crypto algorithm
    ///                different from symmetric authenticated stream cipher
    /// @error CryptoErrorDomain::kInvalidArgument
    /// @error CryptoErrorDomain::kUnknownIdentifier  if @c algId argument has an unsupported value
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<AuthCipherCtx::Uptr> CreateAuthCipherCtx(AlgId algId
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_20746}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02203}
    /// @uptrace{RS_AP_00144}
    /// @brief Create a symmetric message authentication code context.
    /// @param[in] algId  identifier of the target crypto algorithm
    /// @returns unique smart pointer to the created context
    /// @error CryptoErrorDomain::kInvalidArgument  if @c algId argument specifies a crypto algorithm
    ///                different from symmetric message authentication code
    /// @error CryptoErrorDomain::kUnknownIdentifier  if @c algId argument has an unsupported value
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<MessageAuthnCodeCtx::Uptr> CreateMessageAuthCodeCtx(AlgId algId
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_20747}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02205}
    /// @uptrace{RS_AP_00144}
    /// @brief Create a hash function context.
    /// @param[in] algId  identifier of the target crypto algorithm
    /// @returns unique smart pointer to the created context
    /// @error CryptoErrorDomain::kInvalidArgument  if @c algId argument specifies a crypto algorithm
    ///                different from hash function
    /// @error CryptoErrorDomain::kUnknownIdentifier  if @c algId argument has an unsupported value
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<HashFunctionCtx::Uptr> CreateHashFunctionCtx(AlgId algId
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_20748}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02103}
    /// @uptrace{RS_AP_00144}
    /// @brief Create a key derivation function context.
    /// @param[in] algId  identifier of the target crypto algorithm
    /// @returns unique smart pointer to the created context
    /// @error CryptoErrorDomain::kInvalidArgument  if @c algId argument specifies a crypto algorithm
    ///                different from key derivation function
    /// @error CryptoErrorDomain::kUnknownIdentifier  if @c algId argument has an unsupported value
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<KeyDerivationFunctionCtx::Uptr> CreateKeyDerivationFunctionCtx(AlgId algId
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_20750}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02202}
    /// @uptrace{RS_AP_00144}
    /// @brief Create an encryption public key context.
    /// @param[in] algId  identifier of the target asymmetric encryption/decryption algorithm
    /// @returns unique smart pointer to the created context
    /// @error CryptoErrorDomain::kInvalidArgument  if @c algId argument specifies a crypto algorithm
    ///                different from asymmetric encryption/decryption
    /// @error CryptoErrorDomain::kUnknownIdentifier  if @c algId argument has an unsupported value
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<EncryptorPublicCtx::Uptr> CreateEncryptorPublicCtx(AlgId algId
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_20751}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02202}
    /// @uptrace{RS_AP_00144}
    /// @brief Create a decryption private key context.
    /// @param[in] algId  identifier of the target asymmetric encryption/decryption algorithm
    /// @returns unique smart pointer to the created context
    /// @error CryptoErrorDomain::kInvalidArgument  if @c algId argument specifies a crypto algorithm
    ///                different from asymmetric encryption/decryption
    /// @error CryptoErrorDomain::kUnknownIdentifier  if @c algId argument has an unsupported value
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<DecryptorPrivateCtx::Uptr> CreateDecryptorPrivateCtx(AlgId algId
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_20752}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02104}
    /// @uptrace{RS_CRYPTO_02209}
    /// @uptrace{RS_AP_00144}
    /// @brief Create a key-encapsulator public key context of a Key Encapsulation Mechanism (KEM).
    /// @param[in] algId  identifier of the target KEM crypto algorithm
    /// @returns unique smart pointer to the created context
    /// @error CryptoErrorDomain::kInvalidArgument  if @c algId argument specifies a crypto algorithm
    ///                different from asymmetric KEM
    /// @error CryptoErrorDomain::kUnknownIdentifier  if @c algId argument has an unsupported value
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<KeyEncapsulatorPublicCtx::Uptr> CreateKeyEncapsulatorPublicCtx(AlgId algId
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_20753}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02104}
    /// @uptrace{RS_CRYPTO_02209}
    /// @uptrace{RS_AP_00144}
    /// @brief Create a key-decapsulator private key context of a Key Encapsulation Mechanism (KEM).
    /// @param[in] algId  identifier of the target KEM crypto algorithm
    /// @returns unique smart pointer to the created context
    /// @error CryptoErrorDomain::kInvalidArgument  if @c algId argument specifies a crypto algorithm
    ///                different from asymmetric KEM
    /// @error CryptoErrorDomain::kUnknownIdentifier  if @c algId argument has an unsupported value
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<KeyDecapsulatorPrivateCtx::Uptr> CreateKeyDecapsulatorPrivateCtx(AlgId algId
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_20754}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02202}
    /// @uptrace{RS_CRYPTO_02204}
    /// @uptrace{RS_AP_00144}
    /// @brief Create a signature encoding private key context.
    /// @param[in] algId  identifier of the target asymmetric crypto algorithm
    /// @returns unique smart pointer to the created context
    /// @error CryptoErrorDomain::kInvalidArgument  if @c algId argument specifies a crypto algorithm
    ///                different from asymmetric signature encoding with message recovery
    /// @error CryptoErrorDomain::kUnknownIdentifier  if @c algId argument has an unsupported value
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<SigEncodePrivateCtx::Uptr> CreateSigEncodePrivateCtx(AlgId algId
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_20755}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02202}
    /// @uptrace{RS_CRYPTO_02204}
    /// @uptrace{RS_AP_00144}
    /// @brief Create a message recovery public key context.
    /// @param[in] algId  identifier of the target asymmetric crypto algorithm
    /// @returns unique smart pointer to the created context
    /// @error CryptoErrorDomain::kInvalidArgument  if @c algId argument specifies a crypto algorithm
    ///                different from asymmetric signature encoding with message recovery
    /// @error CryptoErrorDomain::kUnknownIdentifier  if @c algId argument has an unsupported value
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<MsgRecoveryPublicCtx::Uptr> CreateMsgRecoveryPublicCtx(AlgId algId
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_20756}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02204}
    /// @uptrace{RS_AP_00144}
    /// @brief Create a signature private key context.
    /// @param[in] algId  identifier of the target signature crypto algorithm
    /// @returns unique smart pointer to the created context
    /// @error CryptoErrorDomain::kInvalidArgument  if @c algId argument specifies a crypto algorithm
    ///                different from private key signature
    /// @error CryptoErrorDomain::kUnknownIdentifier  if @c algId argument has an unsupported value
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<SignerPrivateCtx::Uptr> CreateSignerPrivateCtx(AlgId algId
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_20757}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02204}
    /// @uptrace{RS_AP_00144}
    /// @brief Create a signature verification public key context.
    /// @param[in] algId  identifier of the target signature crypto algorithm
    /// @returns unique smart pointer to the created context
    /// @error CryptoErrorDomain::kInvalidArgument  if @c algId argument specifies a crypto algorithm
    ///                different from public key signature verification
    /// @error CryptoErrorDomain::kUnknownIdentifier  if @c algId argument has an unsupported value
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<VerifierPublicCtx::Uptr> CreateVerifierPublicCtx(AlgId algId
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_20758}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02104}
    /// @uptrace{RS_AP_00144}
    /// @brief Create a key-agreement private key context.
    /// @param[in] algId  identifier of the target key-agreement crypto algorithm
    /// @returns unique smart pointer to the created context
    /// @error CryptoErrorDomain::kInvalidArgument  if @c algId argument specifies a crypto algorithm
    ///                different from key-agreement
    /// @error CryptoErrorDomain::kUnknownIdentifier  if @c algId argument has an unsupported value
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<KeyAgreementPrivateCtx::Uptr> CreateKeyAgreementPrivateCtx(AlgId algId
    ) noexcept = 0;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /// @traceid{SWS_CRYPT_20760}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02005}
    /// @uptrace{RS_CRYPTO_02006}
    /// @uptrace{RS_AP_00144}
    /// @brief Construct @c Signature object from directly provided components of a digital signature/MAC or
    ///           authenticated encryption (AE/AEAD).
	///       All integers inside a digital signature BLOB value are always presented in Big Endian bytes order
    ///       (i.e. MSF - Most Significant byte First).
    /// @param[in] signAlgId  identifier of an applied signature/MAC/AE/AEAD crypto algorithm
    /// @param[in] value  raw BLOB value of the signature/MAC
    /// @param[in] key  symmetric or asymmetric key (according to @c signAlgId) applied for the sign or MAC/AE/AEAD
    ///                 operation
    /// @param[in] hashAlgId  identifier of a hash function algorithm applied together with the signature algorithm
    /// @returns unique smart pointer to the created @c Signature object

    /// @error CryptoErrorDomain::kUnknownIdentifier  if @c signAlgId or @c hashAlgId arguments have
    ///                unsupported values
    /// @error CryptoErrorDomain::kInvalidArgument  if @c signAlgId or @c hashAlgId arguments specify
    ///                crypto algorithms different from the signature/MAC/AE/AEAD and message digest respectively
    /// @error CryptoErrorDomain::kIncompatibleArguments  if @c signAlgId and @c hashAlgId arguments specify
    ///                incompatible algorithms (if @c signAlgId includes hash function specification)
    ///                or if a crypto primitive associated with the @c key argument is incompatible with provided
    ///                @c signAlgId or @c hashAlgId arguments
    /// @error CryptoErrorDomain::kInvalidInputSize  if the @c value argument has invalid size
    ///                (i.e. incompatible with the @c signAlgId argument)
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<Signature::Uptrc> CreateSignature(AlgId signAlgId
        , ReadOnlyMemRegion value
        , const RestrictedUseObject& key
        , AlgId hashAlgId = kAlgIdNone
    ) noexcept = 0;

    /// @traceid{SWS_CRYPT_20761}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02005}
    /// @uptrace{RS_CRYPTO_02006}
    /// @uptrace{RS_AP_00144}
    /// @brief Construct @c Signature object from directly provided components of a hash digest.
    /// @param[in] hashAlgId  identifier of an applied hash function crypto algorithm
    /// @param[in] value  raw BLOB value of the hash digest
    /// @returns unique smart pointer to the created @c Signature object
    /// @error CryptoErrorDomain::kUnknownIdentifier  if @c hashAlgId argument has unsupported value
    /// @error CryptoErrorDomain::kInvalidArgument  if @c hashAlgId argument specifies
    ///                crypto algorithm different from a hash function
    /// @error CryptoErrorDomain::kInvalidInputSize  if the @c value argument has invalid size
    ///                (i.e. incompatible with the @c hashAlgId argument)
    /// @threadsafety{Thread-safe}
    
    virtual ara::core::Result<Signature::Uptrc> CreateHashDigest(AlgId hashAlgId
        , ReadOnlyMemRegion value
    ) noexcept = 0;
};

}  // namespace cryp
}  // namespace crypto
}  // namespace ara

#endif  // ARA_CRYPTO_CRYP_CRYPTO_PROVIDER_H_
