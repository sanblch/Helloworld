#pragma once

#include <boost/format.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

namespace ssl {
#include <openssl/evp.h>
} // namespace ssl

enum class HASHTYPE {
  MD4,
  MD5,
  SHA1,
  SHA224,
  SHA256,
  SHA384,
  SHA512,
  RIPEMD160
};

constexpr size_t HASHSIZE = static_cast<size_t>(HASHTYPE::RIPEMD160) + 1;

constexpr const char *const hashtype_str[HASHSIZE]{
    "MD4", "MD5", "SHA1", "SHA224", "SHA256", "SHA384", "SHA512", "RIPEMD160"};

constexpr const ssl::EVP_MD *(*hashtype_func[HASHSIZE])(){
    ssl::EVP_md4,    ssl::EVP_md5,    ssl::EVP_sha1,   ssl::EVP_sha224,
    ssl::EVP_sha256, ssl::EVP_sha384, ssl::EVP_sha512, ssl::EVP_ripemd160};

constexpr size_t hashtype_size[HASHSIZE]{16, 16, 20, 28, 32, 48, 64, 20};

template <HASHTYPE t> class SSLHash {
  const ssl::EVP_MD *md = nullptr;
  ssl::EVP_MD_CTX *md_ctx = nullptr;

public:
  using size_type =
      boost::multiprecision::number<boost::multiprecision::cpp_int_backend<
          hashtype_size[static_cast<size_t>(t)] * 8,
          hashtype_size[static_cast<size_t>(t)] * 8,
          boost::multiprecision::unsigned_magnitude,
          boost::multiprecision::unchecked, void>>;

  SSLHash() {
    auto hash = hashtype_str[static_cast<size_t>(t)];
    //    md = ssl::EVP_get_digestbyname(hash);
    md = hashtype_func[static_cast<size_t>(t)]();
    if (!md)
      throw std::runtime_error(
          (boost::format("Hashing algorithm %1% initialization error. IDs are "
                         "%2%, %3%.") %
           hash % ssl::OBJ_sn2nid(hash) % ssl::OBJ_ln2nid(hash))
              .str());
    md_ctx = ssl::EVP_MD_CTX_create();
    if (!md_ctx)
      throw std::runtime_error(
          "Hashing algorithm context initialization error.");
    EVP_DigestInit_ex(md_ctx, md, nullptr);
  }

  ~SSLHash() { ssl::EVP_MD_CTX_destroy(md_ctx); }

  unsigned digest(const char *block, size_t block_size, unsigned char *hash) {
    unsigned size;
    EVP_DigestUpdate(md_ctx, block, block_size);
    EVP_DigestFinal_ex(md_ctx, hash, &size);
    return size;
  }

  void reset() {
    EVP_MD_CTX_init(md_ctx);
    EVP_DigestInit_ex(md_ctx, md, nullptr);
  }
};
