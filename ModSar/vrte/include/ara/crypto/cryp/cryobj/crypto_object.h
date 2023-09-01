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
/// @brief Adaptive Autosar Crypto Stack. Cryptographic API. CryptoObject interface definition.

#ifndef ARA_CRYPTO_CRYP_CRYPTO_OBJECT_H_
#define ARA_CRYPTO_CRYP_CRYPTO_OBJECT_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/common/crypto_error_domain.h"
#include "ara/crypto/common/io_interface.h"
#include <memory>

#include "ara/crypto/common/base_id_types.h"
#include "ara/crypto/common/crypto_object_uid.h"
#include "ara/crypto/cryp/cryobj/crypto_primitive_id.h"

#include "ara/core/result.h"

namespace ara
{
namespace crypto
{
namespace cryp
{
//- @interface CryptoObject
///
/// @traceid{SWS_CRYPT_20500}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02005}
/// @brief A common interface for all cryptograhic objects recognizable by the Crypto Provider.
///       This interface (or any its derivative) represents a non-mutable (after completion) object
///       loadable to a temporary transformation context.

class CryptoObject
{
public:
    /// @traceid{SWS_CRYPT_20501}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02005}
    /// @brief Unique smart pointer of the interface.
    using Uptr = std::unique_ptr<CryptoObject>;

    /// @traceid{SWS_CRYPT_20502}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02005}
    /// @brief Unique smart pointer of the constant interface.
    using Uptrc = std::unique_ptr<const CryptoObject>;

    /// @traceid{SWS_CRYPT_20503}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02005}
    /// @brief Destructor.
    virtual ~CryptoObject() noexcept = default;

    /// @traceid{SWS_CRYPT_30208}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02009}
    /// @brief Copy-assign another CryptoObject to this instance.
    /// @param other  the other instance
    /// @returns *this, containing the contents of @a other
    CryptoObject& operator=(const CryptoObject& other) = default;

    /// @traceid{SWS_CRYPT_30209}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Move-assign another CryptoObject to this instance.
    /// @param other  the other instance
    /// @returns *this, containing the contents of @a other
    CryptoObject& operator=(CryptoObject&& other) = default;

    CryptoObject(const CryptoObject& other) = default;
    CryptoObject(CryptoObject&& other) = default;
    CryptoObject() = default;

    /// @traceid{SWS_CRYPT_20504}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02005}
    /// @brief Unique identifier of this CryptoObject.
    struct COIdentifier
    {
        /// @traceid{SWS_CRYPT_20506}@tracestatus{draft}
        /// @uptrace{RS_CRYPTO_02005}
        /// @brief type of objext
        CryptoObjectType mCOType;

        /// @traceid{SWS_CRYPT_20507}@tracestatus{draft}
        /// @uptrace{RS_CRYPTO_02005}
        /// @brief object identifier
        CryptoObjectUid mCouid;

        // @brief crypto object identifier
        uint32_t mHandleId;
    };

    /// @traceid{SWS_CRYPT_20505}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02005}
    /// @brief Return the CryptoPrimitivId of this CryptoObject.
    virtual CryptoPrimitiveId::Uptr GetCryptoPrimitiveId() const noexcept = 0;

    /// @traceid{SWS_CRYPT_20512}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02003}
    /// @brief Return the "session" (or "temporary") attribute of the object.
    ///      A temporary object cannot be saved to a persistent storage location pointed to by an
    ///      IOInterface! A temporary object will be securely destroyed together with this interface
    ///      instance! A non-session object must have an assigned @a COUID (see @c GetObjectId()).
    /// @returns @c true if the object is temporay (i.e. its life time is limited by the current
    /// session only)
    /// @threadsafety{Thread-safe}
    virtual bool IsSession() const noexcept = 0;

    /// @traceid{SWS_CRYPT_20513}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02005}
    /// @brief Get the exportability attribute of the crypto object.
    ///     An exportable object must have an assigned @a COUID (see @c GetObjectId()).
    /// @returns @c true if the object is exportable (i.e. if it can be exported outside the trusted
    /// environment
    ///          of the Crypto Provider)
    /// @threadsafety{Thread-safe}
    virtual bool IsExportable() const noexcept = 0;

    /// @traceid{SWS_CRYPT_20514}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02005}
    /// @brief Return the object's COIdentifier, which includes the object's type and UID.
    ///      An object that has no assigned @a COUID cannot be (securely) serialized / exported or
    ///      saved to a
    ///       non-volatile storage.
    ///      An object should not have a @a COUID if it is session and non-exportable simultaneously
    ///      A few related objects of different types can share a single @a COUID (e.g. private and
    ///      public keys),
    ///       but a combination of @a COUID and object type must be unique always!
    ///
    /// @returns the object's COIdentifier including the object's type and COUID (or an empty COUID,
    /// if this object is not identifiable).
    ///
    ///
    /// @threadsafety{Thread-safe}
    virtual COIdentifier GetObjectId() const noexcept = 0;

