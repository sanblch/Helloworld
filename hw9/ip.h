#pragma once

#include <boost/operators.hpp>
#include <algorithm>
#include <array>
#include <sstream>

template<unsigned N>
struct IP : boost::totally_ordered<IP<N>>{

  IP() = default;
  IP(const IP&) = default;
  IP(const std::array<uint8_t, N>& address) : address(address) {}

  using iterator = typename std::array<uint8_t, N>::iterator;

  iterator begin() {
    return address.begin();
  }

  iterator end() {
    return address.end();
  }

  uint8_t operator[](size_t i) const {
    return address[i];
  }

  bool operator<(const IP& ip) const {
    return address < ip.address;
  }

  bool operator==(const IP& ip) const {
    return address == ip.address;
  }

  std::array<uint8_t, N> address;
};

std::istream& operator>>(std::istream& is, uint8_t& octet) {
  unsigned a;
  is >> a;
  octet = static_cast<uint8_t>(a);
  return is;
}

template<unsigned N>
std::istream& operator>>(std::istream& is, IP<N>& ip) {
  bool ok = true;
  for(unsigned i = 0; i < N - 1; ++i) {
    is >> ip.address.at(i);
    ok &= (is.peek() == '.');
    is.ignore();
  }
  if(!ok)
    throw std::invalid_argument("invalid ip format");
  is >> ip.address.at(N - 1);
  return is;
}

std::ostream& operator<<(std::ostream& os, uint8_t octet) {
  os << std::to_string(octet);
  return os;
}

template<unsigned N>
std::ostream& operator<<(std::ostream& os, const IP<N>& ip) {
  for(unsigned i = 0; i < N - 1; ++i) {
    os << ip.address.at(i) << ".";
  }
  os << ip.address.at(N - 1);
  return os;
}
