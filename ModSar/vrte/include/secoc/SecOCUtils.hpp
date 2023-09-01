/// @file SecOCUtils.hpp
/// @copyright 2021 Robert Bosch GmbH. All rights reserved.

#ifndef INCLUDE_SECOC_SECOCUTILS
#define INCLUDE_SECOC_SECOCUTILS
#include "ISecOCUtils.hpp"

#define SECOC_DEBUG

namespace bosch
{
namespace vrte
{
namespace sec
{
namespace secoc
{
class SecOCUtils : public ISecOCUtils
{
  public : 
  SecOCUtils() = default;

  virtual ~SecOCUtils() {};
  /* Return true when data ID is found within the initialized hashmap */
  bool SearchId(uint16_t dataID, std::unordered_map<uint16_t, SecOCAuthenticatorCfg>& hashmap) override;

  /* Checks whether the message data ID is valid and sets appropriate ara::com::secoc::VerificationStatusResult */
  ara::com::secoc::VerificationStatusResult CheckMsgDataId(std::unordered_map<uint16_t, SecOCAuthenticatorCfg>& hashmap,
                                                           uint16_t                                             dataID) override;
  /* Return effective freshness length that will be part of the message */
  uint16_t freshnessLengthInMsg(std::unordered_map<uint16_t, SecOCAuthenticatorCfg>& hashmap, uint16_t dataID) override;

  /* Returns the length of authenticator (freshness + mac value) which will be added by SecOC at the end of authentic
   * message */
  uint16_t authenticationLengthInMsg(std::unordered_map<uint16_t, SecOCAuthenticatorCfg>& hashmap, uint16_t dataID) override;
};
} // namespace secoc
} // namespace sec
} // namespace vrte
} // namespace bosch

#endif /* INCLUDE_SECOC_SECOCUTILS */
