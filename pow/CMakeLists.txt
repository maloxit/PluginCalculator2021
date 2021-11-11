# CMakeList.txt : CMake project for pow, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../build/plugins)

project ("pow")
add_library(pow SHARED "pow.cpp" "../Shared/Token.cpp" "../Shared/Token.hpp")