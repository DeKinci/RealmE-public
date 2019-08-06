cmake_minimum_required(VERSION 3.0)
project(lodepng)

add_library(lodepng include/lodepng.h src/lodepng.cpp)
target_include_directories(lodepng PUBLIC include/)
