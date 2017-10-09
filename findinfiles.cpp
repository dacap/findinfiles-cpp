// Copyright (C) 2014-2017 David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#include <fstream>
#include <iostream>
#include <regex>
#include <vector>
#include "base/fs.h"
#include "filename-filter.h"
#include "exclude-files.h"

class options {
public:
  options() : ignore_case_(false),
              verbose_(false),
              recursive_(true) {
    for (const std::string& pat : exclude_dirs)
      fn_filter_.exclude_dir(pat);

    for (const std::string& pat : exclude_files)
      fn_filter_.exclude(pat);
  }

  bool verbose() const { return verbose_; }
  bool recursive() const { return recursive_; }
  size_t count_patterns() const { return patterns_.size(); }

  void read_args(int argc, char* argv[]) {
    for (int i=1; i<argc; ++i) {
      const char* arg = argv[i];

      if (*arg == '-') {
        read_modifiers(arg+1);
      }
      else {
        add_pattern(arg);
      }
    }
  }

  bool match_patterns(const std::string& line) const {
    for (const std::regex& re : patterns_) {
      if (!std::regex_search(line, re))
        return false;
    }
    return true;
  }

  bool filter_dirname(const std::string& fn) const {
    return fn_filter_.filter_dirname(fn);
  }

  bool filter_filename(const std::string& fn) const {
    return fn_filter_.filter_filename(fn);
  }

private:
  void read_modifiers(const char* p) {
    for (; *p; ++p) {
      switch (*p) {
        case 'i':
          ignore_case_ = true;
          break;
        case 'v':
          verbose_ = true;
          break;
        case '1':
          recursive_ = false;
          break;
        case '.': {
          std::string include_extension = p;
          fn_filter_.include(".*\\" + include_extension);
          return;
        }
      }
    }
  }

  void add_pattern(const std::string& pat) {
    patterns_.push_back(std::regex(pat,
        (ignore_case_ ?
          std::regex::optimize | std::regex::icase:
          std::regex::optimize)));
  }

  std::vector<std::regex> patterns_;
  bool ignore_case_;
  bool verbose_;
  bool recursive_;
  filename_filter fn_filter_;
};

bool is_text(const std::string& line) {
  for (size_t i=0; i<line.size(); ++i) {
    if (line[i] == 0)
      return false;
  }
  return true;
}

void search_in_file(const options& opt, const std::string& fn) {
  std::ifstream file(fn);
  std::string line;
  size_t ln = 1;
  while (std::getline(file, line)) {
    if (!is_text(line)) {
      if (opt.verbose())
        std::clog << fn << " is binary" << std::endl;
      break;
    }

    if (opt.match_patterns(line))
      std::cout << fn << ":" << ln << ":" << line << "\n";

    ln++;
  }
}

void search_in_dir(const options& opt, const std::string& dir) {
  if (opt.verbose())
    std::clog << "Searching in " << dir << "/" << std::endl;

  for (const auto& fn : base::list_files(dir)) {
    std::string full_fn = base::join_path(dir, fn);

    if (base::is_directory(full_fn)) {
      if (opt.filter_dirname(fn)) {
        if (opt.recursive())
          search_in_dir(opt, full_fn);
      }
      else {
        if (opt.verbose())
          std::clog << "Ignoring " << full_fn << "/" << std::endl;
      }
    }
    else {
      if (opt.filter_filename(fn)) {
        if (opt.verbose())
          std::clog << "Searching in " << full_fn << std::endl;

        search_in_file(opt, full_fn);
      }
      else {
        if (opt.verbose())
          std::clog << "Ignoring " << full_fn << std::endl;
      }
    }
  }
}

int main(int argc, char* argv[]) {
  try {
    options opt;
    opt.read_args(argc, argv);

    if (opt.count_patterns() == 0) {
      std::cout << "No pattern\n";
      return 1;
    }

    std::string dir = base::get_current_path();
    search_in_dir(opt, dir);

    if (opt.verbose())
      std::clog << "Done\n";
  }
  catch (const std::exception& ex) {
    std::cerr << ex.what() << std::endl;
    return 1;
  }
}
