find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(test_matrix test.cpp)
set_target_properties(test_matrix PROPERTIES
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra")
target_link_libraries(test_matrix ${Boost_LIBRARIES})

add_test(TestMatrix test_matrix)
