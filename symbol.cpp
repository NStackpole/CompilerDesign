//Nathan Stackpole, 2017

#include "symbol.hpp"

symbol *symbol_table::find(const std::string &str)
{
    auto result = symbols.find(str);
    return &result->first;
}

symbol *symbol_table::insert(const std::string &str)
{
    auto result = symbols.insert({str,nullptr});
    return &result.first->first;
}