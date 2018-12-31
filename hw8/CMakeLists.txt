cmake_minimum_required(VERSION 3.2)

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PATCH 0)
if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
  set(PATCH $ENV{TRAVIS_BUILD_NUMBER})
endif()

enable_testing()

project(bayan VERSION 0.0.${PATCH})

find_package(Boost 1.40 COMPONENTS
  filesystem REQUIRED
  program_options REQUIRED)
find_package(OpenSSL)

add_executable(${PROJECT_NAME} main.cpp
  files.h
  hash.h
  ifs.h
  options.h
  sslhashfile.h
  sslhash.h)

set_target_properties(${PROJECT_NAME} PROPERTIES
  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra")

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} OpenSSL::SSL)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_DEBIAN_PACKAGE_DEPENDS
  "libboost-filesystem1.58.0, libboost-program-options1.58.0, libssl1.0.0")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER alexk)

include(CPack)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
