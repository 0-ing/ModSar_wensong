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
/// @brief Adaptive Autosar Crypto Stack. Common API. Errors definition.

#ifndef ARA_CRYPTO_COMMON_CRYPTO_ERROR_DOMAIN_H_
#define ARA_CRYPTO_COMMON_CRYPTO_ERROR_DOMAIN_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/core/error_code.h"
#include "ara/core/exception.h"

namespace ara
{
namespace crypto
{

///
/// @traceid{SWS_CRYPT_10099}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02310}
/// @brief Enumeration of all Crypto Error Code values that may be reported by @c ara::crypto.
enum class CryptoErrc : ara::core::ErrorDomain::CodeType
{
    ///No error
    kNoError = 0x0000,
    /// Reserved (a multiplier of error class IDs)
    kErrorClass = 0x1000000,
    /// Reserved (a multiplier of error sub-class IDs)
    kErrorSubClass = 0x10000,
    /// Reserved (a multiplier of error sub-sub-class IDs)
    kErrorSubSubClass = 0x100,

    /// ResourceException: Generic resource fault!
    kResourceFault = 1 * kErrorClass,
    /// ResourceException: Specified resource is busy!
    kBusyResource = kResourceFault + 1,
    /// ResourceException: Insufficient capacity of specified resource!
    kInsufficientResource = kResourceFault + 2,
    /// ResourceException: Specified resource was not reserved!
    kUnreservedResource = kResourceFault + 3,
    /// ResourceException: Specified resource has been modified!
    kModifiedResource = kResourceFault + 4,

	/// LogicException: Generic logic fault!
    kLogicFault = 2 * kErrorClass,
    /// InvalidArgumentException: An invalid argument value is provided!
    kInvalidArgument = kLogicFault + 1 * kErrorSubClass,
    /// InvalidArgumentException: Unknown identifier is provided!
    kUnknownIdentifier = kInvalidArgument + 1,
    /// InvalidArgumentException: Insufficient capacity of the output buffer!
    kInsufficientCapacity = kInvalidArgument + 2,
    /// InvalidArgumentException: Invalid size of an input buffer!
    kInvalidInputSize = kInvalidArgument + 3,
    /// InvalidArgumentException: Provided values of arguments are incompatible!
    kIncompatibleArguments = kInvalidArgument + 4,
    /// InvalidArgumentException: Input and output buffers are intersect!
    kInOutBuffersIntersect = kInvalidArgument + 5,
    /// InvalidArgumentException: Provided value is below the lower boundary!
    kBelowBoundary = kInvalidArgument + 6,
    /// InvalidArgumentException: Provided value is above the upper boundary!
    kAboveBoundary = kInvalidArgument + 7,
	/// AuthTagNotValidException: Provided authentication-tag cannot be verified!
	kAuthTagNotValid = kInvalidArgument + 8,

    /// UnsupportedException: Unsupported request (due to limitations of the implementation)!
    kUnsupported = kInvalidArgument + 1 * kErrorSubSubClass,

    /// InvalidUsageOrderException: Invalid usage order of the interface!
    kInvalidUsageOrder = kLogicFault + 2 * kErrorSubClass,
    /// InvalidUsageOrderException: Context of the interface was not initialized!
    kUninitializedContext = kInvalidUsageOrder + 1,
    /// InvalidUsageOrderException: Data processing was not started yet!
    kProcessingNotStarted = kInvalidUsageOrder + 2,
    /// InvalidUsageOrderException: Data processing was not finished yet!
    kProcessingNotFinished = kInvalidUsageOrder + 3,

    /// RuntimeException: Generic runtime fault!
    kRuntimeFault = 3 * kErrorClass,
    /// RuntimeException: Unsupported serialization format for this object type!
    kUnsupportedFormat = kRuntimeFault + 1,
    /// RuntimeException: Operation is prohibitted due to a risk of a brute force attack!
    kBruteForceRisk = kRuntimeFault + 2,
    /// RuntimeException: The operation violates content restrictions of the target container!
    kContentRestrictions = kRuntimeFault + 3,
    /// RuntimeException: Incorrect reference between objects!
	kBadObjectReference = kRuntimeFault + 4,
	/// RuntimeException: Provided content already exists in the target storage!
	kContentDuplication = kRuntimeFault + 6,

