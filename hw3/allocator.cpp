#include "logging_allocator.h"
#include "thecontainer.h"
#include "reserving_allocator.h"
#include <iostream>
#include <map>

int main(int, char *[]) {
  auto m1 = std::map<int, int>{};
  for(size_t i = 0; i < 10; ++i) {
    m1[i] = (i == 0 ? 1 : m1[i - 1] * i);
  }

  auto m2 = std::map<const int, int, std::less<int>, reserving_allocator<std::pair<const int, int>, 10>>{};
  for(size_t i = 0; i < 10; ++i) {
    m2[i] = (i == 0 ? 1 : m2[i - 1] * i);
    std::cout << i << " " << m2[i] << std::endl;
  }
  std::cout << std::endl;

  auto l1 = TheContainer<int>{};
  for(int i = 0; i < 10; ++i) {
    l1.push_back(i);
  }

  auto l2 = TheContainer<int, reserving_allocator<TheContainerItem<int>, 10>>{};
  for(int i = 0; i < 10; ++i) {
    l2.push_back(i);
    std::cout << i << std::endl;
  }
  std::cout << std::endl;

  return 0;
}
