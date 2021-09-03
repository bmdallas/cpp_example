[![CI](https://github.com/bmdallas/cpp_example/actions/workflows/build.yml/badge.svg)](https://github.com/bmdallas/cpp_example/actions/workflows/build.yml)

This is an example repository using C++ and lots of DevOps to create an ecosystem to develop standardized, tested, and documented code.

This repository uses GitHub actions (see files in the .github folder) to build and test the code each time it is pushed to a merge request or the master branch.

The project uses Conan for C++ dependency management (see conanfile.py and CMakeLists.txt). It is able to install any package from conan.io to use in building the project.

The project uses CMake to build the C++ files. CMake defaults to GNU make as the default generator and this is what is used here. CMake enables this project to set up targets to generate documentation, build libraries and executables, and run unit tests.

The unit tests in this project are developed using Google Test (which is provided by Conan), see the test folder.

The C++ code in this project is developed to the C++20 standard. This source creates a class structure that is designed to support generic Linux drivers. It currently implements a CharacterDriver class which allows the user to open and use the characters drivers in /dev. Not all functions are implemented to allow this, but the structure exists to show how it would be used. Another user of this library could inherit from CharacterDriver to implement extra functionality for a specific CharacterDriver as necessary.
