cmake_minimum_required(VERSION 3.10)

set(This warships)

project(${This}
VERSION 1.1.1
DESCRIPTION "warships game in cpp"
LANGUAGES CXX)

# enable tests
enable_testing()

# add google test
add_subdirectory(external)



# Set C++ standard
set(CMAKE_CXX_STANDARD 11)


file(GLOB Sources "src/*.cpp")
file(GLOB Headers "include/*.h")
add_library(warhsips_object STATIC ${Sources} ${Headers})

# Build executable
add_executable(${This} ${Sources})



# add tests directory
add_subdirectory(tests)