    /// UnexpectedValueException: Unexpected value of an argument is provided!
    kUnexpectedValue = kRuntimeFault + 1 * kErrorSubClass,
    /// UnexpectedValueException: The provided object is incompatible with requested operation or its configuration!
    kIncompatibleObject = kUnexpectedValue + 1,
    /// UnexpectedValueException: Incomplete state of an argument!
    kIncompleteArgState = kUnexpectedValue + 2,
    /// UnexpectedValueException: Specified container is empty!
    kEmptyContainer = kUnexpectedValue + 3,
    /// kMissingArgumentException: Expected argument, but none provided!
    kMissingArgument = kUnexpectedValue + 4,

    /// BadObjectTypeException: Provided object has unexpected type!
    kBadObjectType = kUnexpectedValue + 1 * kErrorSubSubClass,

    /// UsageViolationException: Violation of allowed usage for the object!
    kUsageViolation = kRuntimeFault + 2 * kErrorSubClass,

    /// AccessViolationException: Access rights violation!
    kAccessViolation = kRuntimeFault + 3 * kErrorSubClass,


};

/// @traceid{SWS_CRYPT_19905}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02310}
/// @brief Exception type thrown for CRYPTO errors.
class CryptoException : public ara::core::Exception
{
public:

	/// @traceid{SWS_CRYPT_19906}@tracestatus{draft}
	/// @uptrace{RS_CRYPTO_02310}
	/// @brief Construct a new CryptoException from an ErrorCode.
	/// @param err  the ErrorCode
	explicit CryptoException(ara::core::ErrorCode err) noexcept: ara::core::Exception(err)
    {
    }
};

//- @class CryptoErrorDomain
///
/// @traceid{SWS_CRYPT_19900}@tracestatus{draft}
/// @uptrace{RS_AP_00130}
/// @brief Crypto Error Domain class that provides interfaces as defined by ara::core::ErrorDomain such as
///           a name of the Crypto Error Domain or messages for each error code.
///          This class represents an error domain responsible for all errors that may be reported by
///          public APIs in @c ara::crypto namespace.
/// @domainid{0x8000'0000'0000'0801}
class CryptoErrorDomain final : public ara::core::ErrorDomain
{
    constexpr static core::ErrorDomain::IdType kId = 0x8000000000000801;

public:

    /// @traceid{SWS_CRYPT_19903}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02310}  
	/// @brief crypto error 
    using Errc = CryptoErrc;

    /// @traceid{SWS_CRYPT_19904}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02310}
    /// @brief Alias for the exception base class
    using Exception = CryptoException;

    /// @traceid{SWS_CRYPT_19902}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02310}
    /// @brief Ctor of the CryptoErrorDomain
    constexpr CryptoErrorDomain() noexcept: ara::core::ErrorDomain{kId}
    {
    }

    /// @traceid{SWS_CRYPT_19950}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02310}
	/// @brief returns Text "Crypto"
    /// @returns "Crypto" text
    const char* Name() const noexcept override
    {
        return "Crypto";
    }

