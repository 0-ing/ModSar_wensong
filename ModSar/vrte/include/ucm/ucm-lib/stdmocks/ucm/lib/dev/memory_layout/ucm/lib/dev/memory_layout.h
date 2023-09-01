//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/dev/memory_layout.h
/// @brief
/// @copyright    Robert Bosch GmbH 2019
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_DEV_MEMORY_LAYOUT_H_
#define UCM_AAP_LIBRARY_LIB_DEV_MEMORY_LAYOUT_H_

#include <map>
#include <mutex>
#include <vector>
#include <memory>
#include <unordered_map>

#include "ucm/mock/sequence.h"
#include "ucm/lib/types.h"
#include "ucm/lib/dev/image.h"
#include "ucm/lib/dev/device.h"
#include "ucm/lib/dev/memslot.h"


namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace dev {

class MemoryLayout final
    : virtual protected ucm::mock::Sequence
{

public:
    MemoryLayout() = default;

    // copy semantics
    MemoryLayout(const MemoryLayout&) = delete;
    MemoryLayout& operator=(const MemoryLayout&) = delete;

    // move semantic
    MemoryLayout(MemoryLayout&&) = delete;
    MemoryLayout& operator=(MemoryLayout&&) = delete;

    ~MemoryLayout() = default;

    void add_image(Image::Specs&&) { return pop<void>(); }
    void add_device(Device::Specs&&) { return pop<void>(); }
    void add_memslot(MemSlot::Specs&&) { return pop<void>(); }

    void add_images(std::vector<Image::Specs>&&) { return pop<void>(); }
    void add_devices(std::vector<Device::Specs>&&) { return pop<void>(); }
    void add_memslots(std::vector<MemSlot::Specs>&&) { return pop<void>(); }

    std::shared_ptr<Image> image_byname(const std::string&) { return pop<std::shared_ptr<Image>>(); }
    std::shared_ptr<Device> device_byname(const std::string&) { return pop<std::shared_ptr<Device>>(); }

    std::shared_ptr<Image> image_byid(const id_type&) { return pop<std::shared_ptr<Image>>(); }
    std::shared_ptr<Device> device_byid(const id_type&) { return pop<std::shared_ptr<Device>>(); }
    std::shared_ptr<MemSlot> memslot_byid(const id_type&) { return pop<std::shared_ptr<MemSlot>>(); }

    std::vector<Image::Specs> image_list(void) { return pop<std::vector<Image::Specs>>(); }
};

}    // namespace dev
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_DEV_MEMORY_LAYOUT_H_
