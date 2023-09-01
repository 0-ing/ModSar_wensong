/// @file SecOCMAC.hpp
/// @copyright 2021 Robert Bosch GmbH. All rights reserved.

#ifndef INCLUDE_SECOC_ISECOCMAC
#define INCLUDE_SECOC_ISECOCMAC


#include <secoc/SecOC.hpp>
#include "ara/crypto/common/entry_point.h"
#include <string>
#include <secoc/secoc.h>
#include "secoc/ISecOCUtils.hpp"
#include "secoc/SecOCUtils.hpp"
#include <memory>
///	@brief secoc

namespace bosch
{
namespace vrte
{
namespace sec
{
namespace secoc
{

///	@brief ISecOCMac interface class
class ISecOCMac
{

public:

  ///	@brief ISecOCMac constructor
  ISecOCMac() = default;

  ///	@brief ISecOCMac destrcutor
  virtual ~ISecOCMac(){};

  ///	@brief Method to generate MAC using crypto MAC interface
  ///
  ///	@details Design Decision -1  One SecOC instance has to provide  1 key slot mapped to n DataID's  and n FreshnessValueID's .
  ///	This usecase will be further clarified with ARA::COM
  ///	Design Decision -2 Interface used for MAC value generation/verification is synchronous.
  ///
  ///	@param[in] authenticMsg:Contains the input msg which will be embedded with Authenticator by SecOC
  ///	@param[in] authenticMsgLength :Msg length of i/p msg
  ///	@param[in] securedMsg : Final msg containing Auth msg + Authenticator
  ///	@param[in] securedMsgLength  : Msg length of securedMsg Buffer
  ///	@return VerificationStatusResult : Returns  Verification Status

  virtual ara::com::secoc::VerificationStatusResult
  SecOCGenerateMAC(uint8_t* authenticMsg, uint32_t authenticMsgLength, uint8_t* securedMsg, uint16_t securedMsgLength) = 0;

  ///	@brief Method to verify the generated MAC
  ///
  ///	@details Design Decision -1  One SecOC instance has to provide  1 key slot mapped to n DataID's  and n FreshnessValueID's .
   ///	This usecase will be further clarified with ARA::COM
  ///	Design Decision -2 Interface used for MAC value generation/verification is synchronous.
  ///
  ///	@param[in] pAuthExpected : Expected data as per configuration
  ///	@param[in] authExpectedLength : Data length of expected data  as per configuration
  ///	@param[in]pDataToAuthenticator :Contains the input msg which will be embedded with Authenticator by SecOC
  ///	@param[in]dataToAuthenticatorLength :Msg length of i/p msg
  ///	@return  Status of verification: Returns  Verification Status

  virtual ara::com::secoc::VerificationStatusResult SecOCVerifyMAC(const uint8_t* pAuthExpected,
                                                           uint16_t       authExpectedLength,
                                                           const uint8_t* pDataToAuthenticator,
                                                           uint32_t       dataToAuthenticatorLength) = 0;

  ///	@brief This method is the overloaded operator for bool operation
   virtual operator bool() const =0;
};

} // namespace secoc
} // namespace sec
} // namespace vrte
} // namespace bosch



#endif /* INCLUDE_SECOC_ISECOCMAC */
