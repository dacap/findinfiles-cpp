# Copyright (C) 2014-2017 David Capello
#
# This file is released under the terms of the MIT license.
# Read LICENSE.txt for more information.

cmake_minimum_required(VERSION 2.8)
project(findinfiles)

set(LAF_WITH_TESTS OFF CACHE BOOL "Enable LAF tests")
add_subdirectory(laf)

# Extra flags for C++ compiler
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  add_definitions(-std=c++11 -stdlib=libc++)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_definitions(-std=c++11)
endif()

# findinfiles exe
add_executable(findinfiles findinfiles.cpp)
target_link_libraries(findinfiles laf-base)
