//Nathan Stackpole, 2017

#include "decl.hpp"
#include "../lexer/symbol.hpp"

#include <unordered_map>

#ifndef SCOPE_HPP
#define SCOPE_HPP

struct scope
{
    void insert(symbol*, decl*);

    decl* find(symbol*);

    std::unordered_map<symbol*, decl*> map;
};


#endif