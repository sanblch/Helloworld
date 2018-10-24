cmake_minimum_required(VERSION 3.2)

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PATCH 0)
if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
  set(PATCH $ENV{TRAVIS_BUILD_NUMBER})
endif()

enable_testing()

add_subdirectory(hw1)
