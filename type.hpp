//Nathan Stackpole

#ifndef TYPE_HPP
#define TYPE_HPP

#include <cassert>
#include "AST.hpp"

//Base type class
struct type
{
    struct Visitor;
    virtual ~type() = default;
    virtual void accept(Visitor &) {}
};

struct bool_type : type
{
};

struct integer_type : type
{
};

struct Context
{
    bool_type boolean;
    integer_type integer;
};

type *check(Context &, expr *);

#endif