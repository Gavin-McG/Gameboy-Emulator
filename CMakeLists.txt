cmake_minimum_required(VERSION 3.15)

# Set the project name
project(gb_emulator)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the executable target and its source file
add_executable(gb_emulator main.cpp)

# Define additional source files
target_sources(gb_emulator PRIVATE )

# Define include directories
target_include_directories(gb_emulator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
