from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps


class guiTestProjectRecipe(ConanFile):
    name = "gui_test_project"

    options = {
        "enableLog": [True, False],
        "fPIC": [True, False],
    }
    default_options = {
        "enableLog": False,
        "fPIC": True,
    }

    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"

    def requirements(self):
        self.requires("sdl/3.2.20", options={"shared": True})
        return

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)

        tc.variables["ENABLE_LOG"] = self.options["enableLog"]

        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        return

    def package_info(self):
        return
