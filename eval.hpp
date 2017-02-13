//Nathan Stackpole

#ifndef EVAL_HPP
#define EVAL_HPP

#include "AST.hpp"
#include <limits>
#include <iostream>
#include <cassert>

//Evaluates an expr. If Integer overflow, modular division by 0 or int_min, and division by zero or int_min will throw an exception and abort the program
//Takes an expr pointer, returns an int (the value of evaluation, either an integer value or a 0/1 representing a bool)
int eval(expr *);

#endif