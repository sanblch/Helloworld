#include "hello.h"

#define BOOST_TEST_MODULE test_hello

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_suite_hello)
BOOST_AUTO_TEST_CASE(test_version_valid) {
  BOOST_CHECK(PROJECT_VERSION_PATCH > 0);
}
BOOST_AUTO_TEST_SUITE_END()
