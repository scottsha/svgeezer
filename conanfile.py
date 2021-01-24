from conans import ConanFile, CMake

class SvgeezerConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "opencv/4.5.1", \
                "boost/1.75.0"
    generators = "cmake", "gcc", "txt"
    # default_options = {"opencv:shared": True, "boost:shared": True}

    # def imports(self):
    #     self.copy("*.dll", dst="bin", src="bin") # From bin to bin
    #     self.copy("*.dylib*", dst="bin", src="lib") # From lib to bin