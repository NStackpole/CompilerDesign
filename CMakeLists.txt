project(Compiler CXX)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "-std=c++11")

add_executable(AST-test
	test.cpp
  AST.cpp
  eval.cpp
  type_check.cpp
	)
  
add_executable(calc
  calculator.cpp
  AST.cpp
  eval.cpp
  type_check.cpp
  lexer.cpp
  parser.cpp
  symbol.cpp
  decl.cpp
  scope.cpp
  statement.cpp
  )

set(files AST.cpp test.cpp eval.cpp type_check.cpp lexer.cpp)

add_custom_target(printout
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMAND a2ps -Afill -o- ${files} | ps2pdf - ${CMAKE_BINARY_DIR}/printout.pdf)