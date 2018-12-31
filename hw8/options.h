#pragma once

#include <iostream>
#include <boost/program_options.hpp>

using options = boost::program_options::variables_map;

bool get_options(int argc, const char* argv[], options& vm) {
  namespace boo = boost::program_options;
  try {
    boo::options_description desc{"Bayan usage"};
    desc.add_options()
      ("block-size,b", boo::value<size_t>()->default_value(2048), "Block size for hash algorithm (Bytes)")
      ("dir,d", boo::value<std::vector<std::string>>()->multitoken()->composing(), "Directories")
      ("exclude,e", boo::value<std::vector<std::string>>()->multitoken()->composing(), "Exclude directories")
      ("hash-type,H", boo::value<std::string>()->default_value("MD5"), "Hash algorithm: MD4, MD5, SHA1, SHA224, SHA256, SHA384, SHA512, RIPEMD160")
      ("help,h", "Help")
      ("recursive,r", "Recursive")
      ("size,s", boo::value<size_t>()->default_value(1), "File minimum size (Bytes)")
      ("time,t", "Show execution time");

    boo::positional_options_description pos_desc;
    pos_desc.add("dir", -1);

    boo::command_line_parser parser{argc, argv};
    parser.options(desc).positional(pos_desc).style(
        boo::command_line_style::default_style |
        boo::command_line_style::allow_dash_for_short);
    boo::parsed_options options = parser.run();

    boo::store(options, vm);
    boo::notify(vm);

    if (vm.count("help"))
      std::cout << desc << std::endl;
    else if (vm.count("dir")) {
      return true;
    } else
      throw boo::error("Directories are not passed");
  } catch(const boo::error& ex) {
    std::cerr << ex.what() << std::endl;
  }
  return false;
}
