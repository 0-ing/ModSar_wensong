#ifndef E2E_PROFILES_HPP
#define E2E_PROFILES_HPP

#include <cstdint>

namespace com
{
namespace e2e
{
/// @brief Enumeration used for crc calculation in some profiles
enum struct DataIdMode : uint8_t
{
    ALL_16_BIT,        ///< Two bytes are included in the CRC
    ALTERNATING_8_BIT, ///< One of the two bytes byte is included, alternating high and low byte, depending on parity of
                       ///< the counter
    LOWER_12_BIT,      ///< The low byte is included in the implicit CRC calculation, the low nibble of the high byte is
                       ///< transmitted along with the data, the high nibble of the high byte is not used
    LOWER_8_BIT,       ///< Only low byte is included, high byte is never used.
    INVALID            ///< Last enum
};

/// @brief Enumeration used to differentiate between profiles
enum struct ProfileType : uint8_t
{
    PROFILE_04,       ///< Enum value used for Profile 4
    PROFILE_05,       ///< Enum value used for Profile 5
    PROFILE_06,       ///< Enum value used for Profile 6
    PROFILE_07,       ///< Enum value used for Profile 7
    PROFILE_11,       ///< Enum value used for Profile 11
    PROFILE_04M,      ///< Enum value used for Profile 4m
    PROFILE_DISABLED, ///< Enum value used for Disabled profile
    PROFILE_NOK       ///< Last enum
};

/// @brief Structure used to configure the E2E State Machine
struct StateMachineConfig
{
    StateMachineConfig()
    {
    }
    StateMachineConfig(uint8_t windowSizeValid,
                       uint8_t windowSizeInvalid,
                       uint8_t windowSizeInit,
                       bool clearFromValidToInvalid,
                       uint8_t maxErrorStateInit,
                       uint8_t maxErrorStateInvalid,
                       uint8_t maxErrorStateValid,
                       uint8_t minOkStateInit,
                       uint8_t minOkStateInvalid,
                       uint8_t minOkStateValid)
        : windowSizeValid(windowSizeValid),
          windowSizeInvalid(windowSizeInvalid),
          windowSizeInit(windowSizeInit),
          clearFromValidToInvalid(clearFromValidToInvalid),
          maxErrorStateInit(maxErrorStateInit),
          maxErrorStateInvalid(maxErrorStateInvalid),
          maxErrorStateValid(maxErrorStateValid),
          minOkStateInit(minOkStateInit),
          minOkStateInvalid(minOkStateInvalid),
          minOkStateValid(minOkStateValid)
    {
    }

    uint8_t windowSizeValid{0};          ///< Size of the valid window
    uint8_t windowSizeInvalid{0};        ///< Size of the invalid window
    uint8_t windowSizeInit{0};           ///< Size of the init window
    bool clearFromValidToInvalid{false}; ///< Flag used to clear the counters when transitioning to invalid
    uint8_t maxErrorStateInit{0};        ///< Max number of errors allowed in the init state
    uint8_t maxErrorStateInvalid{0};     ///< Amount of samples that are required to remain in this state
    uint8_t maxErrorStateValid{0};       ///< Max number of errors allowed in the valid state
    uint8_t minOkStateInit{0};           ///< Min ok samples that are required to switch to next state
    uint8_t minOkStateInvalid{0};        ///< Min ok samples that are required to switch to next state
    uint8_t minOkStateValid{0};          ///< Min ok samples that are required to remain in this state
};

/// @brief Base structure used by other Profile configurations
struct ProfileConfig
{
    const ProfileType type;      ///< Current profile configuration type
    StateMachineConfig smConfig; ///< State Machine configuration associated to this profile

protected:
    ProfileConfig(ProfileType Type) : type(Type)
    {
    }
    ProfileConfig(ProfileType Type, StateMachineConfig SMConfig) : type(Type), smConfig(SMConfig)
    {
    }
};

/// @brief Structure used to configure profile 4
struct ProfileConfig_04 : public ProfileConfig
{
    ProfileConfig_04() : ProfileConfig(ProfileType::PROFILE_04)
    {
    }

    ProfileConfig_04(uint32_t DataId,
                     uint16_t MinDataLength,
                     uint16_t MaxDataLength,
                     uint16_t MaxDeltaCounter,
                     uint16_t Offset,
                     StateMachineConfig SMConfig)
        : ProfileConfig(ProfileType::PROFILE_04, SMConfig),
          dataId(DataId),
          minDataLength(MinDataLength),
          maxDataLength(MaxDataLength),
          maxDeltaCounter(MaxDeltaCounter),
          offset(Offset)
    {
    }

    uint32_t dataId{0};          ///< Profile 4 dataId
    uint16_t minDataLength{0};   ///< Profile 4 minDataLength
    uint16_t maxDataLength{0};   ///< Profile 4 maxDataLength
    uint16_t maxDeltaCounter{0}; ///< Profile 4 maxDeltaCounter
    uint16_t offset{0};          ///< Profile 4 offset
};

/// @brief Structure used to configure profile 5
struct ProfileConfig_05 : public ProfileConfig
{
    ProfileConfig_05() : ProfileConfig(ProfileType::PROFILE_05)
    {
    }

    ProfileConfig_05(uint16_t DataId,
                     uint16_t Length,
                     uint8_t MaxDeltaCounter,
                     uint16_t Offset,
                     StateMachineConfig SMConfig)
        : ProfileConfig(ProfileType::PROFILE_05, SMConfig),
          dataId(DataId),
          dataLength(Length),
          maxDeltaCounter(MaxDeltaCounter),
          offset(Offset)
    {
    }

