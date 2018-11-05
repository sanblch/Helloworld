#pragma once

#include <algorithm>
#include <array>
#include <sstream>

struct IP {
  bool operator<(const IP& ip) const {
    return address < ip.address;
  }

  bool operator>(const IP& ip) const {
    return address > ip.address;
  }

  bool operator==(const IP& ip) const {
    return address == ip.address;
  }

  bool any(uint8_t a) const {
    return std::any_of(address.cbegin(), address.cend(), [a](uint8_t i) {
        return a == i;
      });
  }

  std::array<uint8_t, 4> address;
};

std::istream& operator>>(std::istream& is, uint8_t& octet) {
  unsigned a;
  is >> a;
  octet = static_cast<uint8_t>(a);
  return is;
}

std::istream& operator>>(std::istream& is, IP& ip) {
  bool ok = true;
  is >> ip.address.at(0);
  ok &= (is.peek() == '.');
  is.ignore();
  is >> ip.address.at(1);
  ok &= (is.peek() == '.');
  is.ignore();
  is >> ip.address.at(2);
  ok &= (is.peek() == '.');
  is.ignore();
  if(!ok)
    throw std::invalid_argument("invalid ip format");
  is >> ip.address.at(3);
  return is;
}

std::ostream& operator<<(std::ostream& os, uint8_t octet) {
  os << std::to_string(octet);
  return os;
}

std::ostream& operator<<(std::ostream& os, const IP& ip) {
  os << ip.address.at(0) << "." <<
    ip.address.at(1) << "." <<
    ip.address.at(2) << "." <<
    ip.address.at(3);
  return os;
}
