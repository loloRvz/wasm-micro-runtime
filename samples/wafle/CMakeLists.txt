# Copyright (C) 2019 Intel Corporation.  All rights reserved.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

cmake_minimum_required (VERSION 2.8)

project (wafle)

################  wamr runtime settings  ################
message(STATUS "WAMR_BUILD_SDK_PROFILE=${WAMR_BUILD_SDK_PROFILE}")

# Reset default linker flags
set (CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set (CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

set (WAMR_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/../..)

## use library and headers in the SDK
link_directories(${WAMR_ROOT_DIR}/wamr-sdk/out/${WAMR_BUILD_SDK_PROFILE}/runtime-sdk/lib)
include_directories(
    ${WAMR_ROOT_DIR}/wamr-sdk/out/${WAMR_BUILD_SDK_PROFILE}/runtime-sdk/include
    ${WAMR_ROOT_DIR}/core/shared/utils
    ${WAMR_ROOT_DIR}/core/shared/utils/uncommon
    ${WAMR_ROOT_DIR}/core/shared/platform/linux
)

include (${WAMR_ROOT_DIR}/core/shared/utils/uncommon/shared_uncommon.cmake)

################  application related  ################

include_directories(${CMAKE_CURRENT_LIST_DIR}/src)

#Note: uncomment below line to use UART mode
#add_definitions (-DCONNECTION_UART)

add_executable (wafle src/main.c src/bh_read_file.c)
target_link_libraries (wafle vmlib -lm -ldl -lpthread -lrt)


