//Nathan Stackpole, 2017

#ifndef CALC_HPP
#define CALC_HPP

#include "lexer.hpp"
#include "AST.hpp"
#include "eval.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <map>

//Extracts the variables and expression type from the tokens of the line
void calculate(std::vector<token *>);

//performs lexical analysis on a line
std::vector<token *> lex_line(char *, std::map<int, std::string> &);

//Creates an expression given an integer referring to the type of expression that needs to be made and the vectors holding the variables of the expr
//Prints out evaluation of expression
void create_expression(int, std::vector<Integer_expr *>, std::vector<Bool_expr *>);

#endif