#ifndef METHOD_EXECUTER_INFO_HPP
#define METHOD_EXECUTER_INFO_HPP

#include "bind_common.hpp"

namespace com
{
namespace binding
{
/**
 * @brief Class used to store information of a method call
 */
class MethodExecuterInfo
{
public:
    MethodExecuterInfo(const HData& hData, const uint8_t* data) : headerData(hData)
    {
        payload = std::make_shared<std::vector<uint8_t>>(data, data + hData.payloadLength);
    }

    MethodExecuterInfo(MethodExecuterInfo&& source) : headerData{source.headerData}, payload{std::move(source.payload)}
    {
    }

    MethodExecuterInfo(const MethodExecuterInfo&) = delete;

    HData headerData;
    std::shared_ptr<std::vector<uint8_t>> payload;

};


} // namespace binding
} // namespace com
#endif
