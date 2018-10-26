#include <array>
#include <sstream>

struct IP {
  bool operator<(const IP& ip) const {
    return address.at(0) < ip.address.at(0) ||
      address.at(0) == ip.address.at(0) && address.at(1) < ip.address.at(1) ||
      address.at(0) == ip.address.at(0) && address.at(1) == ip.address.at(1) && address.at(2) < ip.address.at(2) ||
      address.at(0) == ip.address.at(0) && address.at(1) == ip.address.at(1) && address.at(2) == ip.address.at(2) && address.at(3) < ip.address.at(3);
    return address.at(0) > ip.address.at(0) ||
                           address.at(0) == ip.address.at(0) && address.at(1) < ip.address.at(1) ||
                                                                                address.at(0) == ip.address.at(0) && address.at(1) == ip.address.at(1) && address.at(2) < ip.address.at(2) ||
                                                                                                                                                                          address.at(0) == ip.address.at(0) && address.at(1) == ip.address.at(1) && address.at(2) == ip.address.at(2) && address.at(3) < ip.address.at(3);

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
