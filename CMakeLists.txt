cmake_minimum_required(VERSION 2.6)

project(Orion2D)
include(FindPkgConfig)

# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -O3 -g -std=c++11 -Wno-cast-function-type" )

# message(STATUS "COMPILE OPTIONS : ${CMAKE_CXX_FLAGS}")

option(USE_VERBOSE "Verbose mode" ON)
message(STATUS "Verbose mode : ${USE_VERBOSE}")

if (USE_VERBOSE)
  add_definitions(-DVERBOSE)
endif()

set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/libs)

# find_package(Boost COMPONENTS filesystem system unit_test_framework REQUIRED)
# find_package(MPI REQUIRED)
# include_directories(${MPI_INCLUDE_PATH})

# Add Orion2D
add_subdirectory (${CMAKE_SOURCE_DIR}/src)

# Add exec partition
# add_subdirectory (${CMAKE_SOURCE_DIR}/src/?????)
