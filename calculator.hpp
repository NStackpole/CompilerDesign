#include "lexer.hpp"
#include "AST.hpp"
#include "eval.hpp"
#include <vector>
#include <iostream>

//Calculates and prints the value of an expression
void calculate();

//performs lexical analysis on a line
std::vector<token *> lex_line(std::string);