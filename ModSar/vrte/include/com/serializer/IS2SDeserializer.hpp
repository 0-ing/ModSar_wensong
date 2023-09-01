#ifndef S2S_DESERIALIZER_INTERFACE_HPP
#define S2S_DESERIALIZER_INTERFACE_HPP

#include <string>
#include <vector>

namespace com
{
namespace serializer
{
/**
 * @brief Interface that will be inherited by the S2S deserialization classes
 */
template<typename SampleType_T>
class IS2SDeserializer
{
public:
    /**
     * @brief Destructor
     */
    virtual ~IS2SDeserializer()
    {
    }

    /**
     * @brief Function used to set the signal data to a object
     * @param iSignalInBuffer Vector that contains the signal data
     * @param objectp Object where to set the signal data
     * @param iSignalName Used to determine which member of the Object should be used to set the signal data
     * @param iSignalLength Length of signal data - used for validation purposes
     * @return TRUE if the object can be used
     */
    virtual bool SetISignalData(const std::vector<uint8_t>& iSignalInBuffer,
                                SampleType_T* objectp,
                                const std::string& iSignalName,
                                const uint32_t iSignalLength)
        = 0;
};

} // namespace serializer
} // namespace com

#endif
