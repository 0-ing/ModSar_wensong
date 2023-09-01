#ifndef __ICEORYXVERSIONS__
#define __ICEORYXVERSIONS__

#define ICEORYX_VERSION_MAJOR    2
#define ICEORYX_VERSION_MINOR    90
#define ICEORYX_VERSION_PATCH    0
#define ICEORYX_VERSION_TWEAK    0

#define ICEORYX_LATEST_RELEASE_VERSION    "2.90.0"
#define ICEORYX_BUILDDATE                 "2023-07-18T05:37:06Z"
#define ICEORYX_SHA1                      "0f5993e07347050427b493597160dd4ae76a8137-dirty"

#include "iox/logging.hpp"

#define ICEORYX_PRINT_BUILDINFO()     IOX_LOG(INFO) << "Built: " << ICEORYX_BUILDDATE;


#endif
