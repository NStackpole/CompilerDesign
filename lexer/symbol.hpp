//Nathan Stackpole, 2017

#include <string>
#include <unordered_map>

#ifndef SYMBOL_HPP
#define SYMBOL_HPP

using symbol = const std::string;

class symbol_table
{
    std::unordered_map<std::string, void*> symbols;

    public:
    
    symbol* find(const std::string&);
    symbol* insert(const std::string&);
};

#endif