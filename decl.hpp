//Nathan Stackpole, 2017

#include <vector>
#include "AST.hpp"
#include "symbol.hpp"

#ifndef DECL_HPP
#define DECL_HPP

struct decl
{
    virtual ~decl() = default;
};

struct var_decl : decl
{
    var_decl(symbol *n, type *t);
    var_decl();
    
    symbol *name;
    type *typ;
    expr *init;
};

#endif