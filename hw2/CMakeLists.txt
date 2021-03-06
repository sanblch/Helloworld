cmake_minimum_required(VERSION 3.2)

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PATCH 0)
if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
  set(PATCH $ENV{TRAVIS_BUILD_NUMBER})
endif()

enable_testing()

project(ip_filter VERSION 0.0.${PATCH})

include_directories(
   ${CMAKE_CURRENT_SOURCE_DIR}
   ${CMAKE_CURRENT_BINARY_DIR})

add_executable(ip_filter ip_filter.cpp)
set_target_properties(ip_filter PROPERTIES
  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra")

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_NAME ip_filter)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER sanblch)

include(CPack)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
