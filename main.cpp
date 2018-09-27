#include <iostream>
#include "hello.h"

int main(int, char**) {
  std::cout << "Hello, world!" << std::endl;
  std::cout << "Version " << version() << std::endl;
}
