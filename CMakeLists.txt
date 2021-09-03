# Set the minimum cmake version. 3.7.2 is needed to support Clang-Tidy
# integration. 3.8 is needed to support C++17
cmake_minimum_required(VERSION 3.8)

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
  # "CMAKE_FORMAT_EXCLUDE cmake/CPM.cmake")
)

# This requires at least CMake 3.8 Set the standard for C++ to 17 and require
# that it be available
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# This is used to enable conan integration.
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
# TARGETS must be passed to this so that you can link using CONAN_PKG::<pkg>
conan_basic_setup(TARGETS)

include_directories(include/public include/private)

# Find the doxygen package
find_package(Doxygen REQUIRED dot)

doxygen_add_docs(doc ${PROJECT_SOURCE_DIR} "Generate documentation"
                 DOXYGEN_EXCLUDE_PATTERNS */test/*)

# Include the source subdirectory for the application and libraries
add_subdirectory(src)

# Enable the CMake testing functionality
enable_testing()

# Include the test subdirectory that will run the unit tests
add_subdirectory(test)
