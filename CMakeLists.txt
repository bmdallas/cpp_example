# Set the minimum cmake version. There is nothing spectacular about this
# cmake structure so, 3.0 is more than enough
cmake_minimum_required(VERSION 3.0)

# Setup the name of the project
project(CPlusPlusCodingExample)

include_directories(include/public include/private)

# Include the source subdirectory for the application and libraries
add_subdirectory(src)

# Include the test subdirectory that will run the unit tests
add_subdirectory(test)
