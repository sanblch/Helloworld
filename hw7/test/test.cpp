#include "../nickname.h"
#include <fstream>

#define BOOST_TEST_MODULE test_nickname

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_suite_nickname)

BOOST_AUTO_TEST_CASE(test_empty) {
  RadixTree t;
  t.insert("");
  BOOST_CHECK(t.find("") == false);
  BOOST_CHECK(t.size() == 0);
}

BOOST_AUTO_TEST_CASE(test_basic) {
  RadixTree t;
  t.insert("name");
  BOOST_CHECK(t.size() == 1);
  BOOST_CHECK(t.find("name"));
  t.remove("name");
  BOOST_CHECK(t.size() == 0);
  BOOST_CHECK(t.find("name") == false);
}

BOOST_AUTO_TEST_CASE(test_insert) {
  RadixTree t;
  t.insert("name");
  t.insert("n");
  t.insert("na");
  t.insert("aname");
  t.insert("amome");
  BOOST_CHECK(t.find("aname"));
  BOOST_CHECK(t.find("amome"));
  BOOST_CHECK(t.find("anime") == false);
  BOOST_CHECK(t.find("name"));
  BOOST_CHECK(t.find("nam") == false);
  BOOST_CHECK(t.find("na"));
  BOOST_CHECK(t.find("n"));
}

BOOST_AUTO_TEST_CASE(test_print) {
  RadixTree t;
  t.insert("alek");
  t.insert("aleks");
  t.insert("aleksey");
  t.insert("alesha");
  t.insert("maksim");
  t.insert("sasha");
  BOOST_CHECK(t.find("ale") == false);
  BOOST_CHECK(t.find("alek"));
  BOOST_CHECK(t.find("aleks"));
  BOOST_CHECK(t.find("aleksey"));
  BOOST_CHECK(t.find("alesha"));
  BOOST_CHECK(t.find("maksim"));
  BOOST_CHECK(t.find("sasha"));
  std::ostringstream oss;
  t.print(oss);
  t.print_graph(oss);
  t.print_graph(oss, true);
  BOOST_CHECK(oss.str() == "aleksey alekse\n"
                           "aleks aleks\n"
                           "alek alek\n"
                           "alesha ales\n"
                           "maksim m\n"
                           "sasha s\n"
                           "ale\n"
                           "   k$\n"
                           "    s$\n"
                           "     ey$\n"
                           "   sha$\n"
                           "maksim$\n"
                           "sasha$\n"
                           "+ ale\n"
                           "| + k$\n"
                           "| | + s$\n"
                           "| |   + ey$\n"
                           "| + sha$\n"
                           "+ maksim$\n"
                           "+ sasha$\n");
}

BOOST_AUTO_TEST_CASE(test_by_dict) {
  std::ifstream ifs("dict.txt");
  std::string str;
  std::vector<std::string> res;
  RadixTree t;
  while(ifs >> str) {
    t.insert(str);
    res.push_back(str);
  }
  BOOST_CHECK(res.size() == 1000);
  for(const auto& str : res)
    BOOST_CHECK(t.find(str));
}

BOOST_AUTO_TEST_SUITE_END()

