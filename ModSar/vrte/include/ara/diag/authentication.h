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
#ifndef ARA_DIAG_AUTHENTICATION_H_INCLUDED
#define ARA_DIAG_AUTHENTICATION_H_INCLUDED
#if 0 // Not yet supported in VRTE
#include <chrono>
#include "ara/core/result.h"
#include "ara/core/string.h"
#include "ara/diag/client_authentication_handle.h"

namespace ara {

namespace diag {

/**
 * @brief Class to implement the Service Authentication interfaces to application
 *
 * @traceid{SWS_DM_01123}@tracestatus{draft}
 * @uptrace{RS_Diag_04251}
 */
class Authentication final
{
public:

   /**
    * @brief Constructor of Authentication
    *
    * @param specifier InstanceSpecifier to a PortPrototype of a DiagnosticAuthentication service instance in the manifest
    * @param reentrancyType specifies if interface is callable fully- or non-reentrant
    *
    * @traceid{SWS_DM_01124}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   explicit Authentication( const ara::core::InstanceSpecifier& specifier,
                            ReentrancyType                      reentrancyType );

   /**
    * @brief Destructor of Authentication
    *
    * @traceid{SWS_DM_01125}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   virtual ~Authentication() noexcept = default;

   /**
    * @brief This function accepts the certificate received from the tester, verifies it,
    * and creates a challenge and ephemeral public key that must be returned to the tester
    *
    * @returns Challenge created by the application, Ephemeral Public Key of Server
    *
    * @param CommunicationConfiguration As defined in ISO14229-1:2020, this parameter provides
    * information about how to proceed with security in further diagnostic communication
    * after the Authentication.
    * @param ClientCertificate The certificate that is received from the tester during Unidirectional
    * Authentication.
    * @param ClientChallenge As defined in ISO14229-1:2020, this parameter provides the challenge
    * received fom the tester during Unidirectional Authentication. This parameter has a dependency
    * on the CommunicationConfiguration used
    * @param metaInfo MetaInfo of the request.
    * @param cancellationHandler Set if the current conversation is canceled.
    *
    * @error DiagErrorDomain::DiagReportingErrc::kCertificateVerificationFailedInvalidTimePeriod Date and time of the
    * server does not match the validity period of the Certificate.
    * @error DiagErrorDomain::DiagReportingErrc::kCertificateVerificationFailedInvalidSignature Signature of the
    * Certificate could not be verified.
    * @error DiagErrorDomain::DiagReportingErrc::kCertificateVerificationFailedInvalidChainOfTrust Certificate could
    * not be verified against stored information about the issuing authority.
    * @error DiagErrorDomain::DiagReportingErrc::kCertificateVerificationFailedInvalidType Certificate does not match
    * the current requested use case.
    * @error DiagErrorDomain::DiagReportingErrc::kCertificateVerificationFailedInvalidFormat Certificate could not be
    * evaluated because the format requirement has not been met.
    * @error DiagErrorDomain::DiagReportingErrc::kCertificateVerificationFailedInvalidContent Certificate could not be
    * verified because the content does not match.
    * @error DiagErrorDomain::DiagReportingErrc::kCertificateVerificationFailedInvalidScope The scope of the Certificate
    * does not match the contents of the server.
    * @error DiagErrorDomain::DiagReportingErrc::kCertificateVerificationFailedInvalidCert Certificate received from
    * client is invalid, because the server has revoked access for some reason.
    * @error DiagErrorDomain::DiagReportingErrc::kChallengeCalculationFailed The challenge could not be
    * calculated on the server side.
    *
    * @traceid{SWS_DM_01126}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   virtual ara::core::Future<std::tuple<ara::core::Span<std::uint8_t>, ara::core::Span<std::uint8_t>>> VerifyCertificateUnidirectional( std::uint8_t                  CommunicationConfiguration,
                                                                                                                                        ara::core::Span<std::uint8_t> ClientCertificate,
                                                                                                                                        ara::core::Span<std::uint8_t> ClientChallenge,
                                                                                                                                        const MetaInfo&               metaInfo,
                                                                                                                                        CancellationHandler           cancellationHandler )
   = 0;

   /**
    * @brief This function accepts the certificate and challenge received from the tester, verifies the
    * certificate, and creates a challenge, Ephemeral Public Key  and Proof Of Ownership that must be
    * returned to the tester. The function also returns the server certificate that will be used by the
    * tester to verify the Proof Of Ownership
    *
    * @returns Challenge created by the application, Certificate of the server,
    * ProofOfOwnership calculated by the server, Ephemeral Public Key of server
    *
    * @param CommunicationConfiguration As defined in ISO14229-1:2020, this parameter provides
    * information about how to proceed with security in further diagnostic communication
    * after the Authentication.
    * @param ClientCertificate The certificate that is received from the tester during Bidirectional
    * Authentication.
    * @param ClientChallenge As defined in ISO14229-1:2020, this parameter provides the challenge
    * received from the tester during Bidirectional Authentication.
    * @param metaInfo MetaInfo of the request.
    * @param cancellationHandler Set if the current conversation is canceled.
    *
    * @error DiagErrorDomain::DiagReportingErrc::kCertificateVerificationFailedInvalidTimePeriod Date and time of the
    * server does not match the validity period of the Certificate.
    * @error DiagErrorDomain::DiagReportingErrc::kCertificateVerificationFailedInvalidSignature Signature of the
    * Certificate could not be verified.
    * @error DiagErrorDomain::DiagReportingErrc::kCertificateVerificationFailedInvalidChainOfTrust Certificate could
    * not be verified against stored information about the issuing authority.
    * @error DiagErrorDomain::DiagReportingErrc::kCertificateVerificationFailedInvalidType Certificate does not match
    * the current requested use case.
    * @error DiagErrorDomain::DiagReportingErrc::kCertificateVerificationFailedInvalidFormat Certificate could not be
    * evaluated because the format requirement has not been met.
    * @error DiagErrorDomain::DiagReportingErrc::kCertificateVerificationFailedInvalidContent Certificate could not be
    * verified because the content does not match.
    * @error DiagErrorDomain::DiagReportingErrc::kCertificateVerificationFailedInvalidScope The scope of the Certificate
    * does not match the contents of the server.
    * @error DiagErrorDomain::DiagReportingErrc::kCertificateVerificationFailedInvalidCert Certificate received from
    * client is invalid, because the server has revoked access for some reason.
    * @error DiagErrorDomain::DiagReportingErrc::kChallengeCalculationFailed The challenge could not be
    * calculated on the server side.
    *
    * @traceid{SWS_DM_01127}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   virtual ara::core::Future<std::tuple<ara::core::Span<std::uint8_t>, ara::core::Span<std::uint8_t>, ara::core::Span<std::uint8_t>, ara::core::Span<std::uint8_t>>> VerifyCertificateBidirectional( std::uint8_t                  CommunicationConfiguration,
                                                                                                                                                                                                     ara::core::Span<std::uint8_t> ClientCertificate,
                                                                                                                                                                                                     ara::core::Span<std::uint8_t> ClientChallenge,
                                                                                                                                                                                                     const MetaInfo&               metaInfo,
                                                                                                                                                                                                     CancellationHandler           cancellationHandler )
   = 0;

   /**
    * @brief This function accepts the Proof Of Ownership received from the tester and verifies it with
    * the Public Key of the certificate received in the verifycertificateunidirectional/ verifycertificatebidirectional
    * against the server challenge created in the last call to verifycertificateunidirectional/ verifycertificatebidirectional
    *
    * @returns Session Key Info or error
    *
    * @param ClientPOWN The Proof Of Ownership provided by the Tester to the previously exchanged Server Challenge
    * @param ClientEphemeralPublicKey As defined in ISO14229-1:2020, this is the Ephemeral public key generated by the client
    * for Diffie-Hellman key agreement.
    * @param metaInfo MetaInfo of the request.
    * @param cancellationHandler Set if the current conversation is canceled.
    *
    * @error DiagErrorDomain::DiagReportingErrc::kCertificateVerificationFailedInvalidTimePeriod Date and time of the
    * server does not match the validity period of the Certificate.
    * @error DiagErrorDomain::DiagReportingErrc::kCertificateVerificationFailedInvalidSignature Signature of the
    * Certificate could not be verified.
    * @error DiagErrorDomain::DiagReportingErrc::kCertificateVerificationFailedInvalidChainOfTrust Certificate could
    * not be verified against stored information about the issuing authority.
    * @error DiagErrorDomain::DiagReportingErrc::kCertificateVerificationFailedInvalidType Certificate does not match
    * the current requested use case.
    * @error DiagErrorDomain::DiagReportingErrc::kCertificateVerificationFailedInvalidFormat Certificate could not be
    * evaluated because the format requirement has not been met.
    * @error DiagErrorDomain::DiagReportingErrc::kCertificateVerificationFailedInvalidContent Certificate could not be
    * verified because the content does not match.
    * @error DiagErrorDomain::DiagReportingErrc::kCertificateVerificationFailedInvalidScope The scope of the Certificate
    * does not match the contents of the server.
    * @error DiagErrorDomain::DiagReportingErrc::kCertificateVerificationFailedInvalidCert Certificate received from
    * client is invalid, because the server has revoked access for some reason.
    * @error DiagErrorDomain::DiagReportingErrc::kChallengeCalculationFailed The challenge could not be
    * calculated on the server side.
    *
    * @traceid{SWS_DM_01128}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   virtual ara::core::Span<std::uint8_t> VerifyOwnership( ara::core::Span<std::uint8_t> ClientPOWN,
                                                          ara::core::Span<std::uint8_t> ClientEphemeralPublicKey,
                                                          const MetaInfo&               metaInfo,
                                                          CancellationHandler           cancellationHandler )
   = 0;

   /**
    * @brief This function accepts the certificate received from the tester, verifies it, and takes necessary
    * actions in the applications. Typical use cases include updates to the access-rights provided to a tester
    * that is already authenticated
    *
    * @returns void
    *
    * @param CertificateData Certificate to be verified, transmitted by the tester
    * @param metaInfo MetaInfo of the request.
    * @param cancellationHandler Set if the current conversation is canceled.
    *
    * @error DiagErrorDomain::DiagReportingErrc::kOwnershipVerificationFailed Delivered Ownership does not match
    * the provided challenge or could not verified with the own private key.
    *
    * @traceid{SWS_DM_01129}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   virtual Ara::core::Result<void> TransmitCertificate( ara::core::Span<std::uint8_t> CertificateData,
                                                        const MetaInfo&               metaInfo,
                                                        CancellationHandler           cancellationHandler )
   = 0;

   /**
    * @brief This Offer will enable the DM to forward request messages to this handler
    *
    * @error DiagErrorDomain::DiagReportingErrc::kGenericError General error occurred.
    * @error DiagErrorDomain::DiagOfferErrc::kAlreadyOffered  This service was already offered.
    *
    * @traceid{SWS_DM_01130}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   ara::core::Result<void> Offer();

   /**
    * @brief This StopOffer will disable the forwarding of request messages from DM
    *
    * @traceid{SWS_DM_01131}@tracestatus{draft}
    * @uptrace{RS_Diag_04251}
    */
   void StopOffer();
};

}  // namespace diag

}  // namespace ara

#endif // Not yet supported in VRTE
#endif /* ARA_DIAG_AUTHENTICATION_H_INCLUDED */
