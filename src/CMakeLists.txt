# CMakeList.txt : CMake project for llvm-tutorial, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (llvm-tutorial "llvm-tutorial.cpp" "llvm-tutorial.h" "tokens.h" "tokens.cpp" "parser.h" "parser.cpp" Codegen.cpp Codegen.h Visitor.cpp Visitor.h)

# TODO: Add tests and install targets if needed.

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs support core irreader)

# Link against LLVM libraries
target_link_libraries(llvm-tutorial ${llvm_libs})