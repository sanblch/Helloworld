#include "ip.h"
#include <range/v3/all.hpp>
#include <iostream>

IP<4> convert(const std::string& str) {
  IP<4> ip;
  std::istringstream iss {str};
  iss >> ip;
  return ip;
}

const IP<4>& printer(const IP<4>& ip) {
  std::cout << ip << std::endl;
  return ip;
}

template<unsigned ... N>
struct filter {
  static_assert(4 >= sizeof ... (N), "number of arguments can't be greater than IP octet number");
  const IP<4>& operator()(const IP<4>& ip) {
    unsigned i = 0;
    bool ok[sizeof ... (N)] = {(ip.address.at(i++) == N)...};
    if(ranges::all_of(ok, [](auto b) { return b == true; }))
      std::cout << ip << std::endl;
    return ip;
  }
};

template<uint8_t N>
struct filter_any {
  const IP<4>& operator()(const IP<4>& ip) {
    if(ranges::any_of(ip.address, [](auto octet) { return octet == N; }))
      std::cout << ip << std::endl;
    return ip;
  }
};

int main() {
  try {
    ranges::getlines(std::cin)                    |
      ranges::view::transform(convert)            |
      ranges::to_vector                           |
      ranges::action::sort                        |
      ranges::action::transform(printer)          |
      ranges::action::transform(filter<1>())      |
      ranges::action::transform(filter<46, 70>()) |
      ranges::action::transform(filter_any<46>());
  } catch(const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}