    /// @traceid{SWS_CRYPT_19953}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02310}
    /// @brief Translate an error code value into a text message.
	/// @param[in] errorCode  an error code identifier from the @c CryptoErrc enumeration
    /// @returns message text of error code  
    const char* Message(ara::core::ErrorDomain::CodeType errorCode) const noexcept override
    {
        Errc const kCode = static_cast<Errc>(errorCode);
        switch(kCode)
        {
        case Errc::kNoError:
            return "No error!";

        case Errc::kErrorSubClass:
        case Errc::kErrorSubSubClass:
            return "Reserved id!";

        case Errc::kResourceFault:
            return "Generic resource fault!";
        case Errc::kBusyResource:
            return "Specified resource is busy!";
        case Errc::kInsufficientResource:
            return "Insufficient capacity of specified resource!";
        case Errc::kUnreservedResource:
            return "Specified resource was not reserved!";
        case Errc::kModifiedResource:
            return "Specified resource has been modified!";

        case Errc::kLogicFault:
            return "Generic logic fault!";

        case Errc::kInvalidArgument:
            return "An invalid argument value is provided!";
        case Errc::kUnknownIdentifier:
            return "Unknown identifier is provided!";
        case Errc::kInsufficientCapacity:
            return "Insufficient capacity of the output buffer!";
        case Errc::kInvalidInputSize:
            return "Invalid size of an input buffer!";
        case Errc::kIncompatibleArguments:
            return "Provided values of arguments are incompatible!";
        case Errc::kInOutBuffersIntersect:
            return "Input and output buffers are intersect!";
        case Errc::kBelowBoundary:
            return "Provided value is below the lower boundary!";
        case Errc::kAboveBoundary:
            return "Provided value is above the upper boundary!";
        case Errc::kAuthTagNotValid:
            return "Provided authentication-tag cannot be verified!";

        case Errc::kUnsupported:
            return "Unsupported request (due to limitations of the implementation)!";

        case Errc::kInvalidUsageOrder:
            return "Invalid usage order of the interface!";
        case Errc::kUninitializedContext:
            return "Context of the interface was not initialized!";
        case Errc::kProcessingNotStarted:
            return "Data processing was not started yet!";
        case Errc::kProcessingNotFinished:
            return "Data processing was not finished yet!";

        case Errc::kRuntimeFault:
            return "Generic runtime fault!";
        case Errc::kUnsupportedFormat:
            return "Unsupported serialization format for this object type!";
        case Errc::kBruteForceRisk:
            return "Operation is prohibitted due to a risk of a brute force attack!";
        case Errc::kContentRestrictions:
            return "The operation violates content restrictions of the target container!";
        case Errc::kBadObjectReference:
            return "Incorrect reference between objects!";
        case Errc::kContentDuplication:
            return "Provided content already exists in the target storage!";

        case Errc::kUnexpectedValue:
            return "Unexpected value of an argument is provided!";
        case Errc::kIncompatibleObject:
            return "The provided object is incompatible with requested operation or its configuration!";
        case Errc::kIncompleteArgState:
            return "Incomplete state of an argument!";
        case Errc::kEmptyContainer:
            return "Specified container is empty!";
        case Errc::kMissingArgument:
            return "Expected argument, but none provided!";

        case Errc::kBadObjectType:
            return "Provided object has unexpected type!";

        case Errc::kUsageViolation:
            return "Violation of allowed usage for the object!";

        case Errc::kAccessViolation:
            return "Access rights violation!";

        default:
            return "Unknown error!";
        }
    }


    /// @traceid{SWS_CRYPT_19954}@tracestatus{draft}
    /// @uptrace{RS_CRYPTO_02310}
    /// @brief throws exception of error code
    /// @param[in] errorCode  an error code identifier from the @c CryptoErrc enumeration
    void ThrowAsException(const ara::core::ErrorCode& errorCode) const override
    {
        core::ThrowOrTerminate<Exception>(errorCode);
    }
};

namespace internal
{
constexpr CryptoErrorDomain g_cryptoErrorDomain;
}

/// @traceid{SWS_CRYPT_19952}@tracestatus{draft}
/// @uptrace{SWS_CORE_10980}
/// @brief Return a reference to the global CryptoErrorDomain.
/// @returns the CryptoErrorDomain
inline constexpr const ara::core::ErrorDomain& GetCryptoErrorDomain() noexcept
{
    return internal::g_cryptoErrorDomain;
}

/// @traceid{SWS_CRYPT_19951}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02310}
/// @brief Makes Error Code instances from the Crypto Error Domain.
///  The returned @c ErrorCode instance always references to @c CryptoErrorDomain.
/// @param[in] code  an error code identifier from the @c CryptoErrc enumeration
/// @param[in] data  supplementary data for the error description
/// @returns an instance of @c ErrorCode created according the arguments
inline constexpr ara::core::ErrorCode
MakeErrorCode(CryptoErrorDomain::Errc code, ara::core::ErrorDomain::SupportDataType data) noexcept
{
    return core::ErrorCode(static_cast<core::ErrorDomain::CodeType>(code),
                           GetCryptoErrorDomain(),
                           data);
}

}  // namespace crypto
}  // namespace ara

#endif  // ARA_CRYPTO_COMMON_CRYPTO_ERROR_DOMAIN_H_