    uint16_t dataId{0};         ///< Profile 5 dataId
    uint16_t dataLength{0};     ///< Profile 5 dataLength
    uint8_t maxDeltaCounter{0}; ///< Profile 5 maxDeltaCounter
    uint16_t offset{0};         ///< Profile 5 offset
};

/// @brief Structure used to configure profile 6
struct ProfileConfig_06 : public ProfileConfig
{
    ProfileConfig_06() : ProfileConfig(ProfileType::PROFILE_06)
    {
    }

    ProfileConfig_06(uint16_t DataId,
                     uint16_t MinDataLength,
                     uint16_t MaxDataLength,
                     uint16_t MaxDeltaCounter,
                     uint16_t Offset,
                     StateMachineConfig SMConfig)
        : ProfileConfig(ProfileType::PROFILE_06, SMConfig),
          dataId(DataId),
          minDataLength(MinDataLength),
          maxDataLength(MaxDataLength),
          maxDeltaCounter(MaxDeltaCounter),
          offset(Offset)
    {
    }

    uint16_t dataId{0};          ///< Profile 6 dataId
    uint16_t minDataLength{0};   ///< Profile 6 minDataLength
    uint16_t maxDataLength{0};   ///< Profile 6 maxDataLength
    uint16_t maxDeltaCounter{0}; ///< Profile 6 maxDeltaCounter
    uint16_t offset{0};          ///< Profile 6 offset
};

/// @brief Structure used to configure profile 7
struct ProfileConfig_07 : public ProfileConfig
{
    ProfileConfig_07() : ProfileConfig(ProfileType::PROFILE_07)
    {
    }

    ProfileConfig_07(uint32_t DataId,
                     uint32_t MinDataLength,
                     uint32_t MaxDataLength,
                     uint32_t MaxDeltaCounter,
                     uint32_t Offset,
                     StateMachineConfig SMConfig)
        : ProfileConfig(ProfileType::PROFILE_07, SMConfig),
          dataId(DataId),
          minDataLength(MinDataLength),
          maxDataLength(MaxDataLength),
          maxDeltaCounter(MaxDeltaCounter),
          offset(Offset)
    {
    }

    uint32_t dataId{0};          ///< Profile 7 dataId
    uint32_t minDataLength{0};   ///< Profile 7 minDataLength
    uint32_t maxDataLength{0};   ///< Profile 7 maxDataLength
    uint32_t maxDeltaCounter{0}; ///< Profile 7 maxDeltaCounter
    uint32_t offset{0};          ///< Profile 7 offset
};

/// @brief Structure used to configure profile 11
struct ProfileConfig_11 : public ProfileConfig
{
    ProfileConfig_11() : ProfileConfig(ProfileType::PROFILE_11)
    {
    }

    ProfileConfig_11(uint16_t DataId,
                     DataIdMode DataIdMode,
                     uint16_t DataLength,
                     uint8_t MaxDeltaCounter,
                     uint16_t CrcOffset,
                     StateMachineConfig SMConfig)
        : ProfileConfig(ProfileType::PROFILE_11, SMConfig),
          dataId(DataId),
          dataIdMode(DataIdMode),
          dataLength(DataLength), // [bit]
          maxDeltaCounter(MaxDeltaCounter),
          crcOffset(CrcOffset)
    {
    }

    uint16_t dataId{0};                         ///< Profile 11 dataId
    DataIdMode dataIdMode{DataIdMode::INVALID}; ///< Profile 11 dataIdMode
    uint16_t dataLength{0};                     ///< Profile 11 dataLength
    uint8_t maxDeltaCounter{0};                 ///< Profile 11 maxDeltaCounter
    uint16_t crcOffset{0};                      ///< Profile 11 crcOffset
};

/// @brief Structure used to configure profile 4m
struct ProfileConfig_04m : public ProfileConfig
{
    ProfileConfig_04m() : ProfileConfig(ProfileType::PROFILE_04M)
    {
    }

    ProfileConfig_04m(uint32_t DataId,
                      uint16_t MinDataLength,
                      uint16_t MaxDataLength,
                      uint32_t SourceId,
                      uint16_t MaxDeltaCounter,
                      uint16_t Offset,
                      StateMachineConfig SMConfig)
        : ProfileConfig(ProfileType::PROFILE_04M, SMConfig),
          dataId(DataId),
          minDataLength(MinDataLength),
          maxDataLength(MaxDataLength),
          sourceId(SourceId),
          maxDeltaCounter(MaxDeltaCounter),
          offset(Offset)
    {
    }

    uint32_t dataId{0};          ///< Profile 4m dataId
    uint16_t minDataLength{0};   ///< Profile 4m minDataLength
    uint16_t maxDataLength{0};   ///< Profile 4m maxDataLength
    uint32_t sourceId{0};        ///< Profile 4m sourceId
    uint16_t maxDeltaCounter{0}; ///< Profile 4m maxDeltaCounter
    uint16_t offset{0};          ///< Profile 4m offset
};

/// @brief Structure used to configure disabled profile
struct ProfileConfig_Disabled : public ProfileConfig
{
    ProfileConfig_Disabled() : ProfileConfig(ProfileType::PROFILE_DISABLED)
    {
    }
};

} // namespace e2e
} // namespace com

#endif
