find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(test_helloworld test.cpp)
set_target_properties(test_helloworld PROPERTIES
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra")
target_link_libraries(test_helloworld hello ${Boost_LIBRARIES})

add_test(TestHelloWorld test_helloworld)
