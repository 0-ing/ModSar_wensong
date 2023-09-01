//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      com_error_domain.h.hpp
/// @brief     Definition of COM Error Domain
/// @copyright Robert Bosch GmbH 2020
/// @author    crg2fe
//=============================================================================

#ifndef COM_ERROR_DOMAIN_H_INCLUDED
#define COM_ERROR_DOMAIN_H_INCLUDED

#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include "ara/core/exception.h"

namespace ara
{
namespace com
{
/**
 * \brief The ComErrc enumeration defines the error codes for the ComErrorDomain.
 *
 * \remark
 * @ID{[SWS_CM_10432]}
 *
 */
enum class ComErrc : ara::core::ErrorDomain::CodeType
{
    kOk                      = 0, ///< No error.
    kServiceNotAvailable     = 1, ///< Service is not available.
    kMaxSamplesReached       = 2, ///< Application holds more SamplePtrs than commited in Subscribe().
    kNetworkBindingFailure   = 3, ///< Local failure has been detected by the network binding.
    kGrantEnforcementError   = 4, ///< Request was refused by Grant enforcement layer.
    kPeerIsUnreachable       = 5, ///< TLS handshake fail.
    kFieldValueIsNotValid    = 6, ///< Field Value is not valid.
    kSetHandlerNotSet        = 7, ///< SetHandler has not been registered.
    kUnsetFailure            = 8, ///< Failure has been detected by unset operation.
    kSampleAllocationFailure = 9, ///< Not Sufficient memory resources can be allocated.
    kIllegalUseOfAllocate
    = 10, ///< The allocation was illegally done via custom allocator (i.e. not via shared memory allocation).
    kServiceNotOffered       = 11, ///< Service not offered.
    kCommunicationLinkError  = 12, ///< Communication link is broken.
    kNoClients               = 13, ///< No clients connected.
    kCommunicationStackError = 14, ///< Communication Stack Error, e.g. network stack, network binding, or communication
                                   ///< framework reports an error.
    kInstanceIDCouldNotBeResolved
    = 15, ///< ResolveInstanceIDs() failed to resolve InstanceID from InstanceSpecifier, i.e. is not mapped correctly.
    kMaxSampleCountNotRealizable   = 16, ///< Provided maxSampleCount not realizable.
    kWrongMethodCallProcessingMode = 17, ///< Wrong processing mode passed to constructor method call.
    kErroneousFileHandle           = 18, ///< The FileHandle returned from FindServce is corrupt/service not available.
    kCouldNotExecute               = 19, ///< Command could not be executed in provided Execution Context.
    kInvalidInstanceIdentifierString = 20, ///< Given InstanceIdentifier string is corrupted or non-compliant.
};

/**
 * \brief Exception type thrown for Com errors.
 *
 * \remark
 * @ID{[SWS_CM_11327]}
 */
class ComException : public ara::core::Exception
{
public:
    /**
     * \brief Construct a new ComException from an ErrorCode.
     * \param err  the ErrorCode
     *
     * \remark
     * @ID{[SWS_CM_11328]}
     */
    explicit ComException(ara::core::ErrorCode errorCode) noexcept : ara::core::Exception(errorCode)
    {
    }
};

/**
 * \brief An error domain for Com errors.
 *
 * @traceid{SWS_CORE_00221}@tracestatus{draft}
 * @uptrace{RS_AP_00130}
 *
 * \remark
 * @ID{[SWS_CM_11267]}
 */
class ComErrorDomain final : public ara::core::ErrorDomain
{
    /**
     * \brief Identifier for Com Error Domain
     *
     * \remark
     * @ID{[SWS_CM_11267]}
     */
    constexpr static ErrorDomain::IdType kId = 0x8000000000001267;

public:
    /**
     * \brief Alias for the error code value enumeration
     *
     * @traceid{SWS_CORE_00231}@tracestatus{draft}
     * @uptrace{RS_AP_00130}
     */
    using Errc = ComErrc;

    /**
     * \brief Alias for the exception base class
     *
     * \remark
     * @ID{[SWS_CM_11337]}
     */
    using Exception = ComException;

    /** \brief Default constructor */
    constexpr ComErrorDomain() noexcept : ErrorDomain(kId)
    {
    }

    /**
     * \brief Return the "shortname" of this error domain.
     * \return "Com"
     *
     * \remark
     * @ID{[SWS_CM_11267]}
     */
    char const* Name() const noexcept override
    {
        return "Com";
    };

    /**
     * \brief Translate an error code value into a text message.
     * \param errorCode  the error code value
     * \return the text message, never nullptr
     */
    char const* Message(ara::core::ErrorDomain::CodeType errorCode) const noexcept override
    {
        Errc const code = static_cast<Errc>(errorCode);
        switch (code)
        {
        case Errc::kServiceNotAvailable:
            return "Service is not available.";
        case Errc::kMaxSamplesReached:
            return "Application holds more SamplePtrs than commited in Subscribe().";
        case Errc::kNetworkBindingFailure:
            return "Local failure has been detected by the network binding.";
        case Errc::kWrongMethodCallProcessingMode:
            return "Wrong processing mode passed to constructor method call.";
        default:
            return "Unknown error.";
        }
    }

    /**
     * \brief Throws the exception type corresponding to the given ErrorCode.
     * \param errorCode  the ErrorCode instance
     *
     * \remark
     * @ID{[SWS_CM_11333]}
     */
    void ThrowAsException(ara::core::ErrorCode const& errorCode) const noexcept(false) override
    {
        ara::core::ThrowOrTerminate<Exception>(errorCode);
    }
};

namespace internal
{
constexpr ComErrorDomain g_ComErrorDomain;
}

/**
 * \brief Return a reference to the global ComErrorDomain.
 * \returns the ComErrorDomain
 *
 * @uptrace{SWS_CORE_05280}
 */
inline constexpr ara::core::ErrorDomain const& GetComErrorDomain() noexcept
{
    return internal::g_ComErrorDomain;
}

/** \brief Create a new ErrorCode within CoreErrorDomain.
 *
 * This function is used internally by constructors of ErrorCode. It is usually not
 * used directly by users.
 *
 * \param code the CoreErrorDomain-specific error code value
 * \param data optional vendor-specific error data
 * \returns a new ErrorCode instance
 *
 * @uptrace{SWS_CORE_05290}
 */
inline constexpr ara::core::ErrorCode MakeErrorCode(ComErrc code,
                                                    ara::core::ErrorDomain::SupportDataType data = 0) noexcept
{
    return ara::core::ErrorCode(static_cast<ara::core::ErrorDomain::CodeType>(code), GetComErrorDomain(), data);
}

} // namespace com
} // namespace ara

#endif // COM_ERROR_DOMAIN_H_INCLUDED
