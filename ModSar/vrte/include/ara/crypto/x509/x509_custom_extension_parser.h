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
/// @brief Adaptive Autosar Crypto Stack. Cryptographic API. X509customExtensionParser interface definition.

#ifndef ARA_CRYPTO_X509_CUSTOM_EXTENSIONS_PARSER_H_
#define ARA_CRYPTO_X509_CUSTOM_EXTENSIONS_PARSER_H_

/*!********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* for signed and unsigned integer types */
#include <cstdint>
/* for utilities (e.g. std::pair) */
#include <utility>

#include "ara/core/result.h"
#include "ara/crypto/common/mem_region.h"
#include "ara/core/string_view.h"



namespace ara 
{
namespace crypto 
{
namespace x509 
{
/// @traceid{SWS_CRYPT_40932}@tracestatus{draft}
/// @uptrace{RS_CRYPTO_02306}
//- @interface X509CustomExtensionsParser
/// @brief X.509 custom extensions parser
/// Callback class to be implemented by user. Implemented functions get called by 
/// X509Provider::ParseCustomCertExtensions when parsing a certificate.
/// If any function of this class returns an error, the parsing will stop.
class X509CustomExtensionsParser {
 public:
   /// @traceid{SWS_CRYPT_40933}@tracestatus{draft}
   /// @uptrace{RS_CRYPTO_02306}
   /// \brief Type alias
   using Integer = ara::crypto::ReadOnlyMemRegion;

   /// @traceid{SWS_CRYPT_40934}@tracestatus{draft}
   /// @uptrace{RS_CRYPTO_02306}
   /// \brief Type alias
  using NumberOfUnusedBits = std::uint8_t;

  /// @traceid{SWS_CRYPT_40935}@tracestatus{draft}
  /// @uptrace{RS_CRYPTO_02306}
  /// \brief Type alias
  using BitString = std::pair<ara::crypto::ReadOnlyMemRegion, NumberOfUnusedBits>;

  /// @traceid{SWS_CRYPT_40936}@tracestatus{draft}
  /// @uptrace{RS_CRYPTO_02306}
  /// \brief Type alias
  using OctetString = ara::crypto::ReadOnlyMemRegion;

  /// @traceid{SWS_CRYPT_40937}@tracestatus{draft}
  /// @uptrace{RS_CRYPTO_02306}
  /// \brief Type alias
  using Oid = ara::core::StringView;

  /// @traceid{SWS_CRYPT_40938}@tracestatus{draft}
  /// @uptrace{RS_CRYPTO_02306}
  /// \brief Type alias
  using Utf8String = ara::crypto::ReadOnlyMemRegion;

  /// @traceid{SWS_CRYPT_40939}@tracestatus{draft}
  /// @uptrace{RS_CRYPTO_02306}
  /// \brief Type alias
  using PrintableString = ara::core::StringView;

  /// @traceid{SWS_CRYPT_40940}@tracestatus{draft}
  /// @uptrace{RS_CRYPTO_02306}
  /// \brief Type alias
  using Ia5String = ara::core::StringView;

  /// @traceid{SWS_CRYPT_40941}@tracestatus{draft}
  /// @uptrace{RS_CRYPTO_02306}
  /// \brief Type alias
  using GeneralizedTime = ara::core::StringView;

  /// @traceid{SWS_CRYPT_40942}@tracestatus{draft}
  /// @uptrace{RS_CRYPTO_02306}
  /// \brief Type alias
  using UtcTime = ara::core::StringView;

  /// @traceid{SWS_CRYPT_40916}@tracestatus{draft}
  /// @uptrace{RS_CRYPTO_02306}
  /// @brief Called when a sequence starts.
  /// @error CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
  virtual ara::core::Result<void> OnSequenceStart() noexcept = 0;

  /// @traceid{SWS_CRYPT_40917}@tracestatus{draft}
  /// @uptrace{RS_CRYPTO_02306}
  /// @brief Called when a sequence ends.
  /// @error CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
  virtual ara::core::Result<void> OnSequenceEnd() noexcept = 0;

  /// @traceid{SWS_CRYPT_40918}@tracestatus{draft}
  /// @uptrace{RS_CRYPTO_02306}
  /// @brief Called when a set starts.
  /// @error CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
  virtual ara::core::Result<void> OnSetStart() noexcept = 0;

  /// @traceid{SWS_CRYPT_40919}@tracestatus{draft}
  /// @uptrace{RS_CRYPTO_02306}
  /// @brief Called when a set ends.
  /// @error CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
  virtual ara::core::Result<void> OnSetEnd() noexcept = 0;

