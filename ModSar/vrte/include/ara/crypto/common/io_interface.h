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
/// @brief Adaptive Autosar Crypto Stack. Common API. TrustedContainer interface definition.

#ifndef ARA_CRYPTO_COMMON_IO_INTERFACE_H_
#define ARA_CRYPTO_COMMON_IO_INTERFACE_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/crypto/common/base_id_types.h"
#include "ara/crypto/common/crypto_object_uid.h"
#include <cstdint>

namespace ara
{
namespace crypto
{
//- @interface IOInterface
///
/// @traceid{SWS_CRYPT_10800}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02004}
/// @brief Formal interface of an IOInterface is used for saving and loading of security objects.
///       Actual saving and loading should be implemented by internal methods known to a trusted
///       pair of Crypto Provider and Storage Provider. Each object should be uniquely identified by
///       its type and Crypto Object Unique Identifier (@b COUID). This interface suppose that
///       objects in the container are compressed i.e. have a minimal size optimized for
///
class IOInterface
{
public:
    /// @traceid{SWS_CRYPT_10810}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Destructor.
    virtual ~IOInterface() noexcept = default;

    /// @traceid{SWS_CRYPT_30202}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Copy-assign another IOInterface to this instance.
    /// @param other  the other instance
    /// @returns *this, containing the contents of @a other
    IOInterface& operator=(const IOInterface& other) = default;

    /// @traceid{SWS_CRYPT_30203}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Move-assign another IOInterface to this instance.
    /// @param other  the other instance
    /// @returns *this, containing the contents of @a other
    IOInterface& operator=(IOInterface&& other) = default;

    IOInterface(const IOInterface& other) = default;
    IOInterface(IOInterface&& other) = default;
    IOInterface() = default;

    /// @traceid{SWS_CRYPT_10801}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02109}
    /// @brief Unique smart pointer of the interface.
    using Uptr = std::unique_ptr<IOInterface>;

    /// @traceid{SWS_CRYPT_10802}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02109}
    /// @brief Unique smart pointer of the constant interface.
    using Uptrc = std::unique_ptr<const IOInterface>;

    /// @traceid{SWS_CRYPT_10811}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Return @a COUID of an object stored to this IOInterface.
    ///       If the container is empty then this method returns @c CryptoObjectType::KUndefined.
    ///       Unambiguous identification of a crypto object requires both components: @c
    ///       CryptoObjectUid and
    ///       @c CryptoObjectType.
    /// @param[out] objectUid @a COUID of an object stored in the container
    /// @returns type of the content stored in the container
    /// @threadsafety{Thread-safe}
    virtual CryptoObjectUid GetObjectId() const noexcept = 0;

    /// @traceid{SWS_CRYPT_10812}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02110}
    /// @brief Return the CryptoObjectType of the object referenced by this IOInterface.
    /// @returns the CryptoObjectType stored inside the referenced resource
    /// @threadsafety{Thread-safe}
    virtual CryptoObjectType GetCryptoObjectType() const noexcept = 0;

    /// @traceid{SWS_CRYPT_10813}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02110}
    /// @brief Return capacity of the underlying resource.
    /// @returns capacity of the underlying buffer of this IOInterface (in bytes)
    /// @threadsafety{Thread-safe}
    virtual std::size_t GetCapacity() const noexcept = 0;

    /// @traceid{SWS_CRYPT_10814}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02109}
    /// @brief Return volatility of the the underlying buffer of this IOInterface.
    ///      A "session" object can be stored to a "volatile" container only.
    ///      A content of a "volatile" container will be destroyed together with the interface
    ///      instance.
    /// @returns @c true if the container has a volatile nature (i.e. "temporary" or "in RAM") or @c
    /// false otherwise
    /// @threadsafety{Thread-safe}
    virtual bool IsVolatile() const noexcept = 0;

