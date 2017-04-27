//Nathan Stackpole, 2017

#include "scope.hpp"

void scope::insert(symbol *s, decl *d)
{
    map.insert({s, d});
}

decl *scope::find(symbol *s)
{
    auto iter = map.find(s);
    if(iter != map.end())
        return iter->second;
    else
        return nullptr;
}