#pragma once

#include "sslhashfile.h"
#include <algorithm>
#include <boost/bimap/bimap.hpp>
#include <boost/bimap/multiset_of.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/support/lambda.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

template <HASHTYPE t> class Hasher {
  std::vector<SSLHashFile<t> *> hash_v;
  size_t BLOCK_SIZE = 0;
  using copy = boost::bimaps::bimap<
      boost::bimaps::set_of<size_t>,
      boost::bimaps::multiset_of<typename SSLHash<t>::size_type>>;
  using copy_type = typename copy::value_type;

  void initiate(const std::vector<std::string> &files) {
    size_t prevs = hash_v.size();
    if (prevs < files.size())
      hash_v.resize(files.size(), nullptr);
    for (size_t i = prevs; i < hash_v.size(); ++i) {
      hash_v[i] = new SSLHashFile<t>(BLOCK_SIZE);
    }
    for (auto &i : hash_v)
      if (i->isOpen())
        i->close();
    for (size_t i = 0; i < files.size(); ++i) {
      hash_v[i]->newfile(files[i]);
    }
  }

public:
  Hasher(size_t BS) : BLOCK_SIZE(BS) {}
  ~Hasher() {
    for (auto &i : hash_v) {
      delete i;
    }
    hash_v.clear();
  }

  void hash(const std::vector<std::string> &files) {
    copy cp;
    initiate(files);
    bool first = true;
    while (std::any_of(hash_v.begin(), hash_v.end(),
                       [](auto i) { return i->isOpen(); })) {
      for (size_t i = 0; i < files.size(); ++i) {
        if (hash_v[i]->isOpen()) {
          auto cpu_int = hash_v[i]->read();
          if (first)
            cp.insert(copy_type{i, cpu_int});
          else
            cp.left.modify_data(cp.left.find(i),
                                boost::bimaps::_data = cpu_int);
        }
      }
      first = false;
      for (auto i = cp.begin(); i != cp.end(); ++i) {
        if (cp.right.count(i->right) < 2) {
          hash_v[i->left]->close();
          cp.erase(i);
        }
      }
    }
    auto i = cp.right.begin();
    auto prev_i = i;
    while (i != cp.right.end()) {
      std::cout << files[i->second] << std::endl;
      if (++i == cp.right.end() || i->first != prev_i->first)
        std::cout << std::endl;
      prev_i = i;
    }
  }
};
