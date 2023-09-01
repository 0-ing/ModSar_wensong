#ifndef _SUGAR_COM_INSTANCE_H
#define _SUGAR_COM_INSTANCE_H
#include <string>
namespace sugar
{
    class InstanceIdentifier {
    public:
        InstanceIdentifier();
        /***
         * name "111-22"
         */
        InstanceIdentifier(const std::string &idStr);

        InstanceIdentifier(int serviceId,int serviceInstanceId);

        const char* getUniqueName() const {return uniqueName.c_str();}

        int getServiceId();
        int getSerciceInstanceId();
    protected:
        std::string uniqueName;
        int serivceId = 0;
        int sericeInstanceId = 0;
    };

    
} // namespace sugar

#endif // _SUGAR_COM_INSTANCE_H
