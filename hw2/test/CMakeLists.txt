find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(test_ip_filter test.cpp)
set_target_properties(test_ip_filter PROPERTIES
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra")
target_link_libraries(test_ip_filter ${Boost_LIBRARIES})

add_test(TestIPFilter test_ip_filter)
