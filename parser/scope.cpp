//Nathan Stackpole, 2017

#include "scope.hpp"

void scope::insert(std::string s, decl *d)
{
    map.insert({s, d});
}

void scope::modify(std::string s, decl *d)
{
    map[s] = d;
}

decl *scope::find(std::string s)
{
    auto iter = map.find(s);
    if(iter != map.end())
        return iter->second;
    else
        return nullptr;
}