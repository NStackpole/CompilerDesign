//Nathan Stackpole, 2017

#include "statement.hpp"

expr_statement::expr_statement(expr *e) : expression(e) 
{}

decl_statement::decl_statement(decl *d) : entity(d)
{}