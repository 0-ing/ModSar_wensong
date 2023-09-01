/// @file SecOC.hpp
/// @copyright 2021 Robert Bosch GmbH. All rights reserved.

#ifndef SECOC_HPP_
#define SECOC_HPP_

#include <cstdint>
#include <string>

namespace bosch
{
namespace vrte
{
namespace sec
{
namespace secoc
{

const uint16_t k_freshnessLength = 8;
const uint16_t k_macLength = 16;

struct SecOCAuthenticatorCfg
{
  uint16_t authInfoTxLength;
  uint16_t freshnessValID;
  uint16_t freshnessValueLength;
  uint16_t freshnessValueTxLength;
};

struct SecOCCryptoCfg
{
  std::string authAlgo;
  std::string cryptoProvider;
  std::string keySlot;
};

} // namespace secoc
} // namespace sec
} // namespace vrte
} // namespace bosch

#endif /*SECOC_HPP_*/
