#include "ip_pool.h"
#include <iostream>

int main() {
  try {
    IPPool<4> ip_pool;
    std::cin >> ip_pool;
    ip_pool.sort();
    std::cout << ip_pool;
    ip_pool.filter(std::cout, 1);
    ip_pool.filter(std::cout, 46, 70);
    ip_pool.filter_any(std::cout, 46);
  } catch(const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}
