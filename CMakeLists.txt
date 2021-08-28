# Set the minimum cmake version. There is nothing spectacular about this
# cmake structure so, 3.0 is more than enough
cmake_minimum_required(VERSION 3.0)

# Setup the name of the project
project(CPlusPlusCodingExample)

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
