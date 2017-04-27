//Nathan Stackpole, 2017

#include "decl.hpp"
#include "../lexer/symbol.hpp"

#include <unordered_map>

#ifndef SCOPE_HPP
#define SCOPE_HPP

struct scope
{
    void insert(std::string, decl*);

    decl* find(std::string);

    std::unordered_map<std::string, decl*> map;
};


#endif