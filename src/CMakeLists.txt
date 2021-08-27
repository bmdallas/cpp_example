# We will split the project into a library and an executable
# by doing this, unit testing is easier because the library
# can be linked into both the unit test and the executable

# Set up a variable to hold the example sources, this can be
# convenient if you end up needing them for something else later
set(example_sources
    example.cpp
)

# Add a library target that compiles the example_sources into a
# library called example_lib. On Linux this will turn into
# libexample.[so,a] depeding on if it is shared or static
add_library(example
    ${example_sources}
)

# Add an executable target (exe_example) that compiles main.cpp into an executable
add_executable(exe_example
    main.cpp
)

# Ensure that the executable links against the example target library
target_link_libraries(exe_example
    example
)
