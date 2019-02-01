#include "nickname.h"
#include <cassert>
#include <iostream>

int main() {
  RadixTree radixTree;
  std::string str;
  while(std::cin >> str) {
    radixTree.insert(str);
  }
  radixTree.print(std::cout);
  radixTree.print_graph(std::cout, true);
}
