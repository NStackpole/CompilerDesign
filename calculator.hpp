#include "lexer.hpp"
#include "AST.hpp"
#include "eval.hpp"
#include <vector>
#include <iostream>
#include <string>

//Calculates and prints the value of an expression
void calculate(std::vector<token *>);

//performs lexical analysis on a line
std::vector<token *> lex_line(char*);