/// @file SecOCAuthenticate.hpp
/// @copyright 2021 Robert Bosch GmbH. All rights reserved.

#ifndef SECOCAUTHENTICATE_HPP_
#define SECOCAUTHENTICATE_HPP_

#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <secoc/SecOC.hpp>
#include <secoc/SecOCMAC.hpp>
#include <secoc/FvmDummy.hpp>
#include <secoc/secoc.h>
#include "secoc/ISecOCUtils.hpp"
#include "secoc/SecOCUtils.hpp"
#include <memory>

#define ATTEMPT_COUNTER 3u

namespace bosch
{
namespace vrte
{
namespace sec
{
namespace secoc
{

enum class EAuthenticState : uint8_t
{
  kSecOcFreshnessCalc = 0x00u,
  kSecOCMacGeneration = 0x01u
};

/// @brief SecOCAuthenticate
class SecOCAuthenticate
{
private:
  std::unordered_map<uint16_t, SecOCAuthenticatorCfg> mAuthCfg;
  SecOCCryptoCfg                                      mSecOCCryptoCfg = {"", "", ""};
  SecOCMac                                            mSecOCMac;
  ara::com::secoc::FvmDummy::Uptr                     mFvm;

  ///	@brief Creation of Secured Msg
  ///	This method creates the secured message by combining the original authentic message
  /// 	and the generated authenticator
  /// 	@param dataID : Data Id of msg
  /// 	@param pAuthenticMsg:Contains the input msg which will be embedded with Authenticator by SecOC
  /// 	@param authenticMsgLength:Msg length of i/p msg
  /// 	@param FreshnessBuffer : Buffer containing the freshness value
  /// 	@param Authenticator : Buffer containing  Authenticator Data for i/p msg

  void createSecuredMsg(uint16_t  dataID,
                        uint8_t*  pAuthenticMsg,
                        uint32_t  authenticMsgLength,
                        uint8_t*  FreshnessBuffer,
                        uint8_t*  Authenticator);
  std::shared_ptr<ISecOCUtils> m_utils;
public:

  ///	@brief SecOCAuthenticate constructor
  ///	Struct SecOCConfig is a struture which is combination of all the configuration values passed by COM
  /// 	@param authCfg map
  /// 	@param SecOCCryptoCfg

  SecOCAuthenticate(std::unordered_map<uint16_t, SecOCAuthenticatorCfg> authCfg, SecOCCryptoCfg cryptoCfg,std::shared_ptr<ISecOCUtils> utils = std::make_shared<SecOCUtils>());//:mAuthCfg{authCfg}, mSecOCMac{cryptoCfg};

  ///	@brief SecOCAuthenticate destrcutor
  ~SecOCAuthenticate(){};

  ///	@brief The method which handles the entire authentication and returns the status.
  ///
  ///   @details Design Decision 1- The retry logic for FVM recoverable errors will be implemented in the SecOC lib.
  ///	Probably it is ok that COM has to wait for some time till the max number has been reached.
  ///	For different SecOC instances, COM can configure different limits.
  ///	This way, COM can configure lower limits for more important messages.
  ///   Design Decision 2 -SecOC has to be implemented thread safe
  ///	Design Decision 3 All SecOC configuration parameters are passed to SecOC by COM.
  ///
  ///	@param[in/out] pAuthenticMsg :Contains the input msg which will be embedded with Authenticator by SecOC
  ///	@param[in] authenticMsgLength :Msg length of i/p msg
  ///	@param[in] dataID : Data Id of msg
  ///  	@return : Status whether the authentication was successful or not

  ara::com::secoc::VerificationStatusResult SecOCAuthenticateMessage(uint8_t*  pAuthenticMsg,
                                                                     uint32_t  authenticMsgLength,
                                                                     uint16_t  dataID);

  ///	@brief This method is invoked by COM
  ///
  ///	@details Design Decision : COM will provide Authentication Msg pointer large enough so that complete authenticator with  authentic message can be copied .
  /// 	No further length check will be performed by SecOC.
  ///	@param[in] dataID: Data Id of msg
  ///   @return size of freshness value + authenticator which will be appended at the end of secured message

  uint16_t  SecOCGetAuthenticationLen(uint16_t dataID);                                                                  

  ///	@brief This method is the overloaded operator for bool operation
  explicit operator bool() const;
};

} // namespace secoc
} // namespace sec
} // namespace vrte
} // namespace bosch

#endif /*SECOCAUTHENTICATE_HPP_*/
