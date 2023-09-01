//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/dev/device_factory.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_DEV__DEVICE_FACTORY_H_
#define UCM_AAP_LIBRARY__UCM_LIB_DEV__DEVICE_FACTORY_H_


#include "ucm/lib/dev/posix.h"
#include "ucm/mock/sequence.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace dev   {

class DeviceFactory : virtual protected ucm::mock::Sequence
{
protected:
    explicit DeviceFactory(const std::string&, const std::string,
                           const bool match_with_regexp=false)
    {
        (void)(match_with_regexp);
    }
    std::string type_{};
    std::string node_{};
    static constexpr uint8_t matchlen_shift_val_ = 16;
    bool match_with_regexp_{};

    inline size_t match_quality(size_t, size_t);
    virtual size_t regexp_matchlen(const std::string) { return pop<size_t>(); }

public:
    DeviceFactory(      DeviceFactory &&) = default;
    DeviceFactory(const DeviceFactory  &) = default;

    DeviceFactory& operator=(       DeviceFactory &&) = default;
    DeviceFactory& operator=(const  DeviceFactory  &) = default;

    virtual ~DeviceFactory() = default;

    /// Create an instance of the Device class with the given specs
    /// @param specs Device specification
    /// @return Unique pointer to the Device class
    virtual std::unique_ptr<Posix>
    create(const Device::Specs&)
    {
        return pop<std::unique_ptr<Posix>&&>();
    }

    /// Checks if the given type and node are supported
    /// @param type Type of the device
    /// @param node Node of the device
    /// @param matchlen Return the length of the match to identify the most
    /// specific Device class
    /// @return If the type and node are supported
    virtual bool is_supported(const std::string&,
                              const std::string&,
                              size_t&)
    {
        return pop<bool>();
    }

    /// Get the device type
    /// @return The device type
    virtual const std::string& type() const noexcept
    {
        return pop<const std::string&>();
    }

    /// Get the node type
    /// @return The device node
    virtual const std::string& node() const noexcept
    {
        return pop<const std::string&>();
    }
};

inline size_t DeviceFactory::match_quality(size_t, size_t)
{
    return pop<size_t>();
}

}    // namespace dev
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__UCM_LIB_DEV__DEVICE_FACTORY_H_