  /// @traceid{SWS_CRYPT_40920}@tracestatus{draft}
  /// @uptrace{RS_CRYPTO_02306}
  /// @brief Called when a boolean is encountered.
  /// @param[in] parsed_bool Parsed boolean value
  /// @error CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
  virtual ara::core::Result<void> OnBool(bool parsed_bool) noexcept = 0;

  /// @traceid{SWS_CRYPT_40921}@tracestatus{draft}
  /// @uptrace{RS_CRYPTO_02306}
  /// @brief Called when an integer is encountered.
  /// @param[in] parsed_integer Parsed integer value
  /// @error CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
  virtual ara::core::Result<void> OnInteger(Integer parsed_integer) noexcept = 0;


  /// @traceid{SWS_CRYPT_40922}@tracestatus{draft}
  /// @uptrace{RS_CRYPTO_02306}
  /// @brief Called when a bit string is encountered.
  /// @param[in] parsed_bit_string Parsed bit string value
  /// @error CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
  virtual ara::core::Result<void> OnBitString(BitString parsed_bit_string) noexcept = 0;

  /// @traceid{SWS_CRYPT_40923}@tracestatus{draft}
  /// @uptrace{RS_CRYPTO_02306}
  /// @brief Called when an octet string is encountered.
  /// @param[in] parsed_octet_string Parsed octet string value
  /// @error CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
  virtual ara::core::Result<void> OnOctetString(OctetString parsed_octet_string) noexcept = 0;

  /// @traceid{SWS_CRYPT_40924}@tracestatus{draft}
  /// @uptrace{RS_CRYPTO_02306}
  /// @brief Called when a NULL is encountered.
  /// @error CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
  virtual ara::core::Result<void> OnNull() noexcept = 0;

  /// @traceid{SWS_CRYPT_40925}@tracestatus{draft}
  /// @uptrace{RS_CRYPTO_02306}
  /// @brief Called when an oid is encountered.
  /// @param[in] parsed_oid Parsed oid value
  /// @error CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
  virtual ara::core::Result<void> OnOid(Oid parsed_oid) noexcept = 0;

  /// @traceid{SWS_CRYPT_40926}@tracestatus{draft}
  /// @uptrace{RS_CRYPTO_02306}
  /// @brief Called when an UTF8 string is encountered.
  /// @param[in] parsed_utf8_string Parsed UTF8 string value
  /// @error CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
  virtual ara::core::Result<void> OnUtf8String(Utf8String parsed_utf8_string) noexcept = 0;

  /// @traceid{SWS_CRYPT_40927}@tracestatus{draft}
  /// @uptrace{RS_CRYPTO_02306}
  /// @brief Called when a printable string is encountered.
  /// @param[in] parsed_printable_string Parsed printable string value
  /// @error CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
  virtual ara::core::Result<void> OnPrintableString(PrintableString parsed_printable_string) noexcept = 0;

  /// @traceid{SWS_CRYPT_40928}@tracestatus{draft}
  /// @uptrace{RS_CRYPTO_02306}
  /// @brief Called when an IA5 string is encountered.
  /// @param[in] parsed_ia5_string Parsed IA5 string value
  /// @error CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
  virtual ara::core::Result<void> OnIa5String(Ia5String parsed_ia5_string) noexcept = 0;

  /// @traceid{SWS_CRYPT_40929}@tracestatus{draft}
  /// @uptrace{RS_CRYPTO_02306}
  /// @brief Called when a generalized time is encountered.
  /// @param[in] parsed_generalized_time Parsed generalized time value
  /// @error CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
  virtual ara::core::Result<void> OnGeneralizedTime(GeneralizedTime parsed_generalized_time) noexcept = 0;

  /// @traceid{SWS_CRYPT_40930}@tracestatus{draft}
  /// @uptrace{RS_CRYPTO_02306}
  /// @brief Called when a UTC time is encountered.
  /// @param[in] parsed_utc_time Parsed UTC time value
  /// @error CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
  virtual ara::core::Result<void> OnUtcTime(UtcTime parsed_utc_time) noexcept = 0;

  /// @traceid{SWS_CRYPT_40931}@tracestatus{draft}
  /// @uptrace{RS_CRYPTO_02306}
  /// @brief Called when the parsing is completed.
  /// @error CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
  virtual ara::core::Result<void> OnParsingEnd() noexcept = 0;
};

}  // namespace x509
}  // namespace crypto
}  // namespace ara

#endif  // ARA_CRYPTO_X509_CUSTOM_EXTENSIONS_PARSER_H_
