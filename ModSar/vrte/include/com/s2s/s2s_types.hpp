#ifndef S2S_TYPES_HPP
#define S2S_TYPES_HPP

#include "ara/com/types.h"
#include "e2e/E2EFactory.hpp"
#include "e2e/E2EProfiles.hpp"

#include <map>
#include <string>
#include <vector>

namespace com
{
namespace s2s
{
/**
 * @brief The DataTypePolicyEnum enum
 */
enum DataTypePolicyEnum
{
    legacy = 0,                       /**< System Description doesn’t use a complete Software Component Description*/
    networkRepresentationFromComSpec, /**< the network representation from the ComSpec that is aggregated by the
                                         PortPrototype shall be used*/
    override,           /**< the requirements specified in the PortInterface and in the ComSpec are not fulfilled by the
                           networkRepresentationProps*/
    transformingISignal /**< This literal indicates that a transformer chain shall be used to communicate the ISignal as
                           UINT8_N over the bus.*/
};

/**
 * @brief The ISignalTypeEnum enum
 */
enum ISignalTypeEnum
{
    array = 0, /**< Enumeration to denote that signal is of array type */
    primitive  /**< Enumeration to denote that signal is of primitive type */
};

/**
 * @brief The ByteOrderEnum enum
 */
enum ByteOrderEnum
{
    mostSignificantByteFirst = 0, /**< Enumeration to denote that signal has BigEndian byte order */
    mostSignificantByteLast,      /**< Enumeration to denote that signal has LittleEndian byte order */
    opaque                        /**< Enumeration to denote that signal has Opaque byte order */
};

// --------------- START Types used inside generated file
/**
 * @brief The ISignalToIPduMapping struct
 */
struct ISignalToIPduMapping
{
    ByteOrderEnum packingByteOrder; /**< Byte order of the signal in the PDU */
    uint32_t startPosition;         /**< Start position of the signal in the PDU */
};

/**
 * @brief The ISignal struct
 */
struct ISignal
{
    DataTypePolicyEnum dataTypePolicy; /**< Policy type of the signal */
    uint32_t length;                   /**< Length of the signal */
    ISignalTypeEnum iSignalType;       /**< Type of the signal */
};

/**
 * @brief The ISignalGroup struct
 */
struct ISignalGroup
{
    std::vector<std::string> signals; /**< Signals contained in signal group */
};

/**
 * @brief The EndToEndTransformationDescription struct
 */
struct EndToEndTransformationDescription
{
    bool clearFromValidToInvalid;    /**< ClearFromValidToInvalid of used by E2E */
    uint8_t counterOffset;           /**< CounterOffset of used by E2E */
    uint8_t crcOffset;               /**< CrcOffset of used by E2E */
    com::e2e::DataIdMode dataIdMode; /**< DataIdMode of used by E2E */
    uint8_t dataIdNibbleOffset;      /**< DataIdNibbleOffset of used by E2E */
    uint8_t maxDeltaCounter;         /**< MaxDeltaCounter of used by E2E */
    uint8_t maxErrorStateInit;       /**< MaxErrorStateInit of used by E2E */
    uint8_t maxErrorStateInvalid;    /**< MaxErrorStateInvalid of used by E2E */
    uint8_t maxErrorStateValid;      /**< MaxErrorStateValid of used by E2E */
    uint8_t maxNoNewOrRepeatedData;  /**< MaxNoNewOrRepeatedData of used by E2E */
    uint8_t minOkStateInit;          /**< MinOkStateInit of used by E2E */
    uint8_t minOkStateInvalid;       /**< MinOkStateInvalid of used by E2E */
    uint8_t minOkStateValid;         /**< MinOkStateValid of used by E2E */
    uint8_t offset;                  /**< Offset of used by E2E */
    std::string profileBehavior;     /**< ProfileBehavior of used by E2E */
    std::string profileName;         /**< ProfileName of used by E2E */
    uint8_t syncCounterInit;         /**< SyncCounterInit of used by E2E */
    uint8_t upperHeaderBitsToShift;  /**< UpperHeaderBitsToShift of used by E2E */
    uint8_t windowSizeInit;          /**< WindowSizeInit of used by E2E */
    uint8_t windowSizeInvalid;       /**< WindowSizeInvalid of used by E2E */
    uint8_t windowSizeValid;         /**< WindowSizeValid of used by E2E */
};

/**
 * @brief The EndToEndTransformationISignalProps struct
 */
struct EndToEndTransformationISignalProps
{
    std::vector<uint16_t> dataIds; /**< DataIds of used by E2E */
    uint16_t dataLength;           /**< DataLength of used by E2E */
    uint16_t maxDataLength;        /**< MaxDataLength of used by E2E */
    uint16_t minDataLength;        /**< MinDataLength of used by E2E */
    uint16_t sourceId;             /**< SourceId of used by E2E */
};

/**
 * @brief The S2SE2EConfig struct
 */
struct S2SE2EConfig
{
    std::string signalGroupName;                      /**< Name of signal group */
    uint32_t startPosition;                           /**< Start Position of signal group in PDU */
    uint32_t length;                                  /**< Length of apply to signal group in PDU */
    EndToEndTransformationDescription e2eDescription; /**< EndToEndTransformationDescription of signal group in PDU */
    EndToEndTransformationISignalProps e2eProps;      /**< EndToEndTransformationISignalProps of signal group in PDU */
};

/**
 * @brief The IPdu struct
 */
struct IPdu
{
    std::string name;                                                  /**< Name of the PDU */
    uint32_t length;                                                   /**< Length of the PDU */
    uint8_t unusedBitPattern;                                          /**< Value to fill the unused area of a PDU */
    uint8_t signalNumForE2eHeader;                                     /**< Number of signal for E2E header */
    std::map<std::string, ISignalToIPduMapping> iSignalToIPduMappings; /**< List of signals that this PDU is mapped to */
    std::vector<S2SE2EConfig> e2eConfigs; /**< List of e2e configs that this PDU is mapped to */
};
// -------------- END Types used inside generated file

// -------------- START Types used inside S2S Event Sender/Receiver
/**
 * @brief The ISignalConfig struct
 */
struct ISignalConfig
{
    std::string iSignalName;        /**< Signal identifier */
    uint32_t startPosition;         /**< Start position of the signal in the PDU */
    uint32_t length;                /**< Length of the signal */
    ByteOrderEnum packingByteOrder; /**< Byte order of the signal */
    ISignalTypeEnum iSignalType;    /**< Type of the signal */
};

/**
 * @brief The S2SEventConfig struct
 */
struct S2SEventConfig
{
    uint32_t pduLength;                        /**< Length of the PDU */
    uint8_t unusedBitPattern;                  /**< Value to fill the unused area of a PDU */
    std::vector<ISignalConfig> iSignalConfigs; /**< List of signals that this PDU is mapped to */
    bool isConfigurationValid;                 /**< Flag used to check if the configuration is valid */
};
// -------------- END Types used inside S2S Event Sender/Receiver

/**
 * @brief The PduPosition struct
 */
struct PduPosition
{
    uint32_t PduByte; /**< Member to represent the byte index of a pdu */
    uint8_t PduBit;   /**< Member to represent the bit index */
};

/**
 * @brief The S2SE2EProtectorConfig struct
 */
struct S2SE2EProtectorConfig
{
    uint32_t startPosition;                                 /**< Start position of the signal group in the PDU */
    uint32_t length;                                        /**< Length of the signal group */
    ara::com::UniquePtr<com::e2e::IE2EProtector> protector; /**< E2EProtector used by the signal group */
};

/**
 * @brief The S2SE2ECheckerConfig struct
 */
struct S2SE2ECheckerConfig
{
    uint32_t startPosition;                             /**< Start position of the signal group in the PDU */
    uint32_t length;                                    /**< Length of the signal group */
    ara::com::UniquePtr<com::e2e::IE2EChecker> checker; /**< E2EChecker used by the signal group */
};

} // namespace s2s
} // namespace com

#endif
