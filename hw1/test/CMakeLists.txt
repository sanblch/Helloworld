find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(test1 test1.cpp)
set_target_properties(test1 PROPERTIES
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra")
target_link_libraries(test1 hello ${Boost_LIBRARIES})

add_test(TestHello test1)
