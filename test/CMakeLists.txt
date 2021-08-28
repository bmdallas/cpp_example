include(GoogleTest)

# Create a Google Test executable
add_executable(example_test
    test_example.cpp
)

target_link_libraries(example_test
    CONAN_PKG::gtest
    pthread
)

# Add the Google Test executable as a CMake test
gtest_discover_tests(example_test
    DISCOVERY_MODE POST_BUILD
)
