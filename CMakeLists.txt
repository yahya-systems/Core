cmake_minimum_required(VERSION 3.20)
project(core-lib CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_executable(main main.cpp)
target_include_directories(main PRIVATE include/)

target_compile_features(main PRIVATE cxx_std_20)
