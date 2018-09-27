cmake_minimum_required(VERSION 3.2)

set(PATCH 0)
if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
  set(PATCH $ENV{TRAVIS_BUILD_NUMBER})
endif()

project(Helloworld VERSION 0.0.${PATCH})

enable_testing()

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file(version.h.in version.h @ONLY)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR})

add_library(hello hello.cpp hello.h)

add_executable(Helloworld main.cpp)
add_compile_options(-Wpedantic -Wall -Wextra)
target_link_libraries(Helloworld hello)

install(TARGETS Helloworld RUNTIME DESTINATION bin)

include(CPack)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
