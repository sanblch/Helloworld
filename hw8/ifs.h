#pragma once

#include <fstream>
#include <iostream>

class Reader {
  std::ifstream ifs {};
  size_t BLOCK_SIZE = 0;
public:
  Reader(size_t BS) : BLOCK_SIZE(BS) {}

  void open(const std::string& file) {
    ifs.open(file, std::ios::binary);
  }
  size_t read(char* str) {
    ifs.read(str, BLOCK_SIZE);
    return ifs.gcount();
  }
  bool eof() {
    return ifs.eof();
  }
  void close() {
    ifs.close();
  }
};
