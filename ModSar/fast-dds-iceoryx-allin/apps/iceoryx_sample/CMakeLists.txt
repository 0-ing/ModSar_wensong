# Copyright (c) 2019 - 2020 by Robert Bosch GmbH. All rights reserved.
# Copyright (c) 2020 - 2022 by Apex.AI Inc. All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# SPDX-License-Identifier: Apache-2.0

# Build icedelivery example
cmake_minimum_required(VERSION 3.16)
project(example_icedelivery)

include(GNUInstallDirs)

set(iceoryx_platform_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../deps/iceoryx/install/lib/cmake/iceoryx_platform)
set(iceoryx_posh_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../deps/iceoryx/install/lib/cmake/iceoryx_posh)
set(iceoryx_hoofs_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../deps/iceoryx/install/lib/cmake/iceoryx_hoofs)
set(iceoryx_dust_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../deps/iceoryx/install/lib/cmake/iceoryx_dust)
find_package(iceoryx_platform REQUIRED)
find_package(iceoryx_posh CONFIG REQUIRED)
find_package(iceoryx_hoofs CONFIG REQUIRED)

include(IceoryxPackageHelper)
include(IceoryxPlatform)
include(IceoryxPlatformSettings)

iox_add_executable(
    TARGET  iox-cpp-publisher
    FILES   ./iox_publisher.cpp
    LIBS    iceoryx_posh::iceoryx_posh
)

iox_add_executable(
    TARGET  iox-cpp-publisher-untyped
    FILES   ./iox_publisher_untyped.cpp
    LIBS    iceoryx_posh::iceoryx_posh
)

iox_add_executable(
    TARGET  iox-cpp-subscriber
    FILES   ./iox_subscriber.cpp
    LIBS    iceoryx_posh::iceoryx_posh
)

iox_add_executable(
    TARGET  iox-cpp-subscriber-untyped
    FILES   ./iox_subscriber_untyped.cpp
    LIBS    iceoryx_posh::iceoryx_posh
)
