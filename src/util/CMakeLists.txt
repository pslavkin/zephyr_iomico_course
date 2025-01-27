# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

target_include_directories(src/util PUBLIC include)
add_library(newlib STATIC util.c)
target_include_directories(newlib PUBLIC include)
target_link_libraries(newlib PUBLIC zephyr_interface)
