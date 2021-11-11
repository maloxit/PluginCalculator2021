# CMakeList.txt : CMake project for trigonometry, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../build/plugins)

project ("trigonometry")
add_library(trigonometry SHARED "trigonometry.cpp" "../Shared/Token.cpp" "../Shared/Token.hpp")