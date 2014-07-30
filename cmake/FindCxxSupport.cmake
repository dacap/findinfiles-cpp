# Copyright (C) 2014 David Capello
#
# This file is released under the terms of the MIT license.
# Read LICENSE.txt for more information.

include(CheckCXXSourceCompiles)

if(CMAKE_COMPILER_IS_GNUCXX)
  add_definitions(-std=c++11)
endif()

# <filesystem> in C++ library

check_cxx_source_compiles("
  #include <filesystem>
  int main() { }
  "
  CXX_HAS_FILESYSTEM)

if(CXX_HAS_FILESYSTEM)
  check_cxx_source_compiles("
    #include <filesystem>
    int main() {
      std::files::path p;
    }
    "
    CXX_HAS_STD_FILES_FILESYSTEM)

  check_cxx_source_compiles("
    #include <filesystem>
    int main() {
      std::tr2::files::path path;
    }
    "
    CXX_HAS_TR2_FILES_FILESYSTEM)

  check_cxx_source_compiles("
    #include <filesystem>
    int main() {
      std::tr2::sys::path path;
    }
    "
    CXX_HAS_TR2_SYS_FILESYSTEM)
endif()
