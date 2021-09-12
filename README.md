[![CI](https://github.com/bmdallas/cpp_example/actions/workflows/build.yml/badge.svg)](https://github.com/bmdallas/cpp_example/actions/workflows/build.yml)

C++ Example Driver Structure
============================
This is an example repository using C++ and lots of DevOps to create an ecosystem to develop standardized, tested, and documented code. The code in this repo implements the starting point for an Object-Oriented structure for user-space driver Object abstractions. The class ADriver is the base of all drivers, and allows for polymorphism across all drivers. The class CharacterDriver inherits from ADriver and implements the read and write functionality for a linux Character driver. This class should be inherited from to provide custom character driver implementations in user-space, that support extra functionality like IOCTL calls specific to the driver. 


Building the Code
=================
This repository uses a combination of Conan and CMake to build the C++ code. To build the code in this repository, run the following commands:

```bash
mkdir build
cd build
conan install ..
conan build ..
```

This repository supports other functions that are used in the DevOps pipeline such as:

```bash
make test
make check-format
make format
make fix-format
```

Manual Testing
==============
The main executable trys to write "Hello Driver!"  to a character device, then read from that device. For testing the Linux Device driver found [here](https://github.com/bmdallas/buffer-driver) is used. Here is an example of how to run the manual tests:

```bash
sudo insmod buffer-driver.ko
sudo exe_util_driver --device /dev/buffer_driver0
```

DevOps
======
This repository uses GitHub actions (see files in the .github folder) to build and test the code each time it is pushed to a merge request or the master branch. This pipeline builds the code, runs clang-tidy on the code, check formatting rules using clang-format, and runs tests using Google Test.

Other Information
=================
The project uses Conan for C++ dependency management (see conanfile.py and CMakeLists.txt). It is able to install any package from conan.io to use in building the project.

The project uses CMake to build the C++ files. CMake defaults to GNU make as the default generator and this is what is used here. CMake enables this project to set up targets to generate documentation, build libraries and executables, and run unit tests.

The unit tests in this project are developed using Google Test (which is provided by Conan), see the test folder.

The C++ code in this project is developed to the C++20 standard. This source creates a class structure that is designed to support generic Linux drivers. It currently implements a CharacterDriver class which allows the user to open and use the characters drivers in /dev. Not all functions are implemented to allow this, but the structure exists to show how it would be used. Another user of this library could inherit from CharacterDriver to implement extra functionality for a specific CharacterDriver as necessary.
