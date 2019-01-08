#pragma once

#include <sstream>
#include <string>
#include <vector>

struct Cmd {
  std::string str;
};

std::istream& operator>>(std::istream& is, Cmd& cmd) {
  is >> cmd.str;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Cmd& cmd) {
  os << cmd.str;
  return os;
}

struct Bulk {
  std::vector<Cmd> cmds;
  int init{0};
};

std::ostream& operator<<(std::ostream& os, const Bulk& blk) {
  if(blk.cmds.empty())
    return os;
  os << "bulk: ";
  for(auto it = blk.cmds.cbegin(); it != blk.cmds.cend(); ++it)
    os << (*it) << (it == blk.cmds.cend() - 1 ? "" : ", ");
  return os;
}
