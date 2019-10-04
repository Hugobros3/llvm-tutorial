# CMakeList.txt : CMake project for llvm-tutorial, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (llvm-tutorial "llvm-tutorial.cpp" "llvm-tutorial.h" "tokens.h" "tokens.cpp" "parser.h" "parser.cpp")

# TODO: Add tests and install targets if needed.
