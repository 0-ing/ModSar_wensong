/// @file SecOCMAC.hpp
/// @copyright 2021 Robert Bosch GmbH. All rights reserved.

#ifndef INCLUDE_SECOC_SECOCMAC
#define INCLUDE_SECOC_SECOCMAC

#include "ara/crypto/common/entry_point.h"
#include "secoc/ISecOCMAC.hpp"
#include "secoc/ISecOCUtils.hpp"
#include "secoc/SecOCUtils.hpp"
#include <memory>
#include <secoc/SecOC.hpp>
#include <secoc/secoc.h>
#include <string>
///	@brief secoc

namespace bosch
{
namespace vrte
{
namespace sec
{
namespace secoc
{

///	@brief SecOCMac class manages the generation and verification of CMAC
class SecOCMac : public ISecOCMac
{
private:
  SecOCCryptoCfg                               mSecocCryptoCfg;
  ara::crypto::cryp::SymmetricKey::Uptrc       mSymKey;
  ara::crypto::cryp::MessageAuthnCodeCtx::Uptr mMessageAuthnCtx;
  ara::crypto::keys::KeySlot::Uptr             mKeySlot;
  std::shared_ptr<ISecOCUtils>                 m_utils;

public:
  ///	@brief SecOCMac constructor
  SecOCMac(SecOCCryptoCfg secocCryptoCfg, std::shared_ptr<ISecOCUtils> utils = std::make_shared<SecOCUtils>());

  ///	@brief SecOCMac destrcutor
  ~SecOCMac(){};

  ///	@brief Method to generate MAC using crypto MAC interface
  ///
  ///	@details Design Decision -1  One SecOC instance has to provide  1 key slot mapped to n DataID's  and n
  ///FreshnessValueID's . 	This usecase will be further clarified with ARA::COM 	Design Decision -2 Interface used for MAC
  ///value generation/verification is synchronous.
  ///
  ///	@param[in] authenticMsg:Contains the input msg which will be embedded with Authenticator by SecOC
  ///	@param[in] authenticMsgLength :Msg length of i/p msg
  ///	@param[in] securedMsg : Final msg containing Auth msg + Authenticator
  ///	@param[in] securedMsgLength  : Msg length of securedMsg Buffer
  ///	@return VerificationStatusResult : Returns  Verification Status

  ara::com::secoc::VerificationStatusResult SecOCGenerateMAC(uint8_t* authenticMsg,
                                                             uint32_t authenticMsgLength,
                                                             uint8_t* securedMsg,
                                                             uint16_t securedMsgLength) override;

  ///	@brief Method to verify the generated MAC
  ///
  ///	@details Design Decision -1  One SecOC instance has to provide  1 key slot mapped to n DataID's  and n
  ///FreshnessValueID's . 	This usecase will be further clarified with ARA::COM
  ///	Design Decision -2 Interface used for MAC value generation/verification is synchronous.
  ///
  ///	@param[in] pAuthExpected : Expected data as per configuration
  ///	@param[in] authExpectedLength : Data length of expected data  as per configuration
  ///	@param[in]pDataToAuthenticator :Contains the input msg which will be embedded with Authenticator by SecOC
  ///	@param[in]dataToAuthenticatorLength :Msg length of i/p msg
  ///	@return  Status of verification: Returns  Verification Status

  ara::com::secoc::VerificationStatusResult SecOCVerifyMAC(const uint8_t* pAuthExpected,
                                                           uint16_t       authExpectedLength,
                                                           const uint8_t* pDataToAuthenticator,
                                                           uint32_t       dataToAuthenticatorLength) override;

  ///	@brief This method is the overloaded operator for bool operation
  explicit operator bool() const override;
};

} // namespace secoc
} // namespace sec
} // namespace vrte
} // namespace bosch

#endif /*INCLUDE_SECOC_SECOCMAC*/
