#include "../logging_allocator.h"
#include "../thecontainer.h"

#define BOOST_TEST_MODULE test_allocator

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_suite_allocator)

void check_counters(unsigned val) {
  BOOST_CHECK(logging_allocator<TheContainerItem<int>>::allocated == val);
  BOOST_CHECK(logging_allocator<TheContainerItem<int>>::deallocated == val);
  BOOST_CHECK(logging_allocator<TheContainerItem<int>>::constructed == val);
  BOOST_CHECK(logging_allocator<TheContainerItem<int>>::destroyed == val);
}

void reset_counters() {
  logging_allocator<TheContainerItem<int>>::allocated = 0;
  logging_allocator<TheContainerItem<int>>::deallocated = 0;
  logging_allocator<TheContainerItem<int>>::constructed = 0;
  logging_allocator<TheContainerItem<int>>::destroyed = 0;
}

void print_counters() {
  std::cout << logging_allocator<TheContainerItem<int>>::allocated << std::endl;
  std::cout << logging_allocator<TheContainerItem<int>>::deallocated << std::endl;
  std::cout << logging_allocator<TheContainerItem<int>>::constructed << std::endl;
  std::cout << logging_allocator<TheContainerItem<int>>::destroyed << std::endl;
}

BOOST_AUTO_TEST_CASE(test_allocator_basic) {
  reset_counters();
  {
    auto c = TheContainer<int, logging_allocator<int>>{};
    c.push_back(1);
  }
  check_counters(1);
}

BOOST_AUTO_TEST_CASE(test_allocator_copy) {
  reset_counters();
  {
    auto c1 = TheContainer<int, logging_allocator<int>>{};
    c1.push_back(1);
    c1.push_back(2);
    auto c2 = TheContainer<int, logging_allocator<int>>{c1};
  }
  check_counters(4);
}

BOOST_AUTO_TEST_CASE(test_allocator_move) {
  reset_counters();
  {
    auto c1 = TheContainer<int, logging_allocator<int>>{};
    c1.push_back(1);
    c1.push_back(2);
    c1.push_back(3);
    auto c2 = TheContainer<int, logging_allocator<int>>{std::move(c1)};
    BOOST_CHECK(c1.begin() == c1.end());
    auto it = c2.begin();
    BOOST_CHECK(*it == 1);
    BOOST_CHECK(*(++it) == 2);
    BOOST_CHECK(*(++it) == 3);
  }
  check_counters(3);
}

BOOST_AUTO_TEST_SUITE_END()

