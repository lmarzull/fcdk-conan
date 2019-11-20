import os
from conans import ConanFile, CMake, tools


class FcdkTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake", "cmake_find_package", "cmake_paths"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def config_options(self):
        self.settings.compiler.libcxx = "libstdc++11"

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="bin", src="lib")
        self.copy('*.so*', dst='bin', src='lib')

    def test(self):
        if not tools.cross_building(self.settings):
            os.chdir("bin")
            self.run(".%stest-fcdk" % os.sep)
