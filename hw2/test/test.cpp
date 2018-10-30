#define BOOST_TEST_MODULE test_ip_filter

#include <ip_pool.h>
#include <boost/test/unit_test.hpp>
#include <sstream>

template<typename T>
void read(const std::string& in, const T& out) {
  std::istringstream iss(in);
  T t;
  iss >> t;
  BOOST_CHECK(t == out);
}

template<typename T>
void readwrite(const std::string& in, const std::string& out) {
  std::istringstream iss(in);
  T t;
  iss >> t;
  std::ostringstream oss;
  oss << t;
  BOOST_CHECK(oss.str() == out);
}

BOOST_AUTO_TEST_SUITE(test_suite_ip_filter)

BOOST_AUTO_TEST_CASE(test_ip_io) {
  readwrite<IP>("192.168.0.1", "192.168.0.1");
}

BOOST_AUTO_TEST_CASE(test_ip_cmp) {
  IP ip1 {{"192", "168", "0", "1"}};
  IP ip2 {{"193", "168", "0", "1"}};
  IP ip3 {{"192", "169", "0", "1"}};
  IP ip4 {{"192", "168", "1", "1"}};
  IP ip5 {{"192", "168", "0", "2"}};
  BOOST_CHECK(ip2 < ip1);
  BOOST_CHECK(ip3 < ip1);
  BOOST_CHECK(ip4 < ip1);
  BOOST_CHECK(ip5 < ip1);
  BOOST_CHECK(!(ip1 < ip1));
  BOOST_CHECK(!(ip1 < ip2));
  BOOST_CHECK(!(ip1 < ip3));
  BOOST_CHECK(!(ip1 < ip4));
  BOOST_CHECK(!(ip1 < ip5));
}

BOOST_AUTO_TEST_CASE(test_ip_lexicography) {
  IP ip1 {{"192", "168", "0", "1"}};
  IP ip2 {{"22", "168", "0", "1"}};
  IP ip3 {{"3", "169", "0", "1"}};
  BOOST_CHECK(ip1 < ip2);
  BOOST_CHECK(ip2 < ip3);
  BOOST_CHECK(ip1 < ip3);
  BOOST_CHECK(!(ip2 < ip1));
  BOOST_CHECK(!(ip3 < ip2));
  BOOST_CHECK(!(ip3 < ip1));
}

BOOST_AUTO_TEST_CASE(test_ip_parse) {
  read("192.168.0.1", IP({{"192", "168", "0", "1"}}));
  read(".168.0.1", IP({{"", "168", "0", "1"}}));
  read("192.168.0.", IP({{"192", "168", "0", ""}}));
  read("192..0.1", IP({{"192", "", "0", "1"}}));
  read("192.168..1", IP({{"192", "168", "", "1"}}));
  read("..0.1", IP({{"", "", "0", "1"}}));
  read("192.168..", IP({{"192", "168", "", ""}}));
  read("192...1", IP({{"192", "", "", "1"}}));
  read(".168.0.", IP({{"", "168", "0", ""}}));
  read(".168..1", IP({{"", "168", "", "1"}}));
  read("192..0.", IP({{"192", "", "0", ""}}));
  read("...1", IP({{"", "", "", "1"}}));
  read("192...", IP({{"192", "", "", ""}}));
  read(".168..", IP({{"", "168", "", ""}}));
  read("..0.", IP({{"", "", "0", ""}}));
  read("...", IP({{"", "", "", ""}}));
}

BOOST_AUTO_TEST_CASE(test_ip_pool_io) {
  readwrite<IPPool>("192.168.0.1 bla bla\n192.168.0.2 bla bla",
                    "192.168.0.1\n192.168.0.2\n");
}

BOOST_AUTO_TEST_SUITE_END()
