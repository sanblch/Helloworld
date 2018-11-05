#pragma once

#include "ip.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <vector>

struct IPPool {
  void sort() {
    std::sort(std::begin(pool), std::end(pool), std::greater<>());
  }

  void filter(std::ostream& os, uint8_t first) {
    for(const auto& ip : pool)
      if(ip.address.at(0) == first)
        os << ip << std::endl;
  }

  void filter(std::ostream& os, uint8_t first, uint8_t second) {
    for(const auto& ip : pool)
      if(ip.address.at(0) == first && ip.address.at(1) == second)
        os << ip << std::endl;
  }

  void filter_any(std::ostream& os, uint8_t any) {
    for(const auto& ip : pool)
      if(ip.any(any))
        os << ip << std::endl;
  }

  std::vector<IP> pool;
};

std::istream& operator>>(std::istream& is, IPPool& ip_pool) {
  std::string unused;
  while(is && is.peek() != EOF)  {
    IP ip;
    is >> ip;
    ip_pool.pool.emplace_back(ip);
    std::getline(is, unused);
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, IPPool& ip_pool) {
  for(const auto& ip : ip_pool.pool) {
    os << ip << std::endl;
  }
  return os;
}
