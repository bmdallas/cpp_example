include(GoogleTest)

# Create a Google Test executable
add_executable(util_driver_test test_util_driver.cpp)

target_link_libraries(util_driver_test CONAN_PKG::gtest pthread)

# Add the Google Test executable as a CMake test
gtest_discover_tests(util_driver_test DISCOVERY_MODE POST_BUILD)