    /// @traceid{SWS_CRYPT_10815}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02109}
    /// @brief Return the "session" (or "temporary") attribute of an object as set e.g. by
    /// KeyDerivationFunctionCtx::DeriveKey().
    ///       A "session" object can be stored to a VolatileTrustedContainer only!
    ///       If this IOInterface is linked to a KeySlot this returns always false.
    /// @returns @c true if the object referenced by this IOInterface has set the "session"
    /// attribute
    /// @threadsafety{Thread-safe}
    virtual bool IsObjectSession() const noexcept = 0;

    /// @traceid{SWS_CRYPT_10816}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02109}
    /// @brief Return the "exportable" attribute of an object stored to the container.
    ///       The exportability of an object doesn't depend from the volatility of its container.
    /// @returns @c true if an object stored to the container has set the "exportable" attribute
    /// @threadsafety{Thread-safe}
    virtual bool IsObjectExportable() const noexcept = 0;

    /// @traceid{SWS_CRYPT_10817}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02109}
    /// @brief Return size of an object payload stored in the underlying buffer of this IOInterface.
    ///       If the container is empty then this method returns 0.
    ///       Returned value does not take into account the object's meta-information properties,
    ///       but their size is fixed and common for all crypto objects independently from their
    ///       actual type. space for an object's meta-information automatically, according to their
    ///       implementation details.
    /// @returns size of an object payload stored in the underlying buffer of this IOInterface (in
    /// bytes)
    /// @threadsafety{Thread-safe}
    virtual std::size_t GetPayloadSize() const noexcept = 0;

    /// @traceid{SWS_CRYPT_10818}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @uptrace{RS_CRYPTO_02110}
    /// @brief Return content type restriction of this IOInterface. If
    /// KeySlotPrototypeProps::mAllowContentTypeChange==TRUE, then kUndefined shall be returned.
    ///  If a container has a type restriction different from @c CryptoObjectType::kUndefined then
    ///  only objects of the
    ///       mentioned type can be saved to this container.
    ///       Volatile containers don't have any content type restrictions.
    /// @returns an object type of allowed content (@c CryptoObjectType::kUndefined means without
    /// restriction)
    /// @threadsafety{Thread-safe}
    virtual CryptoObjectType GetTypeRestriction() const noexcept = 0;

    /// @traceid{SWS_CRYPT_10819}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02008}
    /// @brief Return actual allowed key/seed usage flags defined by the key slot prototype for this
    /// "Actor"
    ///           and current content of the container.
    ///       Volatile containers don't have any prototyped restrictions, but can have restrictions
    ///       defined at run-time for a current instance of object. A value returned by this method
    ///       is bitwise AND of the common usage flags defined at run-time and the usage flags
    ///       defined by the UserPermissions prototype for current "Actor". This method is
    ///       especially useful for empty permanent prototyped containers.
    /// @returns allowed key/seed usage flags
    /// @threadsafety{Thread-safe}
    virtual AllowedUsageFlags GetAllowedUsage() const noexcept = 0;

    /// @traceid{SWS_CRYPT_10821}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Get whether the underlying KeySlot is writable - if this IOInterface is linked to a
    /// VolatileTrustedContainer always return true.
    /// @returns true if the underlying resource can be written
    /// @threadsafety{Thread-safe}
    virtual bool IsWritable() const noexcept = 0;

    /// @traceid{SWS_CRYPT_10822}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Get vendor specific ID of the primitive.
    /// @returns the binary Crypto Primitive ID
    /// @threadsafety{Thread-safe}
    virtual CryptoAlgId GetPrimitiveId() const noexcept = 0;

    /// @traceid{SWS_CRYPT_10823}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02004}
    /// @brief Get whether the underlying KeySlot is valid. An IOInterface is invalidated if the
    /// underlying resource has been modified after the IOInterface has been opened.
    /// @returns true if the underlying resource can be valid, false otherwise
    /// @threadsafety{Thread-safe}
    virtual bool IsValid() const noexcept = 0;
};

} // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_COMMON_IO_INTERFACE_H_
