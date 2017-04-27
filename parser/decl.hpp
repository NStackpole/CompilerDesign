//Nathan Stackpole, 2017

#include "../AST/AST.hpp"
#include "../lexer/symbol.hpp"

#include <vector>

#ifndef DECL_HPP
#define DECL_HPP

struct decl
{
    expr *init;
    virtual ~decl() = default;
};

struct var_decl : decl
{
    var_decl(symbol *n, type *t);
    var_decl();

    symbol *name;
    type *typ;
    
};

#endif