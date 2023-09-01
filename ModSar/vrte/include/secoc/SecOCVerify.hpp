/// @file SecOCVerify.hpp
/// @copyright 2021 Robert Bosch GmbH. All rights reserved.

#ifndef SECOCVERIFY_HPP_
#define SECOCVERIFY_HPP_

#include <string>
#include <unordered_map>
#include <vector>
#include <mutex>
#include <memory>
#include <secoc/SecOC.hpp>
#include <secoc/SecOCMAC.hpp>
#include <secoc/FvmDummy.hpp>
#include <secoc/secoc.h>
#include "secoc/ISecOCUtils.hpp"
#include "secoc/SecOCUtils.hpp"

namespace bosch
{
namespace vrte
{
namespace sec
{
namespace secoc
{

/// @brief The override status enum that defines whether verification is executed and whether the message is passed on, and for
/// how long the override is active
enum class OverrideStatus : uint8_t
{
  // Until further notice, authenticator verification is not performed, PDU is dropped, verification result is set to
  // kSecOcNoVerification.
  kSecOcOverrideDropUntilNotice = 0x00u,
  // Until NumberOfMessagesToOverride is reached, authenticator verification is not performed, PDU is dropped,
  // verification result is set to kSecOcNoVerification.
  kSecOcOverrideDropUntilLimit = 0x01u,
  // Cancel Override of VerifyStatus
  kSecOcOverrideCancel = 0x02u,
  // Until further notice, authenticator verification is performed, PDU is forwarded to the application independent of
  // verification result, verification result is set to kSecOcVerificationFailureOverwritten in case of failed
  // verification.
  kSecOcOverridePassUntilNotice = 0x40,
  // Until NumberOfMessagesToOverride is reached, authenticator verification is not performed, PDU is sent to the
  // application, verification result is set to kSecOcNoVerification.
  kSecOcOverrideSkipUntilLimit = 0x41,
  // Until NumberOfMessagesToOverride is reached, authenticator verification is performed, PDU is sent to the
  // application independent of verification result, verification result is set to kSecOcVerificationFailure Overwritten
  // in case of failed verification.
  kSecOcOverridePassUntilLimit = 0x42,
  // Until further notice, authenticator verification is not performed, PDU is sent to the application, verification
  // result is set to kSecOcNoVerification.
  kSecOcOverrideSkipUntilNotice = 0x43,
};

struct dataIdOverrideStatus
{
  OverrideStatus overrideStatus;

  //  Number of sequential VerifyStatus to override when using a specific counter for authentication verification. This
  //  is only considered when OverrideStatus is equal to k SecOcOverrideDropUntilLimit, kSecOcOverrideSkipUntilLimit or
  //  kSecOcOverride PassUntilLimit.
  uint8_t currentMessagesOverridden;
  uint8_t numberOfMessagesToOverride;
};

///	@brief SecOC Verify class
class SecOCVerify
{
private:
  std::unordered_map<uint16_t, SecOCAuthenticatorCfg> mAuthCfg;
  SecOCMac                                            mSecOCMac;
  uint16_t                                            mBuildAttempts;

  // This option defines if the parameter "ValueId" of the function SecOC_VerifyStatusOverride() accepts the freshness
  // value (as a collection of one or more Secured I-PDUs to freshness) or the dataID for individual Secured I-PDUs.
  // - true: Function SecOC_VerifyStatusOverride accepts SecOCDataId as parameter.
  // - false: Function SecOC_VerifyStatusOverride accepts SecOCFreshnessValueId as parameter.
  bool mSecOCOverrideStatusWithDataId;

  ara::com::secoc::FvmDummy::Uptr                     mFvm;
  std::unordered_map<uint16_t, dataIdOverrideStatus>  mOverrideStatus;

  /// @brief Update the override status for the given Data ID. Return the error code to be forwarded to the external
  /// application.Caller has to skip verification if function returns kSecOcNoVerification. If function returns
  /// kSecOcVerificationFailureOverwritten, caller has to perform verification, and send
  /// kSecOcVerificationFailureOverwritten only if verification fails
  ///
  ///  @details Design Decision :  If status has been overriden, SEC sends to COM an indiciation whether the message has to be dropped,
  ///  skipped or passed(based on configuration). But SEC does not implement the service towards the external application.
  ///
  /// @param[in] dataId : Data Id of msg
  ara::com::secoc::VerificationStatusResult SecOCUpdateOverrideStatus(uint16_t dataId);

  std::shared_ptr<ISecOCUtils> m_utils;
public:

  ///	@brief Constructor
  ///	Struct SecOCConfig is a structure which is combination of all the configuration values passed by COM
  SecOCVerify(std::unordered_map<uint16_t, SecOCAuthenticatorCfg> authCfg,
              SecOCCryptoCfg                                      cryptoCfg,
              uint16_t                                            buildAttempts,
              bool                                                overrideStatusWithDataId,
              std::shared_ptr<ISecOCUtils> utils = std::make_shared<SecOCUtils>());


  ///	@brief The method which is to be called by COM to verify the secured message and returns the status
  ///
  ///   @details Design Decision 1- The retry logic for FVM recoverable errors will be implemented in the SecOC lib.
  ///	Probably it is ok that COM has to wait for some time till the max number has been reached.
  ///	For different SecOC instances, COM can configure different limits.
  ///	This way, COM can configure lower limits for more important messages.
  ///   Design Decision 2 -SecOC has to be implemented thread safe
  ///
  ///	@param[in]pSecuredMsg Input buffer containing the secured message to be verified
  ///	@return  Status whether the verification was successful or not

  ara::com::secoc::VerificationStatusResult
  SecOCVerifyMessage(uint16_t dataId, uint8_t* pSecuredMsg, uint32_t securedMsgLength);

  ~SecOCVerify(){};

  ///	@brief This service method provides the ability to force specific behavior of SecOc: accept or drop a message with or
  /// 	without performing the verification of authenticator or independent of the authenticator verification result, and
  /// 	to force a specific result for ara::com::secoc::VerificationStatusResult allowing additional fault handling in the
  /// 	application.
  ///	@param[in] ValueID
  ///	@param[in] overrideStatus
  ///	@param[in] numberOfMessagesToOverride
  ///	@return VerificationStatusResult : Returns  Verification Status

  ara::com::secoc::VerificationStatusResult
  SecOCVerifyStatusOverride(uint16_t ValueID, OverrideStatus overrideStatus, uint8_t numberOfMessagesToOverride);

  ///	@brief This method is invoked by COM
  ///
  ///	@details Design decision :During verification COM needs to know the size of authenticator(security tag) .
  ///	SecOC to provide an API for this.
  ///	@param[in] dataID : Data Id of msg
  ///   @return Returns the size of freshness value + authenticator which will be appended at the end of secured message
  uint16_t  SecOCGetAuthenticationLen(uint16_t dataID);   

  ///	@brief This method is the overloaded operator for bool operation
  explicit operator bool() const;
};

} // namespace secoc
} // namespace sec
} // namespace vrte
} // namespace bosch

#endif /*SECOCVERIFY_HPP_*/
