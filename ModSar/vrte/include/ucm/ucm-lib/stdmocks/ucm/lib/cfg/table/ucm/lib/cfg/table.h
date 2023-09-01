//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/cfg/table.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_CFG_TABLE_H_
#define UCM_AAP_LIBRARY_LIB_CFG_TABLE_H_

#include <string>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/mock/sequence.h"

#include "ucm/lib/dev/image.h"
#include "ucm/lib/dev/device.h"
#include "ucm/lib/dev/memslot.h"
#include "ucm/lib/ara/ara_types.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace cfg {

struct ConfigDefault
{
    constexpr static bool swp_is_tar = true;
    constexpr static int domain_id_ = 0;
    constexpr static const char* domain_name_ = "unknown";

    constexpr static int pipeline_threads = 2;
    constexpr static int pipeline_thread_prio = 20;
    constexpr static std::size_t pipeline_nelem = 16;
    constexpr static std::size_t pipeline_esize = 65536;
    constexpr static std::size_t pipelines_number = 2;

    constexpr static long lifespan = -1;

    constexpr static const char* tmpdir = "/tmp";
    constexpr static const char* scratch = "/scratch";

    constexpr static ara::ARATypes::LogLevelType loglevel =
#if defined(BUILD_TYPE_RELEASE) || defined(BUILD_TYPE_MINSIZEREL)
            ara::ARATypes::LogLevelType::kInfo;
#else
            ara::ARATypes::LogLevelType::kVerbose;
#endif
};

struct Table final
    : virtual protected ucm::mock::Sequence
{
    explicit Table(int, char**) {}

    Table(Table&&) = delete;
    Table& operator=(Table&&) = delete;

    Table(const Table&) = delete;
    Table& operator=(const Table&) = delete;

    ~Table() = default;

    // const members
    const bool is_daemon_ {};
    const bool do_syslog_ {};
    const bool do_aralog_ {};
    const bool do_conlog_ {};
    const std::string cfgfile_ {};
    const std::string pidfile_ {};
    const std::string logfile_ {};
    const std::string progname_ {};

    std::string version_{"R20-05"};

    /// Use TAR as package format
    bool swp_tar_{ConfigDefault::swp_is_tar};

    // kill UCM after time?
    long lifespan_{ConfigDefault::lifespan};

    // processing pipeline default configuration
    int pipeline_threads_{ConfigDefault::pipeline_threads};
    int pipeline_thread_prio_{ConfigDefault::pipeline_thread_prio};
    std::size_t pipeline_nelem_{ConfigDefault::pipeline_nelem};
    std::size_t pipeline_esize_{ConfigDefault::pipeline_esize};
    std::size_t pipelines_number_{ConfigDefault::pipelines_number};

    // execution domain
    int domain_id_{ConfigDefault::domain_id_};
    std::string domain_name_{ConfigDefault::domain_name_};

    // working directories
    std::string tmpdir_{ConfigDefault::tmpdir};
    std::string scratch_{ConfigDefault::scratch};

    // UCM specific types
    ara::ARATypes::LogLevelType log_level_{ConfigDefault::loglevel};

    // devices, slots, images
    std::vector<dev::Image::Specs> images_specs_{};
    std::vector<dev::Device::Specs> devices_specs_{};
    std::vector<dev::MemSlot::Specs> memslots_specs_{};
};

}    // namespace cfg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_CFG_TABLE_H_
