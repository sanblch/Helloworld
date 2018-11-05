#pragma once

#include "ip.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <vector>

template<unsigned N>
struct IPPool {
  void sort() {
    std::sort(std::begin(pool), std::end(pool), std::greater<>());
  }

  template<typename ... Args>
  void filter(std::ostream& os, Args ... args) {
    static_assert(N >= sizeof ... (args), "number of arguments can't be greater than IP octet number");
    for(const auto& ip : pool) {
      unsigned i = 0;
      bool ok[sizeof ... (args)] = {(ip.address.at(i++) == args)...};
      if(std::all_of(std::begin(ok), std::end(ok), [](bool b) { return b == true; }))
        os << ip << std::endl;
    }
  }

  void filter_any(std::ostream& os, uint8_t any) {
    for(const auto& ip : pool)
      if(ip.any(any))
        os << ip << std::endl;
  }

  std::vector<IP<N>> pool;
};

template<unsigned N>
std::istream& operator>>(std::istream& is, IPPool<N>& ip_pool) {
  std::string unused;
  while(is && is.peek() != EOF)  {
    IP<N> ip;
    is >> ip;
    ip_pool.pool.emplace_back(ip);
    std::getline(is, unused);
  }
  return is;
}

template<unsigned N>
std::ostream& operator<<(std::ostream& os, IPPool<N>& ip_pool) {
  for(const auto& ip : ip_pool.pool) {
    os << ip << std::endl;
  }
  return os;
}
