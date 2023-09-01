/// @file SecOCUtils.hpp
/// @copyright 2021 Robert Bosch GmbH. All rights reserved.

#ifndef INCLUDE_SECOC_ISECOCUTILS
#define INCLUDE_SECOC_ISECOCUTILS
#include <unordered_map>
#include <secoc/SecOC.hpp>
#include <secoc/secoc.h>
#define SECOC_DEBUG

namespace bosch
{
namespace vrte
{
namespace sec
{
namespace secoc
{
class ISecOCUtils
{
public:
  ISecOCUtils() = default;

  virtual ~ISecOCUtils() {};
  /* Return true when data ID is found within the initialized hashmap */
  virtual bool SearchId(uint16_t dataID, std::unordered_map<uint16_t, SecOCAuthenticatorCfg>& hashmap) = 0;

  /* Checks whether the message data ID is valid and sets appropriate ara::com::secoc::VerificationStatusResult */
  virtual ara::com::secoc::VerificationStatusResult
  CheckMsgDataId(std::unordered_map<uint16_t, SecOCAuthenticatorCfg>& hashmap, uint16_t dataID) = 0;
  /* Return effective freshness length that will be part of the message */
  virtual uint16_t freshnessLengthInMsg(std::unordered_map<uint16_t, SecOCAuthenticatorCfg>& hashmap,
                                        uint16_t                                             dataID) = 0;

  /* Returns the length of authenticator (freshness + mac value) which will be added by SecOC at the end of authentic
   * message */
  virtual uint16_t authenticationLengthInMsg(std::unordered_map<uint16_t, SecOCAuthenticatorCfg>& hashmap,
                                             uint16_t                                             dataID) = 0;
};
} // namespace secoc
} // namespace sec
} // namespace vrte
} // namespace bosch

#endif /* INCLUDE_SECOC_ISECOCUTILS */
