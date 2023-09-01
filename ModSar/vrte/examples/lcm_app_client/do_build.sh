#!/bin/bash

# **********************************************************************************************************************
# *                                                                                                                    *
# * COPYRIGHT RESERVED, Robert Bosch GmbH, 2020. All rights reserved.                                                  *
# * The reproduction, distribution and utilization of this document as well as the communication of its contents to    *
# * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.     *
# * All rights reserved in the event of the grant of a patent, utility model or design.                                *
# *                                                                                                                    *
# **********************************************************************************************************************
 
ROOT_DIR=$(pwd)
CLEAN=false
BUILD_TYPE=debug
VRTE_VERSION=R22-08
TARGET_ARCHITECTURE=aarch64
TARGET_VARIANT=WAVE3.3_P
INTERFACE_PKG=false
DEPLOYMENT_PKG=false
APP=' '

FONT_RED='\033[31m'
FONT_YELLOW='\033[33m'
FONT_BLUE='\033[32m'
COLOR_DISABLE='\033[0m'
COLOR_HIGHLIGHT='\033[1m'

while getopts cha:idv:t:r:p: opt
do
   case $opt in
       h) echo -en "Use -c to delete the build folder\n"
	  echo -en "Use -a to define the target architecture. aarch64\ x86_64 (default: aarch64)\n"
	  echo -en "Use -r to define the VRTE version. (default: R22-04)\n"
	  echo -en "Use -t to define the build type. debug\ release (default: debug)\n"
	  echo -en "Use -v to define the variant which you want to build. WAVE3.3_P\WAVE3.2_S\WAVE3.2 (default: WAVE3.3_P)\n"
	  #echo -en "Use -p to chose the app to build\n"
           exit 0
           ;; 
       c) CLEAN=true;;
       t) BUILD_TYPE=($OPTARG);;
       v) TARGET_VARIANT=($OPTARG);;
       r) VRTE_VERSION=($OPTARG);;
       a) TARGET_ARCHITECTURE=($OPTARG);;
       p) APP=($OPTARG);;

   esac
done

cat << EOF
**********************************************************************************************************************
*                                                                                                                    *
* COPYRIGHT RESERVED, Robert Bosch GmbH, 2020. All rights reserved.                                                  *
* The reproduction, distribution and utilization of this document as well as the communication of its contents to    *
* others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.     *
* All rights reserved in the event of the grant of a patent, utility model or design.                                *
*                                                                                                                    *
**********************************************************************************************************************
EOF

echo -en "$FONT_YELLOW"
echo "Option clean: $CLEAN" 
echo "CPU architecture: $TARGET_ARCHITECTURE"
echo "VRTE: $VRTE_VERSION"
echo "Type: $BUILD_TYPE"
echo "Variant: $TARGET_VARIANT"
echo -e "$COLOR_DISABLE"

#Clean the build
if [[ "${CLEAN}" == "true" ]] ; then
    echo "Delete the ${ROOT_DIR}/build"
    rm -rf build compile.log
    exit 0
fi

#check build type and variant
if [[ "${BUILD_TYPE}" != "debug" && "${BUILD_TYPE}" != "release" ]] ; then
    echo -e "${FONT_RED}Invalid build type, please chose type: debug/release $COLOR_DISABLE"
    exit 1
fi

if [[ "${TARGET_VARIANT}" != "WAVE3.3_P" && "${TARGET_VARIANT}" != "WAVE3.3_S" && "${TARGET_VARIANT}" != "WAVE3.2" ]] ; then
    echo -e "${FONT_RED}Invalid variant, please chose variant: WAVE3.3_P/WAVE3.3_S/WAVE3.2 $COLOR_DISABLE"
    exit 1
fi

export WAVE3_BUILD_TYPE=${BUILD_TYPE}
export WAVE3_TARGET_VARIANT=${TARGET_VARIANT}

echo -en "$FONT_BLUE"
echo -e "Script:\t"    $0
echo -e "Date:\t"      $(date)
echo -e "Node:\t"      $(hostname)
echo -e "User:\t"      $USER
echo -e "$COLOR_DISABLE"

RB_VRTE_VERSION=${VRTE_VERSION}
RB_VRTE_TOOL_ROOT='/opt/VRTE'
QNX_SDK_ROOT='/opt'

# export build flags
export BUILD_TARGET="qnx_${TARGET_ARCHITECTURE}"
export BUILD_OPTIONS="-experimental"
if [ "${BUILD_TYPE}" == "debug" ] ; then
	TYPE='_DEBUG_'
else
	TYPE='_RELEASE_'
fi

if [ "${TARGET_VARIANT}" == "WAVE3.3_P" ] ; then
	VARIANT='_WAVE33_P_'
