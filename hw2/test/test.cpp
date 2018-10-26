#define BOOST_TEST_MODULE test_hello

#include <ip.h>
#include <boost/test/unit_test.hpp>
#include <sstream>

BOOST_AUTO_TEST_SUITE(test_suite_ip_filter)
BOOST_AUTO_TEST_CASE(test_ip_io) {
  std::string str = "192.168.0.1";
  std::istringstream iss(str);
  IP ip;
  iss >> ip;
  std::ostringstream oss;
  oss << ip;
  BOOST_TEST(str == oss.str());
}
BOOST_AUTO_TEST_SUITE_END()