    /// @traceid{SWS_CRYPT_20515}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02005}
    /// @brief Return the COIdentifier of the CryptoObject that this CryptoObject depends on.
    ///       For signatures objects this method @b must return a reference to correspondent
    ///       signature verification public key! Unambiguous identification of a CryptoObject
    ///       requires both components: @c CryptoObjectUid and @c CryptoObjectType.
    ///
    /// @returns target COIdentifier of the existing dependence or @c CryptoObjectType::kUnknown and
    /// empty COUID,
    ///          if the current object does not depend on another CryptoObject
    ///
    /// @threadsafety{Thread-safe}
    virtual COIdentifier HasDependence() const noexcept = 0;

    /// @traceid{SWS_CRYPT_20516}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02309}
    /// @brief Return actual size of the object's payload.
    ///       Returned value always must be less than or equal to the maximum payload size expected
    ///       for this primitive and object type, it is available via call:
    ///       <tt>MyProvider().GetPayloadStorageSize(GetObjectType(),
    ///       GetPrimitiveId()).Value();</tt> Returned value does not take into account the object's
    ///       meta-information properties, but their size is fixed and common for all crypto objects
    ///       independently from their actual type. During an allocation of a @c TrustedContainer,
    ///       Crypto Providers (and %Key Storage Providers) reserve space for an object's
    ///       meta-information automatically, according to their implementation details.
    /// @returns size in bytes of the object's payload required for its storage
    /// @threadsafety{Thread-safe}
    virtual std::size_t GetPayloadSize() const noexcept = 0;

    /// @traceid{SWS_CRYPT_20517}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Save itself to provided IOInterface
    /// A CryptoObject with property "session" cannot be saved in a KeySlot.
    /// @param[in] container IOInterface representing underlying storage
    /// @error SecurityErrorDomain::kIncompatibleObject  if the object is "session", but the
    /// IOInterface
    ///         represents a KeySlot.
    /// @error SecurityErrorDomain::kContentRestrictions  if the object doesn't satisfy the slot
    /// restrictions
    ///         (@see keys::KeySlotPrototypeProps)
    /// @error SecurityErrorDomain::kInsufficientCapacity  if the capacity of the target container
    /// is not
    ///                enough, i.e. if <tt>(container.Capacity() < this->StorageSize())</tt>
    /// @error SecurityErrorDomain::kModifiedResource if the underlying resource has been modified
    /// after
    ///                 the IOInterface has been opened, i.e., the IOInterface has been invalidated.
    /// @error SecurityErrorDomain::kUnreservedResource  if the IOInterface is not opened writeable.
    /// @threadsafety{Thread-safe}
    virtual ara::core::Result<void> Save(IOInterface& container) const noexcept = 0;

    /// @traceid{SWS_CRYPT_20518}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02005}
    /// @brief Downcast and move unique smart pointer from the generic @c CryptoObject interface to
    /// concrete derived
    ///           object.
    /// @tparam ConcreteObject  target type (derived from @c CryptoObject) for downcasting
    /// @param[in] object  unique smart pointer to the constant generic @c CryptoObject interface
    /// @returns unique smart pointer to downcasted constant interface of specified derived type
    /// @error SecurityErrorDomain::kBadObjectType  if an actual type of the @c object is not the
    /// specified
    ///                @c ConcreteObject
    /// @threadsafety{Thread-safe}
    template<class ConcreteObject>
    static ara::core::Result<typename ConcreteObject::Uptrc>
    Downcast(CryptoObject::Uptrc&& object) noexcept
    {
        using DstValType = typename ConcreteObject::Uptrc;
        if (object)
        {
            const CryptoObjectType kObjType = object->GetObjectId().mCOType;
            if (kObjType != ConcreteObject::kObjectType)
            {
                ara::core::ErrorDomain::SupportDataType data =
                    (static_cast<ara::core::ErrorDomain::SupportDataType>(kObjType) << 16) |
                    static_cast<ara::core::ErrorDomain::SupportDataType>(
                        ConcreteObject::kObjectType);
                return ara::core::Result<DstValType>::FromError(
                    ara::crypto::MakeErrorCode(CryptoErrc::kBadObjectType, data));
            }
        }
        return DstValType{static_cast<const ConcreteObject*>(object.release())};
    }
};

} // namespace cryp
} // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_CRYP_CRYPTO_OBJECT_H_
