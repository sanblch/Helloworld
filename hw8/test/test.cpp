#include "../sslhashfile.h"
#include <algorithm>
#include <array>
#include <cstring>
#include <fstream>
#include <map>

#include <boost/test/included/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>

namespace b = boost::unit_test;

constexpr const unsigned DATASIZE = 2;
constexpr const char* const files[] {"1.txt", "2.txt"};

void gen_files() {
  const char* data[] = {"", "zvezda1"};
  std::ofstream ofs{};
  for(unsigned i = 0; i < DATASIZE; ++i) {
    ofs.open(files[i], std::ios::binary);
    ofs << data[i];
    ofs.close();
  }
}

constexpr const char *const md5ans[]{"d41d8cd98f00b204e9800998ecf8427e",
                                     "e70f0b0ca9cd626a405b3559709e6ea6"};
constexpr const char *const sha256ans[]{
    "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
    "bee4f2e30af30e145089ac66ff8c4829ff26e5982f974d8b015a41391a089935"};
constexpr const char *const sha512ans[]{
    "cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce47d0d13c5d"
    "85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e",
    "09de5b282604b48566adaa459e4640bc4825a9825d2761a8018690c9197809f384570e832c"
    "a9cf8fad218f671dae27f9da8172f4fb459350d76406c6da0da69b"};

std::map<HASHTYPE, const char *const (&)[DATASIZE]> ans = {
    {HASHTYPE::MD5, md5ans},
    {HASHTYPE::SHA256, sha256ans},
    {HASHTYPE::SHA512, sha512ans}};

template<HASHTYPE t>
void test_algo_hashing(unsigned i) {
  SSLHashFile<t> hash(64);
  hash.newfile(std::string(files[i], std::strlen(files[i])));
  BOOST_CHECK(hash.readHex() == ans.at(t)[i]);
}

#ifndef BOOST_TEST_ALTERNATIVE_INIT_API
b::test_suite* init_unit_test_suite(int, char*[]) {
#else
bool init_unit_test() {
#endif
  gen_files();
  std::array<unsigned, DATASIZE> params;
  std::iota(params.begin(), params.end(), 0);
  b::test_suite* ts1 = BOOST_TEST_SUITE("test_hashing");
  ts1->add(BOOST_PARAM_TEST_CASE(&test_algo_hashing<HASHTYPE::MD5>, params.begin(), params.end()));
  ts1->add(BOOST_PARAM_TEST_CASE(&test_algo_hashing<HASHTYPE::SHA256>, params.begin(), params.end()));
  ts1->add(BOOST_PARAM_TEST_CASE(&test_algo_hashing<HASHTYPE::SHA512>, params.begin(), params.end()));
  b::framework::master_test_suite().add(ts1);
#ifndef BOOST_TEST_ALTERNATIVE_INIT_API
  return nullptr;
#else
  return true;
#endif
}
