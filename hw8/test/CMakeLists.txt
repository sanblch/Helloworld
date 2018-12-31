find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(test_hashing test.cpp)
set_target_properties(test_hashing PROPERTIES
  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra")
target_link_libraries(test_hashing ${Boost_LIBRARIES} OpenSSL::SSL)

add_test(TestHashing test_hashing)
