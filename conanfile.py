from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps


class TbaEngineRecipe(ConanFile):
    name = "tba_engine"

    options = {
        "enableLog": [True, False],
        "buildTests": [True, False],
        "fPIC": [True, False]
    }
    default_options = {
        "enableLog": False,
        "buildTests": False,
        "fPIC": True
    }

    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"

    def requirements(self):
        self.requires("sdl/3.2.20", options={"shared": True})
        return

    def build_requirements(self):
        self.test_requires("gtest/1.17.0")

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)

        tc.variables["ENABLE_LOG"] = self.options.enableLog
        tc.variables["BUILD_TESTS"] = self.options.buildTests

        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        return

    def package_info(self):
        return
