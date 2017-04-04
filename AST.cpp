//Nathan Stackpole, 2017

#include "AST.hpp"
#include "type_check.hpp"

Context cxt;

//Constructors
Bool_expr::Bool_expr(bool v) : value(v), expr_type(&cxt.boolean) {}

Not_expr::Not_expr(expr *expression) : e(expression), expr_type(&cxt.boolean)
{
    assert(check(cxt, expression) == &cxt.boolean);
}

Or_expr::Or_expr(expr *expression1, expr *expression2) : e1(expression1), e2(expression2), expr_type(&cxt.boolean)
{
    assert(check(cxt, expression1) == &cxt.boolean && check(cxt, expression2) == &cxt.boolean);
}

OrElse_expr::OrElse_expr(expr *expression1, expr *expression2) : e1(expression1), e2(expression2), expr_type(&cxt.boolean)
{
    assert(check(cxt, expression1) == &cxt.boolean && check(cxt, expression2) == &cxt.boolean);
}

Xor_expr::Xor_expr(expr *expression1, expr *expression2) : e1(expression1), e2(expression2), expr_type(&cxt.boolean)
{
    assert(check(cxt, expression1) == &cxt.boolean && check(cxt, expression2) == &cxt.boolean);
}

And_expr::And_expr(expr *expression1, expr *expression2) : e1(expression1), e2(expression2), expr_type(&cxt.boolean)
{
    assert(check(cxt, expression1) == &cxt.boolean && check(cxt, expression2) == &cxt.boolean);
}

AndThen_expr::AndThen_expr(expr *expression1, expr *expression2) : e1(expression1), e2(expression2), expr_type(&cxt.boolean)
{
    assert(check(cxt, expression1) == &cxt.boolean && check(cxt, expression2) == &cxt.boolean);
}

EqualTo_expr::EqualTo_expr(expr *expression1, expr *expression2) : e1(expression1), e2(expression2), expr_type(&cxt.boolean)
{
    assert(check(cxt, expression1) == check(cxt, expression2));
}

NotEqualTo_expr::NotEqualTo_expr(expr *expression1, expr *expression2) : e1(expression1), e2(expression2), expr_type(&cxt.boolean)
{
    assert(check(cxt, expression1) == check(cxt, expression2));
}

LessThan_expr::LessThan_expr(expr *expression1, expr *expression2) : e1(expression1), e2(expression2), expr_type(&cxt.boolean)
{
    assert(check(cxt, expression1) == &cxt.integer && check(cxt, expression2) == &cxt.integer);
}

MoreThan_expr::MoreThan_expr(expr *expression1, expr *expression2) : e1(expression1), e2(expression2), expr_type(&cxt.boolean)
{
    assert(check(cxt, expression1) == &cxt.integer && check(cxt, expression2) == &cxt.integer);
}

LessThanOrEqualTo_expr::LessThanOrEqualTo_expr(expr *expression1, expr *expression2) : e1(expression1), e2(expression2), expr_type(&cxt.boolean)
{
    assert(check(cxt, expression1) == &cxt.integer && check(cxt, expression2) == &cxt.integer);
}

MoreThanOrEqualTo_expr::MoreThanOrEqualTo_expr(expr *expression1, expr *expression2) : e1(expression1), e2(expression2), expr_type(&cxt.boolean)
{
    assert(check(cxt, expression1) == &cxt.integer && check(cxt, expression2) == &cxt.integer);
}

Conditional_expr::Conditional_expr(expr *expression1, expr *expression2, expr *expression3) : e1(expression1), e2(expression2), e3(expression3), expr_type(&cxt.boolean)
{
    assert(check(cxt, expression1) == &cxt.boolean);
}

Integer_expr::Integer_expr(int integer) : val(integer), expr_type(&cxt.integer) {}

Addition_expr::Addition_expr(expr *expression1, expr *expression2) : e1(expression1), e2(expression2), expr_type(&cxt.integer)
{
    assert(check(cxt, expression1) == &cxt.integer && check(cxt, expression2) == &cxt.integer);
}

Subtraction_expr::Subtraction_expr(expr *expression1, expr *expression2) : e1(expression1), e2(expression2), expr_type(&cxt.integer)
{
    assert(check(cxt, expression1) == &cxt.integer && check(cxt, expression2) == &cxt.integer);
}

Division_expr::Division_expr(expr *expression1, expr *expression2) : e1(expression1), e2(expression2), expr_type(&cxt.integer)
{
    assert(check(cxt, expression1) == &cxt.integer && check(cxt, expression2) == &cxt.integer);
}

