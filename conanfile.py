from conans import ConanFile, CMake, tools

class FcdkConan(ConanFile):
    name = "fcdk"
    version = "1.0.0"
    license = "<Put the package license here>"
    author = "laurent Marzullo laurent.marzullo@gmai.com"
    url = ""
    description = "Fratal C++ Development kit"
    topics = ("C++")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    generators = "cmake", "cmake_find_package", "cmake_paths"


    def source(self):
        self.run("git clone https://github.com/lmarzull/fcdk.git")
        self.run("cd fcdk && git checkout devel")


    def requirements(self):
        self.requires( "gtest/1.8.1@bincrafters/stable" )


    def build(self):
        cmake = CMake(self)
        cmake.configure( source_folder="fcdk", defs = {"ENABLE_TESTING": True} )
        cmake.build()

