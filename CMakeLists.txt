# CMakeList.txt : CMake project for Calculator, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Calculator")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
# Add source to this project's executable.
add_executable (Calculator "Calculator.cpp" "Calculator.hpp" "Shared/Token.cpp" "Shared/Token.hpp" "Expression.cpp" "Expression.hpp" "StandartLexems.cpp" "StandartLexems.hpp" "ExpressionParser.cpp" "ExpressionParser.hpp" "RPNConverter.cpp" "RPNConverter.hpp" "Evaluator.cpp" "Evaluator.hpp"  "LexemePluginLoader.cpp" "LexemePluginLoader.hpp" "main.cpp")

# TODO: Add tests and install targets if needed.
# Example libraries.
add_subdirectory(trigonometry)
add_subdirectory(pow)