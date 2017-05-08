project(Compiler CXX)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "-std=c++11")

add_executable(AST-test
	test.cpp
  AST/AST.cpp
  AST/eval.cpp
  AST/type_check.cpp
	)
  
add_executable(calc
  calculator.cpp
  AST/AST.cpp
  AST/eval.cpp
  AST/type_check.cpp
  lexer/lexer.cpp
  parser/parser.cpp
  lexer/symbol.cpp
  parser/decl.cpp
  parser/scope.cpp
  parser/statement.cpp
  lexer/token.cpp
  )

add_executable(generate_code
  codegen/codegen.cpp
  AST/AST.cpp
  AST/eval.cpp
  AST/type_check.cpp
  lexer/lexer.cpp
  parser/parser.cpp
  lexer/symbol.cpp
  parser/decl.cpp
  parser/scope.cpp
  parser/statement.cpp
  lexer/token.cpp
  codegen/llvm/llvm_gen.cpp
  )

set(files AST.cpp test.cpp eval.cpp type_check.cpp lexer.cpp)

add_custom_target(printout
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMAND a2ps -Afill -o- ${files} | ps2pdf - ${CMAKE_BINARY_DIR}/printout.pdf)