// Copyright (C) 2014 David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef FILESYSTEM_WRAPPER_H_INCLUDED
#define FILESYSTEM_WRAPPER_H_INCLUDED
#pragma once

#include "cxx-config.h"

#ifdef CXX_HAS_FILESYSTEM
  #include <filesystem>
#else
  #error <filesystem> is not available
#endif

#if defined CXX_HAS_STD_FILES_FILESYSTEM
  namespace fs = std::files;
#elif defined CXX_HAS_TR2_FILES_FILESYSTEM
  namespace fs = std::tr2::files;
#elif defined CXX_HAS_TR2_SYS_FILESYSTEM
  namespace fs = std::tr2::sys;
#else
  #error Unknown namespace for <filesystem>
#endif

#endif // FILESYSTEM_WRAPPER_H_INCLUDED
