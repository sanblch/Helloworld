#include "files.h"
#include "hash.h"
#include "options.h"
#include <chrono>

template<HASHTYPE t>
void hash(const options& opt, const files& f) {
  Hasher<t> hasher(opt["block-size"].as<size_t>());
  for(auto i = f.begin(); i != f.end(); ++i) {
    hasher.hash(i->second);
  }
}

int main(int argc, const char* argv[]) {
  options opt;
  if(!get_options(argc, argv, opt))
    exit(0);

  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();

  paths d;
  paths e;
  get_paths(opt["dir"].as<std::vector<std::string>>(), d);
  if(opt.count("exclude"))
    get_exclude_paths(opt["exclude"].as<std::vector<std::string>>(), e);
  files f;
  size_t s = opt["size"].as<size_t>();
  if(opt.count("recursive"))
    get_files_recursive(d, e, f, s);
  else
    get_files(d, e, f, s);

  if(opt["hash-type"].as<std::string>() == "MD4")
    hash<HASHTYPE::MD4>(opt, f);
  else if(opt["hash-type"].as<std::string>() == "MD5")
    hash<HASHTYPE::MD5>(opt, f);
  else if(opt["hash-type"].as<std::string>() == "SHA1")
    hash<HASHTYPE::SHA1>(opt, f);
  else if(opt["hash-type"].as<std::string>() == "SHA224")
    hash<HASHTYPE::SHA224>(opt, f);
  else if(opt["hash-type"].as<std::string>() == "SHA256")
    hash<HASHTYPE::SHA256>(opt, f);
  else if(opt["hash-type"].as<std::string>() == "SHA384")
    hash<HASHTYPE::SHA384>(opt, f);
  else if(opt["hash-type"].as<std::string>() == "SHA512")
    hash<HASHTYPE::SHA512>(opt, f);
  if(opt["hash-type"].as<std::string>() == "RIPEMD160")
    hash<HASHTYPE::RIPEMD160>(opt, f);

  if(opt.count("time")) {
    end = std::chrono::system_clock::now();
    unsigned elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
    std::cout << "Elapsed " << elapsed_seconds / 60 << " minutes, "
              << elapsed_seconds % 60 << "seconds." << std::endl;
  }
}
