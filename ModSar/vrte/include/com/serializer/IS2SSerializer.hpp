#ifndef S2S_SERIALIZER_INTERFACE_HPP
#define S2S_SERIALIZER_INTERFACE_HPP

#include <string>
#include <vector>

namespace com
{
namespace serializer
{
/**
 * @brief Interface that will be inherited by the S2S serialitaion classes
 */
template<typename SampleType_T>
class IS2SSerializer
{
public:
    /**
     * @brief Destructor
     */
    virtual ~IS2SSerializer()
    {
    }

    /**
     * @brief Function used to get the signal data from a object
     * @param iSignalOutBuffer Vector where the signal data will be placed
     * @param objectp Object from where to extract the signal data
     * @param iSignalName Used to determine which member of the Object should be used to extract the signal data
     * @param iSignalLength Length of signal data - used for validation purposes
     * @return TRUE if out vector can be used
     */
    virtual bool GetISignalData(std::vector<uint8_t>& iSignalOutBuffer,
                                const SampleType_T* objectp,
                                const std::string& iSignalName,
                                const uint32_t iSignalLength)
        = 0;
};

} // namespace serializer
} // namespace com

#endif
