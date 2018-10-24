project(helloworld VERSION 0.0.${PATCH})

configure_file(version.h.in version.h @ONLY)

include_directories(
   ${CMAKE_CURRENT_SOURCE_DIR}
   ${CMAKE_CURRENT_BINARY_DIR})

add_library(hello hello.cpp hello.h)

add_executable(helloworld main.cpp)
set_target_properties(helloworld hello PROPERTIES
  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra")
target_link_libraries(helloworld hello)

install(TARGETS helloworld RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_NAME helloworld)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER sanblch)

include(CPack)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
