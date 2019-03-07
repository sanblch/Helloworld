#include "../bulk.h"
#include "../commander.h"
#include <iostream>

#define BOOST_TEST_MODULE test_bulk

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_suite_bulk)

BOOST_AUTO_TEST_CASE(test_cmd) {
  std::istringstream iss("anystring\n");
  Cmd cmd;
  iss >> cmd;
  BOOST_CHECK(cmd.str == "anystring");
}

void check_bulk(const Bulk& blk, const std::string& str) {
  std::ostringstream oss;
  oss << blk;
  BOOST_CHECK(oss.str() == str);
}

BOOST_AUTO_TEST_CASE(test_bulk) {
  check_bulk({}, "");
  check_bulk({{{""}}}, "bulk: ");
  check_bulk({{{"cmd1"}}}, "bulk: cmd1");
  check_bulk({{{"cmd1"}, {"cmd2"}, {"cmd3"}}}, "bulk: cmd1, cmd2, cmd3");
}

void check_commands(const std::string& in, const std::string& out) {
  std::istringstream iss(in);
  CommandReceiver receiver(iss);
  std::ostringstream oss;
  CommandSender sender(oss);
  receiver.addObserver(sender);
  receiver.startReceiving();
  std::cout << oss.str() << std::endl;
  std::cout << out << std::endl;
  BOOST_CHECK(oss.str() == out);
}

BOOST_AUTO_TEST_CASE(test_commands) {
  check_commands("", "");
  check_commands("\n", "bulk: \n");
  check_commands("\n\n", "bulk: , \n");
  check_commands("cmd1\ncmd2", "bulk: cmd1, cmd2\n");
  check_commands("cmd1\ncmd2\n", "bulk: cmd1, cmd2\n");
  check_commands("cmd1\n", "bulk: cmd1\n");
  check_commands("cmd1\n\ncmd3\n", "bulk: cmd1, , cmd3\n");
}

BOOST_AUTO_TEST_CASE(test_multicommands) {
  check_commands("{\ncmd1\n}", "bulk: cmd1\n");
  check_commands("{\ncmd1\ncmd2\n}", "bulk: cmd1, cmd2\n");
  check_commands("{\ncmd1\ncmd2\n}\n{\ncmd3\ncmd4\n}",
                 "bulk: cmd1, cmd2\nbulk: cmd3, cmd4\n");
  check_commands("cmd1\ncmd2\n{\ncmd3\ncmd4\n}",
                 "bulk: cmd1, cmd2\nbulk: cmd3, cmd4\n");
  check_commands("{\ncmd1\ncmd2\n}\ncmd3\ncmd4\n",
                 "bulk: cmd1, cmd2\nbulk: cmd3, cmd4\n");
  check_commands("{\ncmd1\n{\ncmd2\ncmd3\n}\ncmd4\n}\ncmd3\ncmd4\n",
                 "bulk: cmd1, cmd2, cmd3, cmd4\nbulk: cmd3, cmd4\n");
  check_commands("{\ncmd1", "");
  check_commands("cmd1\n{\ncmd2\n{\ncmd3", "bulk: cmd1\n");
  check_commands("{\ncmd1\n{\ncmd2\n}\ncmd3", "");
}

BOOST_AUTO_TEST_SUITE_END()

