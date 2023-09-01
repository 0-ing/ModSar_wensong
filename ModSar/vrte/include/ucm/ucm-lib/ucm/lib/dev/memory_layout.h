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

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

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
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_dev_MemoryLayout, CTor);
    FRIEND_TEST(Test_ucm_lib_dev_MemoryLayout, AddImage);
    FRIEND_TEST(Test_ucm_lib_dev_MemoryLayout, ImageList);
    FRIEND_TEST(Test_ucm_lib_dev_MemoryLayout, AddImages);
    FRIEND_TEST(Test_ucm_lib_dev_MemoryLayout, AddDevice);
    FRIEND_TEST(Test_ucm_lib_dev_MemoryLayout, AddDevices);
    FRIEND_TEST(Test_ucm_lib_dev_MemoryLayout, AddMemslot);
    FRIEND_TEST(Test_ucm_lib_dev_MemoryLayout, AddMemslots);
    FRIEND_TEST(Test_ucm_lib_dev_MemoryLayout, ImageById);
    FRIEND_TEST(Test_ucm_lib_dev_MemoryLayout, DeviceById);
    FRIEND_TEST(Test_ucm_lib_dev_MemoryLayout, MemslotById);
    FRIEND_TEST(Test_ucm_lib_dev_MemoryLayout, ImageByName);
    FRIEND_TEST(Test_ucm_lib_dev_MemoryLayout, DeviceByName);
    FRIEND_TEST(Test_ucm_lib_dev_MemoryLayout, ImageSlotsLock);
#endif

public:
    MemoryLayout() = default;

    // copy semantics
    MemoryLayout(const MemoryLayout&) = delete;
    MemoryLayout& operator=(const MemoryLayout&) = delete;

    // move semantic
    MemoryLayout(MemoryLayout&&) = delete;
    MemoryLayout& operator=(MemoryLayout&&) = delete;

    ~MemoryLayout() = default;

    void add_image(Image::Specs&&);
    void add_device(Device::Specs&&);
    void add_memslot(MemSlot::Specs&&);

    void add_images(std::vector<Image::Specs>&&);
    void add_devices(std::vector<Device::Specs>&&);
    void add_memslots(std::vector<MemSlot::Specs>&&);

    std::shared_ptr<Image> image_byname(const std::string&);
    std::shared_ptr<Device> device_byname(const std::string&);

    std::shared_ptr<Image> image_byid(const id_type&);
    std::shared_ptr<Device> device_byid(const id_type&);
    std::shared_ptr<MemSlot> memslot_byid(const id_type&);

    std::vector<Image::Specs> image_list(void);

private:
    mutable std::mutex mutex_{};

    std::map<id_type, std::shared_ptr<Image>>  image_byid_{};
    std::map<id_type, std::shared_ptr<Device>> device_byid_{};
    std::map<id_type, std::shared_ptr<MemSlot>> memslot_byid_{};

    std::map<std::string, std::shared_ptr<Image>> image_byname_{};
    std::map<std::string, std::shared_ptr<Device>> device_byname_{};
    std::unordered_multimap<std::string, std::shared_ptr<MemSlot>>
    memslot_byname_{};

    void image_slots_lock(std::shared_ptr<Image>&);

    std::shared_ptr<Image> _image_byid(const id_type&);
    std::shared_ptr<Device> _device_byid(const id_type&);
    std::shared_ptr<MemSlot> _memslot_byid(const id_type&);
};

}    // namespace dev
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_DEV_MEMORY_LAYOUT_H_
