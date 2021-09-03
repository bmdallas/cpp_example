from conans import ConanFile, CMake, tools


class CppExampleConan(ConanFile):
    name = "cpp_example"
    version = "0.1.0"
    license = "GPLv3"
    author = "Bryan Dallas"
    url = "https://github.com/bmdallas/cpp_example"
    description = "Example C++ Code for Interviews"
    topics = ("C++", "Interview")
    requires = ("boost/1.76.0")
    build_requires = ("gtest/1.11.0")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    generators = "cmake"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def source(self):
        self.run("git clone https://github.com/bmdallas/cpp_example.git")

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder=".")
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include", src="include/public/")
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["example"]

