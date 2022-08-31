from conans import ConanFile, CMake

class AwesomeProjectConan(ConanFile):
   settings = "os", "compiler", "build_type", "arch"
   requires = ("fmt/9.0.0" , "grpc/1.48.0")
   generators = "CMakeToolchain", "CMakeDeps"

   def imports(self):
       self.copy("*.dll", dst="bin", src="bin") # From bin to bin
       self.copy("*.dylib*", dst="bin", src="lib") # From lib to bin

   def configure(self):
       self.options["fmt"].shared = True

   def build(self):
       cmake = CMake(self)
       cmake.configure()
       cmake.build()
