Yet another game engine. Again.

# Build

The project uses `Conan` package manager on top of `CMake`. The dependencies and supported build options can be viewed in [`conanfile.py`](https://github.com/master-clown/TbaEngine/blob/main/conanfile.py).

## `Conan` profiles

Use [`generate-conan-profiles.sh`](https://github.com/master-clown/TbaEngine/blob/main/generate-conan-profiles.sh) to generate the profiles, which contain the stable build config. Handle the resulting
profile files in accordance with `Conan` documentation. 

## Building

The build command is standard:

```
conan build -bf=${BUILD_DIR} \
    --profile:all=${CONAN_PROFILE_NAME} \
    -o "&:enableLog=${ENABLE_LOG}" \
    -o "&:buildTests=${BUILD_TESTS}" \
    ${SRC_DIR}
```

## Supported systems

As of now, the project is developed and tested on Linux platforms. Supposedly, it should be fine on other platforms
supported by the project dependencies.

# Usage

The client can use [`Application`](https://github.com/master-clown/TbaEngine/blob/main/src/Framework/Framework/include/Framework/Application.h) or [`RenderApplication`](https://github.com/master-clown/TbaEngine/blob/main/src/Framework/Framework/include/Framework/RenderableApplication.h) as a base class for his own application. The interfaces of these
base classes represent the standard well-known organization of games and graphical apps (`create -> main_loop { iterate -> render } -> quit`).

Every single engine component exists as a CMake target, with explicitly declared dependencies and features. Link the
component you need with `target_link_libraries()` in CMake, and that should be enough to make it available to you.

The leading reference principles in devising the components architecture are SRP, YAGNE, KISS. One can expect this from
any component, otherwise the violation should be amended.

## Deployment

The proper and convenient way of the engine deployment is TBD, for now it is just a bunch of libraries. 

## Documentation

Not the main priority, apart from the mandatory UMLs for each engine component, which should demonstrate the
architecture, connection with other components, and some aspects of implementation (optionally).

To get started, see
[`uml/general-view.puml`](https://github.com/master-clown/TbaEngine/blob/main/uml/general-view.puml).

## Examples

See [`test/`](https://github.com/master-clown/TbaEngine/tree/main/test) folder.

Also there is a number of tests available via `ctest`, which are brought by some components. There are two types of
tests (given here by their `ctest` labels)
- `UnitTests`
- `ManualGuiTests` - for the cases when it is hard to devise a unit test. Examples: keyboard event checking, rendering
  tests.
