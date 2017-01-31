//Nathan Stackpole

#include "Compile.hpp"


//Constructors
Bool_expr::Bool_expr(bool v)
{
    value = v;
}

Not_expr::Not_expr(expr& expression)
{
    e = &expression;
}

Or_expr::Or_expr(expr& expression1, expr& expression2)
{
    e1 = &expression1;
    e2 = &expression2;
}

Xor_expr::Xor_expr(expr& expression1, expr& expression2)
{
    e1 = &expression1;
    e2 = &expression2;
}

And_expr::And_expr(expr& expression1, expr& expression2)
{
    e1 = &expression1;
    e2 = &expression2;
}

EqualTo_expr::EqualTo_expr(expr& expression1, expr& expression2)
{
    e1 = &expression1;
    e2 = &expression2;
}

LessThan_expr::LessThan_expr(expr& expression1, expr& expression2)
{
    e1 = &expression1;
    e2 = &expression2;
}

MoreThan_expr::MoreThan_expr(expr& expression1, expr& expression2)
{
    e1 = &expression1;
    e2 = &expression2;
}

Conditional_expr::Conditional_expr(expr& expression1, expr& expression2, expr& expression3)
{
    e1 = &expression1;
    e2 = &expression2;
    e3 = &expression3;
}

Integer_expr::Integer_expr(int integer)
{
    val = integer;
}

//Base expression functions
int expr::weight(expr *e)
{
    return e->weight();
}

int expr::height(expr *e)
{
    return e->height();
}

//Bool_expr function definitions
int Bool_expr::weight() { return 1; }
int Bool_expr::height() { return 0; }
int Bool_expr::eval() { return value; }

//Not_expr function definitions
int Not_expr::weight() { return 1 + expr::weight(e); }
int Not_expr::height() { return 1 + expr::height(e); }
int Not_expr::eval() { return !(e->eval()); }

//Or_expr function definitions
int Or_expr::weight() { return 1 + expr::weight(e1) + expr::weight(e2); }
int Or_expr::height() { return 1 + std::max(expr::height(e1), expr::height(e2)); }
int Or_expr::eval() { return (e1->eval() | e2->eval()); }

//Xor_expr function definitions
int Xor_expr::weight() { return 1 + expr::weight(e1) + expr::weight(e2); }
int Xor_expr::height() { return 1 + std::max(expr::height(e1), expr::height(e2)); }
int Xor_expr::eval() { return (e1->eval() != e2->eval()); }

//And_expr function definitions
int And_expr::weight() { return 1 + expr::weight(e1) + expr::weight(e2); }
int And_expr::height() { return 1 + std::max(expr::height(e1), expr::height(e2)); }
int And_expr::eval() { return (e1->eval() & e2->eval()); }

//Conditional_expr function definitions
int Conditional_expr::weight() { return 1 + expr::weight(e1) + expr::weight(e2); }
int Conditional_expr::height() { return 1 + std::max(expr::height(e1), expr::height(e2)); }
int Conditional_expr::eval() 
{ 
    if(e1->eval())
        return e2->eval();
    else
        return e3->eval();
}

//Integer functions
int Integer_expr::eval() {return val;}
int Integer_expr::weight() {return 1;}
int Integer_expr::height() {return 0;}

//LessThan_expr function definitions
int LessThan_expr::weight() { return 1 + expr::weight(e1) + expr::weight(e2); }
int LessThan_expr::height() { return 1 + std::max(expr::height(e1), expr::height(e2)); }
int LessThan_expr::eval() { return (e1->eval() < e2->eval()); }

//MoreThan_expr function definitions
int MoreThan_expr::weight() { return 1 + expr::weight(e1) + expr::weight(e2); }
int MoreThan_expr::height() { return 1 + std::max(expr::height(e1), expr::height(e2)); }
int MoreThan_expr::eval() { return (e1->eval() > e2->eval()); }

//EqualTo_expr function definitions
int EqualTo_expr::weight() { return 1 + expr::weight(e1) + expr::weight(e2); }
int EqualTo_expr::height() { return 1 + std::max(expr::height(e1), expr::height(e2)); }
int EqualTo_expr::eval() { return (e1->eval() == e2->eval()); }