cmake_minimum_required(VERSION 3.0...4.1)

project(ease.hpp)

add_library(ease.hpp INTERFACE ease.hpp)
target_compile_features(ease.hpp INTERFACE cxx_std_17)
target_include_directories(ease.hpp INTERFACE .)
