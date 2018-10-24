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
