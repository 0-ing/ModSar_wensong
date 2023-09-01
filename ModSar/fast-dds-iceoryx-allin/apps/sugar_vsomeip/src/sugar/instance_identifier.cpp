#include "sugar/instance_identifier.h"

namespace sugar
{

    InstanceIdentifier::InstanceIdentifier()
    {
    }
    /***
     * name "111-22"
     */
    InstanceIdentifier::InstanceIdentifier(const std::string &idStr)
    {
        this->uniqueName = "[vsomeip]" + idStr;
        std::string str1;
        std::string str2;
        bool hadEqual = false;
        for (auto i = idStr.begin(); i != idStr.end();i++) {
            if (*i == '=') {
                hadEqual = true;
                break;
            }
            if (!hadEqual) {
                str1.push_back(*i);
            } else {
                str2.push_back(*i);
            }
        }
        this->serivceId = atoi(str1.c_str());
        this->sericeInstanceId = atoi(str2.c_str());
    }

    InstanceIdentifier::InstanceIdentifier(int serviceId, int serviceInstanceId)
    {
        this->serivceId = serivceId;
        this->sericeInstanceId = sericeInstanceId;
    }
    int InstanceIdentifier::getServiceId()
    {
        return serivceId;
    }
    int InstanceIdentifier::getSerciceInstanceId()
    {
        return sericeInstanceId;
    }

} // namespace sugar