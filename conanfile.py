from conans import ConanFile, CMake, tools


class FcdkConan(ConanFile):
    name = "fcdk"
    version = "1.0"
    license = "<Put the package license here>"
    author = "laurent Marzullo laurent.marzullo@gmai.com"
    url = "<Package recipe repository url here, for issues about the package>"
    description = "Fratal C++ Development kit"
    topics = ("C++")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    generators = "cmake"

    def source(self):
        self.run("git clone https://github.com/lmarzull/fcdk.git")


    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder="fcdk")
        cmake.build()

        # Explicit way:
        # self.run('cmake %s/hello %s'
        #          % (self.source_folder, cmake.command_line))
        # self.run("cmake --build . %s" % cmake.build_config)

    def package(self):
        self.copy("*.h", dst="include/fcdk", src="fcdk/src/fcdk")

    def package_info(self):
        self.cpp_info.libs = ["fcdk"]

