cmake_minimum_required(VERSION 3.10)

project(warships)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Source files
file(GLOB SOURCES "src/*.cpp")

# Include directories
include_directories(include)

# Build executable
add_executable(warships ${SOURCES})
