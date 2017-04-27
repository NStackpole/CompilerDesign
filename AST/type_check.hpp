//Nathan Stackpole, 2017

#ifndef TYPE_HPP
#define TYPE_HPP

#include <cassert>
#include "AST.hpp"

//Checks the type of an expr using the visitor pattern. Returns a type* to the proper type for the expr.
//Will abort if the expr members of the expr are not of the right type for the expr.
//Takes a Context refernce and an expr pointer, returns a type pointer
type *check(Context &, expr *);

#endif