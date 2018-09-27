#include "hello.h"

std::string version() {
  return std::to_string(PROJECT_VERSION_MAJOR) + "." +
    std::to_string(PROJECT_VERSION_MINOR) + "." +
    std::to_string(PROJECT_VERSION_PATCH);
}
