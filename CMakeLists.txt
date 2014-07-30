# Copyright (C) 2014 David Capello
#
# This file is released under the terms of the MIT license.
# Read LICENSE.txt for more information.

cmake_minimum_required(VERSION 2.8)
project(findinfiles)

# Search .cmake files inside cmake/ directory
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# C++ TR2/11/14 Support
find_package(CxxSupport)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/cxx-config.h.cmakein
               ${CMAKE_CURRENT_BINARY_DIR}/cxx-config.h @ONLY)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

if(NOT CXX_HAS_FILESYSTEM)
  message(FATAL_ERROR "findinfiles needs a compiler with <filesystem> library")
endif()

# findinfiles exe
add_executable(findinfiles findinfiles.cc)
