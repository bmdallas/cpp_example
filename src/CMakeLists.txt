# We will split the project into a library and an executable by doing this, unit
# testing is easier because the library can be linked into both the unit test
# and the executable

# This line requires CMake 3.7.2 minimum
set(CMAKE_CXX_CLANG_TIDY
    clang-tidy -header-filter=.
    -checks=clang-*,modernize-*,cppcoreguidelines-*,performance-*,google-*
    -warnings-as-errors=*)

# Set up a variable to hold the util_driver sources, this can be convenient if you
# end up needing them for something else later
set(util_driver_sources driver.cpp)

# Add a library target that compiles the util_driver_sources into a library called
# util_driver_lib. On Linux this will turn into libutil_driver.[so,a] depeding on if it
# is shared or static
add_library(util_driver ${util_driver_sources})

# Link our library against boost
target_link_libraries(util_driver CONAN_PKG::boost)

# Add an executable target (exe_util_driver) that compiles main.cpp into an
# executable
add_executable(exe_util_driver main.cpp)

# Ensure that the executable links against the util_driver target library and boost
target_link_libraries(exe_util_driver util_driver CONAN_PKG::boost)
