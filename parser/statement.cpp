//Nathan Stackpole, 2017

#include "statement.hpp"

expr_statement::expr_statement(expr *e) : expression(e) 
{}

decl_statement::decl_statement(decl *d) : entity(d)
{}

if_statement::if_statement(expr *cond, statement *s1, statement *s2) : condition(cond), stmt1(s1), stmt2(s2)
{}