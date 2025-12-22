cmake_minimum_required(VERSION 3.10)


add_subdirectory(Common)
add_subdirectory(Event)
add_subdirectory(Framework)
add_subdirectory(Input)
add_subdirectory(Logger)
add_subdirectory(Render)
add_subdirectory(Winsys)

# A simple app which tests the framework
# TODO: move outside the project or replace with unit-tests
add_subdirectory(GuiTest)
