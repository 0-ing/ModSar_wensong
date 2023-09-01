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
/// @file      e2e_error_domain.h.hpp
/// @brief     Definition of COM E2E Error Domain
/// @copyright Robert Bosch GmbH 2020
/// @author    crg2fe
//=============================================================================

#ifndef ARA_COM_E2E_ERROR_DOMAIN_H
#define ARA_COM_E2E_ERROR_DOMAIN_H

#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"

namespace ara
{
namespace com
{
namespace e2e
{
/**
 * \brief The E2EErrc enumeration defines the error codes for the E2E Error Domain.
 *
 * \remark
 * @ID{[SWS_CM_10474]}
 *
 */
enum class E2EErrc : ara::core::ErrorDomain::CodeType
{
    kRepeated      = 1, ///< Data has a repeated counter
    kWrongSequence = 2, ///< Counter jump changed more than the allowed delta.
    kError         = 3, ///< Error not related to counters occurred. 
    kNotAvailable  = 4, ///< No value has been received yet.
    kNoNewData     = 5, ///< No new data is available.
};

/**
 * \brief The ProfileCheckStatus represents the results of the E2E check.
 *
 * \remark
 * @ID{[SWS_CM_90421]}
 */
enum class ProfileCheckStatus : uint8_t
{
    kOk,                ///< The checks of the sample were successful (including counter check).
    kRepeated      = 1, ///< Sample has a repeated counter.
    kWrongSequence = 2, ///< Sample counter jump was bigger than the allowed delta.
    kError         = 3, ///< Error not related to counters occurred (e.g. wrong crc, wrong length, wrong Data ID).
    kNotAvailable  = 4, ///< No sample was received yet.
    kNoNewData     = 5, ///< No new data is available since the last one.
    kCheckDisabled      ///< No E2E check status available (no E2E protection is configured).
};

/**
 * \brief The SMState represents the state the E2E supervision after the most recent check of the sample(s).
 *
 * \remark
 * @ID{[SWS_CM_90422]}
 */
enum class SMState : uint8_t
{
    kValid,         ///< Communication is functioning properly according to E2E checks, sample(s) can be used.
    kNoData,        ///< No data have been received from the publisher at all.
    kInit,          ///< SMState is initializing. Not enough data to switch state. Sample(s) cannot be used.
    kInvalid,       ///< Too few E2E checks yielded OK or to many yielded ERROR. Sample(s) cannot be used
    kStateMDisabled ///<  No E2E state machine available (no statemachine is configured).
};

/**
 * @brief An error domain for E2E errors.
 *
 * @traceid{SWS_CORE_00221}@tracestatus{draft}
 * @uptrace{RS_AP_00130}
 *
 * \remark
 * @ID{[SWS_CM_99026]}
 */
class E2EErrorDomain final : public ara::core::ErrorDomain
{
    /**
     * \brief Identifier for E2E Error Domain
     *
     * \remark
     * @ID{[SWS_CM_99026]}
     */
    constexpr static ErrorDomain::IdType kId = 0x8000000000001268;

public:
    /**
     * \brief Alias for the error code value enumeration
     *
     *  @traceid{SWS_CORE_00231}@tracestatus{draft}
     *  @uptrace{RS_AP_00130}
     */
    using Errc = E2EErrc;

    /** \brief Default constructor */
    constexpr E2EErrorDomain() noexcept : ErrorDomain(kId)
    {
    }

    /**
     * \brief Return the "shortname" of this error domain.
     * \return "E2E"
     *
     * \remark
     * @ID{[SWS_CM_99026]}
     */
    char const* Name() const noexcept override
    {
        return "E2E";
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
        case Errc::kRepeated:
            return "Data has a repated counter.";
        case Errc::kWrongSequence:
            return "Counter jump changed more than the allowed delta.";
        case Errc::kError:
            return "Error not related to counters occurred.";
        case Errc::kNotAvailable:
            return "No value has been received yet.";
        case Errc::kNoNewData:
            return "No new data is available.";
        default:
            return "Unknown error.";
        }
    }

    /** \brief Throw an error as exception (not implemented) */
    void ThrowAsException(ara::core::ErrorCode const& errorCode) const noexcept(false) override
    {
        static_cast<void>(errorCode);
    }
};

namespace internal
{
constexpr E2EErrorDomain g_E2EErrorDomain;
}

/**
 * \brief Return a reference to the global E2EErrorDomain.
 * \returns the ComErrorDomain
 *
 * @uptrace{SWS_CORE_05280}
 */
inline constexpr ara::core::ErrorDomain const& GetE2EErrorDomain() noexcept
{
    return internal::g_E2EErrorDomain;
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
inline constexpr ara::core::ErrorCode MakeErrorCode(E2EErrc code,
                                                    ara::core::ErrorDomain::SupportDataType data = 0) noexcept
{
    return ara::core::ErrorCode(static_cast<ara::core::ErrorDomain::CodeType>(code), GetE2EErrorDomain(), data);
}

} // namespace e2e
} // namespace com
} // namespace ara

#endif // ARA_COM_E2E_ERROR_DOMAIN_H
