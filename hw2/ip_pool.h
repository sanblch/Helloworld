#pragma once

#include "ip.h"
#include <algorithm>
#include <vector>

struct IPPool {
  void sort() {
    std::sort(std::begin(pool), std::end(pool));
  }

  void filter(std::ostream& os, const std::string& first) {
    for(const auto& ip : pool)
      if(ip.address.at(0) == first)
        os << ip << std::endl;
  }

  void filter(std::ostream& os, const std::string& first, const std::string& second) {
    for(const auto& ip : pool)
      if(ip.address.at(0) == first && ip.address.at(1) == second)
        os << ip << std::endl;
  }

  void filter_any(std::ostream& os, const std::string& any) {
    for(const auto& ip : pool)
      if(ip.any(any))
        os << ip << std::endl;
  }

  std::vector<IP> pool;
};

std::istream& operator>>(std::istream& is, IPPool& ip_pool) {
  IP ip;
  std::string unused;
  while(is >> ip) {
    if(ip.any(""))
      throw std::invalid_argument("invalid ip format");
    ip_pool.pool.push_back(ip);
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
