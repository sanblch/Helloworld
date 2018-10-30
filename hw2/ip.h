#pragma once

#include <algorithm>
#include <array>
#include <sstream>

bool lexicographic_gt(const std::string& lhs, const std::string& rhs) {
  if(lhs.size() > rhs.size())
    return true;
  else if(lhs.size() < rhs.size())
    return false;
  return lhs > rhs;
}

struct IP {
  bool operator<(const IP& ip) const {
    return gt(0, ip);
  }

  bool gt(size_t i, const IP& ip) const {
    if(address.size() == i)
      return false;
    if(address.at(i) != ip.address.at(i))
      return lexicographic_gt(address.at(i), ip.address.at(i));
    return gt(i + 1, ip);
  }

  bool operator==(const IP& ip) const {
    return address == ip.address;
  }

  bool any(const std::string& str) const {
    return std::any_of(address.cbegin(), address.cend(), [&str](const std::string& item) {
          return item == str;
      });
  }

  std::array<std::string, 4> address;
};

std::istream& operator>>(std::istream& is, IP& ip) {
  std::getline(is, ip.address.at(0), '.');
  std::getline(is, ip.address.at(1), '.');
  std::getline(is, ip.address.at(2), '.');
  is >> ip.address.at(3);
  return is;
}

std::ostream& operator<<(std::ostream& os, const IP& ip) {
  os << ip.address.at(0) << "." <<
    ip.address.at(1) << "." <<
    ip.address.at(2) << "." <<
    ip.address.at(3);
  return os;
}
