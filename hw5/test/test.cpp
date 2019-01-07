#include "../matrix.h"

#define BOOST_TEST_MODULE test_matrix

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_suite_matrix)

BOOST_AUTO_TEST_CASE(test_matrix_basic) {
  Matrix<int, -1> matrix;
  BOOST_CHECK(matrix.size() == 0);

  auto a = matrix[0][0];
  BOOST_CHECK(a == -1);
  BOOST_CHECK(matrix.size() == 0);

  matrix[100][100] = 314;
  BOOST_CHECK(matrix[100][100] == 314);
  BOOST_CHECK(matrix.size() == 1);

  matrix[100][100] = -1;
  BOOST_CHECK(matrix.size() == 0);
}

BOOST_AUTO_TEST_CASE(test_matrix_functionality) {
  Matrix<int, 0, 3> matrix;
  ((matrix[100][100][100] = 314) = 0) = 217;
  BOOST_CHECK(matrix.size() == 1);
  BOOST_CHECK(matrix[100][100][100] == 217);
}

BOOST_AUTO_TEST_SUITE_END()

