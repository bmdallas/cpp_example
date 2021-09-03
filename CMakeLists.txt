# Set the minimum cmake version. There is nothing spectacular about this cmake
# structure so, 3.0 is more than enough
cmake_minimum_required(VERSION 3.0)

# Setup the name of the project
project(CPlusPlusCodingExample)

# CMake Package Management
include(cmake/CPM.cmake)

# Add the CMake Format package from TheLartians
cpmaddpackage(
  NAME
  Format.cmake
  VERSION
  1.7.0
  GITHUB_REPOSITORY
  TheLartians/Format.cmake
  OPTIONS # set to yes skip cmake formatting
  "FORMAT_SKIP_CMAKE NO"
  # path to exclude (optional, supports regular expressions)
  "CMAKE_FORMAT_EXCLUDE cmake/CPM.cmake")

# This is used to enable conan integration.
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
# TARGETS must be passed to this so that you can link using CONAN_PKG::<pkg>
conan_basic_setup(TARGETS)

include_directories(include/public include/private)

# Include the source subdirectory for the application and libraries
add_subdirectory(src)

# Enable the CMake testing functionality
enable_testing()

# Include the test subdirectory that will run the unit tests
add_subdirectory(test)
