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

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
