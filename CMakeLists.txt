cmake_minimum_required(VERSION 3.10)

set(This warships)

project(${This}
VERSION 1.1.1
DESCRIPTION "warships game in cpp"
LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

file(GLOB Sources "src/*.cpp")
file(GLOB Headers "include/*.h")
add_library(warships_object STATIC ${Sources} ${Headers})
add_executable(${This} ${Sources})

enable_testing()
add_subdirectory(external)
add_subdirectory(tests)
add_dependencies(${This} run_tests)
