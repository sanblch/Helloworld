#pragma once

#include "sslhash.h"
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <vector>

using paths = std::vector<boost::filesystem::path>;
using files = std::map<size_t, std::vector<std::string>>;

void insert_path(paths &d, const std::string& p) {
  d.push_back(p[p.size() - 1] == '/' ? p.substr(0, p.size() - 1) : p);
}

void get_paths(const std::vector<std::string> &lst, paths &d) {
  namespace boo = boost::filesystem;
  for (const auto &item : lst) {
    if (boo::exists(item) && boo::is_directory(item)) {
      insert_path(d, item);
    }
  }
}

void get_exclude_paths(const std::vector<std::string> &lst, paths &e) {
  namespace boo = boost::filesystem;
  for (const auto &item : lst) {
    boo::path p = item;
    if ((p.is_absolute() && boo::exists(item) && boo::is_directory(item)) ||
        p.is_relative()) {
      insert_path(e, item);
    }
  }
}

void insert_file(const boost::filesystem::directory_entry &item, files &f,
                 const size_t s) {
  namespace boo = boost::filesystem;
  if (boo::exists(item) && !boo::is_directory(item) && !boo::is_symlink(item) &&
      boo::file_size(item) > s) {
    f[boo::file_size(item)].push_back(item.path().string());
  }
}

void get_files(const paths &d, const paths &e, files &f, const size_t s) {
  namespace boo = boost::filesystem;
  for (const auto &dir : d) {
    bool excluded = false;
    for (const auto &ex : e) {
      if ((ex.is_relative() && dir.filename() == ex.filename()) || dir == ex) {
        excluded = true;
        break;
      }
    }
    if (excluded)
      break;
    boo::directory_iterator it{dir};
    while (it != boo::directory_iterator{}) {
      insert_file(*it, f, s);
      ++it;
    }
  }
}

void get_files_recursive(const paths &d, const paths &e, files &f,
                         const size_t s) {
  namespace boo = boost::filesystem;
  for (const auto &dir : d) {
    boo::recursive_directory_iterator it{dir};
    while (it != boo::recursive_directory_iterator{}) {
      for (const auto &ex : e) {
        if ((ex.is_relative() && it->path().filename() == ex.filename()) ||
            it->path() == ex) {
          it.no_push();
          break;
        }
      }
      insert_file(*it, f, s);
      ++it;
    }
  }
}