elif [ "${TARGET_VARIANT}" == "WAVE3.3_S" ] ; then
	VARIANT='_WAVE33_S_'
else
	VARIANT='_WAVE32_'
fi

WAVE3_BUILD_OPTIONS="-D$VARIANT -D$TYPE"
export WAVE3_BUILD_OPTIONS=$WAVE3_BUILD_OPTIONS
 
#export BUILD_OPTIONS="-sca2 -experimental"
#export BUILD_CMAKE_GENOPTIONS="-DCMAKE_BUILD_TYPE=RelWithDebInfo -DTARGET=QNX"

if [ -d "$RB_VRTE_TOOL_ROOT/$RB_VRTE_VERSION/Tools/vrteb/bin" ]
then
	export PATH=$RB_VRTE_TOOL_ROOT/$RB_VRTE_VERSION/Tools/vrteb/bin:${PATH}
else
	echo -e "${FONT_RED}ERROR: $RB_VRTE_TOOL_ROOT/$RB_VRTE_VERSION/Tools/vrteb/bin not found.${COLOR_DISABLE}"
	exit 1
fi

echo "Searching for QNX SDK ..."
RB_QNX_HOME_TRY1=$ROOT_DIR/../../../../driveos/qnx_sdp71
RB_QNX_HOME_TRY2=$QNX_SDK_ROOT/qnx-sdk-7.1.0-platform-20210215-v1-linux
if [ -f "${RB_QNX_HOME_TRY1}/qnxsdp-env.sh" ]; then
	vrteb.sh setting set sdk.qnx.profile1.path=${RB_QNX_HOME_TRY1}
	export RB_QNX_HOME=${RB_QNX_HOME_TRY1}
elif [ -f "${RB_QNX_HOME_TRY2}/qnxsdp-env.sh" ]; then
	vrteb.sh setting set sdk.qnx.profile2.path=${RB_QNX_HOME_TRY2}
	export RB_QNX_HOME=${RB_QNX_HOME_TRY2}
else
	echo "----------------------------------"
	echo -e "${FONT_RED} ERROR: QNX SDK not found in ${RB_QNX_HOME_TRY1} or ${RB_QNX_HOME_TRY2} ${COLOR_DISABLE}" 
	echo "----------------------------------"
	exit 1
fi

echo "RB_QNX_HOME=${RB_QNX_HOME}"
export RB_VRTE_QNX_SDK_ENV=${RB_QNX_HOME}/qnxsdp-env.sh
echo "qnx sdk initializing ..."
. ${RB_VRTE_QNX_SDK_ENV}
echo "qnx sdk initialized!"

RB_VRTE_6i_HOME=${RB_VRTE_TOOL_ROOT}/${RB_VRTE_VERSION}/6i
RB_VRTE_6i_SDKS=$RB_VRTE_6i_HOME/SDKs
export RB_VRTE_6I_SDK_QNX_HOME="$QNX_SDK_ROOT/qnx-sdk-7.1.0-platform-20210215-v1"
export RB_VRTE_6i_SDK_QNX_AARCH64_TARGET_HS="${RB_VRTE_6i_SDKS}/qnx_aarch64/fs1/target/opt/vrte"
export RB_VRTE_6i_SDK_QNX_X86_64_TARGET_HS="${RB_VRTE_6i_SDKS}/qnx_x86_64/fs1/target/opt/vrte"
export RB_VRTE_6i_SDK_QNX_AARCH64_TARGET_FS1="${RB_VRTE_6i_SDKS}/qnx_aarch64/fs1/target/opt/vrte"
export RB_VRTE_6i_SDK_QNX_X86_64_TARGET_FS1="${RB_VRTE_6i_SDKS}/qnx_x86_64/fs1/target/opt/vrte"

if [ -z "${BUILD_TARGET}" ]; then echo "ERROR: BUILD_TARGET is not defined" && exit 1; fi

echo BUILD_TARGET=${BUILD_TARGET}
echo BUILD_OPTIONS=${BUILD_OPTIONS}
echo BUILD_CMAKE_GENOPTIONS=${BUILD_CMAKE_GENOPTIONS}
echo BUILD_CMAKE_BUILDOPTIONS=${BUILD_CMAKE_BUILDOPTIONS}
echo BUILD_NATIVE_OPTIONS=${BUILD_NATIVE_OPTIONS}

vrteb.sh install -o ${ROOT_DIR}/build/${TARGET_VARIANT}/${BUILD_TYPE} -s ${ROOT_DIR}  -a ${BUILD_TARGET} ${BUILD_OPTIONS} --cb -DUSE_WOLFSSL_LIC_AVAILABLE=OFF | tee build/compile.log