//Nathan Stackpole, 2017

#ifndef CALC_HPP
#define CALC_HPP

#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "AST/AST.hpp"
#include "AST/eval.hpp"
#include <vector>
#include <iostream>
#include <string>

//Extracts the variables and expression type from the tokens of the line
void calculate(std::vector<token *> &, symbol_table *);

//performs lexical analysis on a line
std::vector<token *> lex_line(char *, std::unordered_map<int, std::string> &, keyword_table *, symbol_table *);

#endif