Modulus_expr::Modulus_expr(expr *expression1, expr *expression2) : e1(expression1), e2(expression2), expr_type(&cxt.integer)
{
    assert(check(cxt, expression1) == &cxt.integer && check(cxt, expression2) == &cxt.integer);
}

Negation_expr::Negation_expr(expr *expression) : e(expression), expr_type(&cxt.integer)
{
    assert(check(cxt, expression) == &cxt.integer);
}

Multiplication_expr::Multiplication_expr(expr *expression1, expr *expression2) : e1(expression1), e2(expression2), expr_type(&cxt.integer)
{
    assert(check(cxt, expression1) == &cxt.integer && check(cxt, expression2) == &cxt.integer);
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
bool Bool_expr::get_value() { return value; }
void Bool_expr::accept(Visitor &v) { return v.visit(this); }

//Not_expr function definitions
int Not_expr::weight() { return 1 + expr::weight(e); }
int Not_expr::height() { return 1 + expr::height(e); }
expr *Not_expr::get_e() const { return e; }
void Not_expr::accept(Visitor &v) { return v.visit(this); }

//Or_expr function definitions
int Or_expr::weight() { return 1 + expr::weight(e1) + expr::weight(e2); }
int Or_expr::height() { return 1 + std::max(expr::height(e1), expr::height(e2)); }
expr *Or_expr::get_e1() const { return e1; }
expr *Or_expr::get_e2() const { return e2; }
void Or_expr::accept(Visitor &v) { return v.visit(this); }

//OrElse_expr function definitions
int OrElse_expr::weight() { return 1 + expr::weight(e1) + expr::weight(e2); }
int OrElse_expr::height() { return 1 + std::max(expr::height(e1), expr::height(e2)); }
expr *OrElse_expr::get_e1() const { return e1; }
expr *OrElse_expr::get_e2() const { return e2; }
void OrElse_expr::accept(Visitor &v) { return v.visit(this); }

//Xor_expr function definitions
int Xor_expr::weight() { return 1 + expr::weight(e1) + expr::weight(e2); }
int Xor_expr::height() { return 1 + std::max(expr::height(e1), expr::height(e2)); }
expr *Xor_expr::get_e1() const { return e1; }
expr *Xor_expr::get_e2() const { return e2; }
void Xor_expr::accept(Visitor &v) { return v.visit(this); }

//And_expr function definitions
int And_expr::weight() { return 1 + expr::weight(e1) + expr::weight(e2); }
int And_expr::height() { return 1 + std::max(expr::height(e1), expr::height(e2)); }
expr *And_expr::get_e1() const { return e1; }
expr *And_expr::get_e2() const { return e2; }
void And_expr::accept(Visitor &v) { return v.visit(this); }

//AndThen_expr function definitions
int AndThen_expr::weight() { return 1 + expr::weight(e1) + expr::weight(e2); }
int AndThen_expr::height() { return 1 + std::max(expr::height(e1), expr::height(e2)); }
expr *AndThen_expr::get_e1() const { return e1; }
expr *AndThen_expr::get_e2() const { return e2; }
void AndThen_expr::accept(Visitor &v) { return v.visit(this); }

//Conditional_expr function definitions
int Conditional_expr::weight() { return 1 + expr::weight(e1) + expr::weight(e2); }
int Conditional_expr::height() { return 1 + std::max(expr::height(e1), expr::height(e2)); }
expr *Conditional_expr::get_e1() const { return e1; }
expr *Conditional_expr::get_e2() const { return e2; }
expr *Conditional_expr::get_e3() const { return e3; }
void Conditional_expr::accept(Visitor &v) { return v.visit(this); }

//Integer functions
int Integer_expr::weight() { return 1; }
int Integer_expr::height() { return 0; }
int Integer_expr::get_val() { return val; }
void Integer_expr::accept(Visitor &v) { return v.visit(this); }

//LessThan_expr function definitions
int LessThan_expr::weight() { return 1 + expr::weight(e1) + expr::weight(e2); }
int LessThan_expr::height() { return 1 + std::max(expr::height(e1), expr::height(e2)); }
expr *LessThan_expr::get_e1() const { return e1; }
expr *LessThan_expr::get_e2() const { return e2; }
void LessThan_expr::accept(Visitor &v) { return v.visit(this); }

//MoreThan_expr function definitions
int MoreThan_expr::weight() { return 1 + expr::weight(e1) + expr::weight(e2); }
int MoreThan_expr::height() { return 1 + std::max(expr::height(e1), expr::height(e2)); }
expr *MoreThan_expr::get_e1() const { return e1; }
expr *MoreThan_expr::get_e2() const { return e2; }
void MoreThan_expr::accept(Visitor &v) { return v.visit(this); }

//EqualTo_expr function definitions
int EqualTo_expr::weight() { return 1 + expr::weight(e1) + expr::weight(e2); }
int EqualTo_expr::height() { return 1 + std::max(expr::height(e1), expr::height(e2)); }
expr *EqualTo_expr::get_e1() const { return e1; }
expr *EqualTo_expr::get_e2() const { return e2; }
void EqualTo_expr::accept(Visitor &v) { return v.visit(this); }

//NotEqualTo_expr function definitions
int NotEqualTo_expr::weight() { return 1 + expr::weight(e1) + expr::weight(e2); }
int NotEqualTo_expr::height() { return 1 + std::max(expr::height(e1), expr::height(e2)); }
expr *NotEqualTo_expr::get_e1() const { return e1; }
expr *NotEqualTo_expr::get_e2() const { return e2; }
void NotEqualTo_expr::accept(Visitor &v) { return v.visit(this); }

//LessThanOrEqualTo_expr function definitions
int LessThanOrEqualTo_expr::weight() { return 1 + expr::weight(e1) + expr::weight(e2); }
int LessThanOrEqualTo_expr::height() { return 1 + std::max(expr::height(e1), expr::height(e2)); }
expr *LessThanOrEqualTo_expr::get_e1() const { return e1; }
expr *LessThanOrEqualTo_expr::get_e2() const { return e2; }
void LessThanOrEqualTo_expr::accept(Visitor &v) { return v.visit(this); }

//MoreThanOrEqualTo_expr function definitions
int MoreThanOrEqualTo_expr::weight() { return 1 + expr::weight(e1) + expr::weight(e2); }
int MoreThanOrEqualTo_expr::height() { return 1 + std::max(expr::height(e1), expr::height(e2)); }
expr *MoreThanOrEqualTo_expr::get_e1() const { return e1; }
expr *MoreThanOrEqualTo_expr::get_e2() const { return e2; }
void MoreThanOrEqualTo_expr::accept(Visitor &v) { return v.visit(this); }

//Addition_expr function definitios
int Addition_expr::weight() { return 1 + expr::weight(e1) + expr::weight(e2); }
int Addition_expr::height() { return 1 + std::max(expr::height(e1), expr::height(e2)); }
expr *Addition_expr::get_e1() const { return e1; }
expr *Addition_expr::get_e2() const { return e2; }
void Addition_expr::accept(Visitor &v) { return v.visit(this); }

//Subtraction_expr function definitios
int Subtraction_expr::weight() { return 1 + expr::weight(e1) + expr::weight(e2); }
int Subtraction_expr::height() { return 1 + std::max(expr::height(e1), expr::height(e2)); }
expr *Subtraction_expr::get_e1() const { return e1; }
expr *Subtraction_expr::get_e2() const { return e2; }
void Subtraction_expr::accept(Visitor &v) { return v.visit(this); }

//Division_expr function definitios
int Division_expr::weight() { return 1 + expr::weight(e1) + expr::weight(e2); }
int Division_expr::height() { return 1 + std::max(expr::height(e1), expr::height(e2)); }
expr *Division_expr::get_e1() const { return e1; }
expr *Division_expr::get_e2() const { return e2; }
void Division_expr::accept(Visitor &v) { return v.visit(this); }

//Modulus_expr function definitios
int Modulus_expr::weight() { return 1 + expr::weight(e1) + expr::weight(e2); }
int Modulus_expr::height() { return 1 + std::max(expr::height(e1), expr::height(e2)); }
expr *Modulus_expr::get_e1() const { return e1; }
expr *Modulus_expr::get_e2() const { return e2; }
void Modulus_expr::accept(Visitor &v) { return v.visit(this); }

//Negation_expr function definitios
int Negation_expr::weight() { return 1 + expr::weight(e); }
int Negation_expr::height() { return 1 + expr::height(e); }
expr *Negation_expr::get_e() const { return e; }
void Negation_expr::accept(Visitor &v) { return v.visit(this); }

//Multiplication_expr function definitios
int Multiplication_expr::weight() { return 1 + expr::weight(e1) + expr::weight(e2); }
int Multiplication_expr::height() { return 1 + std::max(expr::height(e1), expr::height(e2)); }
expr *Multiplication_expr::get_e1() const { return e1; }
expr *Multiplication_expr::get_e2() const { return e2; }
void Multiplication_expr::accept(Visitor &v) { return v.visit(this); }