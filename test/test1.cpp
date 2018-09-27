#include "hello.h"
#include <regex>

#define BOOST_TEST_MODULE test_hello

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_suite_hello)
BOOST_AUTO_TEST_CASE(test_version_valid) {
  std::regex re("\\d+[.]\\d+[.]\\d+");
  BOOST_CHECK(std::regex_match(version(), re));
}
BOOST_AUTO_TEST_SUITE_END()
