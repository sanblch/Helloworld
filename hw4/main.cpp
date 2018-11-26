#include "ip_printer.h"
#include <iostream>
#include <tuple>
#include <vector>

int main() {
  print_ip_address(std::cout, static_cast<char>(-1));
  print_ip_address(std::cout, static_cast<short>(0));
  print_ip_address(std::cout, 2130706433);
  print_ip_address(std::cout, 8875824491850138409L);
  std::string ips { "192.168.0.1" };
  print_ip_address(std::cout, ips);
  std::vector<int> ipv { 192, 168, 0, 1 };
  print_ip_address(std::cout, ipv);
  std::tuple<int, int, int, int> ipt { 192, 168, 0, 1 };
  print_ip_address(std::cout, ipt);
}
