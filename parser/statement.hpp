//Nathan Stackpole, 2017

#include "decl.hpp"
#include "../AST/AST.hpp"

#ifndef STMT_HPP
#define STMT_HPP

struct statement
{
    virtual ~statement() = default;
};

struct expr_statement : statement
{
    expr_statement(expr *);

    expr *expression;
};

struct decl_statement : statement
{
    decl_statement(decl *);

    decl *entity;
};

struct if_statement : statement
{
    if_statement(expr *, statement *, statement *);

    expr *condition;
    statement *stmt1;
    statement *stmt2;
};

#endif