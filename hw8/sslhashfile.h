#pragma once

#include "ifs.h"
#include "sslhash.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <memory>

template <typename T> T fromBigEndian(const unsigned char *arr, size_t size) {
  T ret{};
  for (size_t i = 0; i < size; ++i)
    ret = static_cast<T>((ret << 8) | static_cast<uint8_t>(arr[i]));
  return ret;
}

template <HASHTYPE t> class SSLHashFile {
  SSLHash<t> sslHash;
  Reader reader;
  size_t BLOCK_SIZE = 0;
  char *str;
  unsigned char *hash_array;
  bool open = false;

public:
  SSLHashFile(size_t BS) : sslHash(), reader(BS), BLOCK_SIZE(BS) {
    str = new char[BLOCK_SIZE];
    hash_array = new unsigned char[EVP_MAX_MD_SIZE];
  }

  ~SSLHashFile() {
    delete[] str;
    delete[] hash_array;
  }

  void newfile(const std::string &file) {
    sslHash.reset();
    reader.open(file);
    open = true;
  }

  typename SSLHash<t>::size_type read() {
    size_t str_size = reader.read(str);
    size_t hash_size = sslHash.digest(str, str_size, hash_array);
    if (reader.eof())
      close();
    return fromBigEndian<typename SSLHash<t>::size_type>(hash_array, hash_size);
  }

  std::string readHex() {
    size_t str_size = reader.read(str);
    size_t hash_size = sslHash.digest(str, str_size, hash_array);
    if (reader.eof())
      close();
    std::ostringstream oss;
    oss << std::setfill('0') << std::hex;
    for(size_t i = 0; i < hash_size; ++i) {
      oss << std::setw(2) << static_cast<unsigned>(hash_array[i]);
    }
    return oss.str();
  }

  bool isOpen() { return open; }

  void close() {
    reader.close();
    open = false;
  }
};
