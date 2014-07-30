// Copyright (C) 2014 David Capello
// 
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef FILENAME_FILTER_H_INCLUDED
#define FILENAME_FILTER_H_INCLUDED
#pragma once

#include <regex>
#include <vector>

class filename_filter {
public:
  void exclude_dir(const std::string& pat) {
    dir_excludes_.push_back(std::regex(pat, std::regex::icase | std::regex::optimize));
  }

  void exclude(const std::string& pat) {
    excludes_.push_back(std::regex(pat, std::regex::icase | std::regex::optimize));
  }

  void include(const std::string& pat) {
    includes_.push_back(std::regex(pat, std::regex::icase | std::regex::optimize));
  }

  bool filter_dirname(const std::string& dn) const {
    for (const std::regex& re : dir_excludes_) {
      if (std::regex_match(dn, re))
        return false;
    }
    return true;
  }

  bool filter_filename(const std::string& fn) const {
    for (const std::regex& re : excludes_) {
      if (std::regex_match(fn, re))
        return false;
    }

    if (includes_.empty())
      return true;

    for (const std::regex& re : includes_) {
      if (std::regex_match(fn, re))
        return true;
    }

    return false;
  }

private:
  std::vector<std::regex> dir_excludes_;
  std::vector<std::regex> excludes_;
  std::vector<std::regex> includes_;
};

#endif // FILENAME_FILTER_H_INCLUDED
