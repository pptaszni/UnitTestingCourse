cmake_minimum_required(VERSION 3.0.0)
project(UnitTestingCourse)

enable_testing()
set(CMAKE_CXX_STANDARD 17)
option(ENABLE_TESTING "Builds unit and modular tests" ON)
option(BUILD_SHARED_LIBS "By default add_library will create shared library" ON)

# note that for production -02 optimization should be used and -g debug symbols removed
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -O -g -pthread")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)

add_definitions(-DENABLE_DEBUG)
add_subdirectory(src)
if (ENABLE_TESTING)
  add_subdirectory(tests)
endif()
