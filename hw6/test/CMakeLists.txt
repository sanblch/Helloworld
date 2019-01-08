find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(test_bulk test.cpp)
set_target_properties(test_bulk PROPERTIES
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra")
target_link_libraries(test_bulk ${Boost_LIBRARIES})

add_test(TestBulk test_bulk)
