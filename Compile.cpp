#include "Compile.hpp"

int expr::weight(expr *e)
{
    return e->weight();
}

int expr::height(expr *e)
{
    return e->height();
}

int Bool_expr::weight() { return 1; }
int Bool_expr::height() { return 0; }
bool Bool_expr::eval() { return value; }
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

And_expr::And_expr(expr& expression1, expr& expression2)
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

int Not_expr::weight() { return 1 + expr::weight(e); }
int Not_expr::height() { return 1 + expr::height(e); }
bool Not_expr::eval() { return !(e->eval()); }


int Or_expr::weight() { return 1 + expr::weight(e1) + expr::weight(e2); }
int Or_expr::height() { return 1 + std::max(expr::height(e1), expr::height(e2)); }
bool Or_expr::eval() { return (e1->eval() | e2->eval()); }

int And_expr::weight() { return 1 + expr::weight(e1) + expr::weight(e2); }
int And_expr::height() { return 1 + std::max(expr::height(e1), expr::height(e2)); }
bool And_expr::eval() { return (e1->eval() & e2->eval()); }

int Conditional_expr::weight() { return 1 + expr::weight(e1) + expr::weight(e2); }
int Conditional_expr::height() { return 1 + std::max(expr::height(e1), expr::height(e2)); }
bool Conditional_expr::eval() 
{ 
    if(e1->eval())
        return e2->eval();
    else
        return e3->eval();
}