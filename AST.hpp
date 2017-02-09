//Nathan Stackpole

#ifndef AST_HPP
#define AST_HPP

#include <algorithm>
#include <cassert>

struct bool_type;
struct integer_type;
struct type;

class Bool_expr;
class Not_expr;
class And_expr;
class Or_expr;
class AndThen_expr;
class OrElse_expr;
class Xor_expr;
class Conditional_expr;
class Integer_expr;
class LessThan_expr;
class MoreThan_expr;
class EqualTo_expr;
class NotEqualTo_expr;
class LessThanOrEqualTo_expr;
class MoreThanOrEqualTo_expr;
class Addition_expr;
class Subtraction_expr;
class Division_expr;
class Modulus_expr;
class Negation_expr;
class Multiplication_expr;

//Base expression class
struct expr
{
    struct Visitor;
    type *expr_type = nullptr;
    virtual ~expr() = default;
    virtual int height() = 0;
    virtual int weight() = 0;
    virtual void accept(Visitor &) = 0;
    int height(expr *);
    int weight(expr *);
};

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

//expr Visitor class
struct expr::Visitor
{
    virtual void visit(Bool_expr *) = 0;
    virtual void visit(And_expr *) = 0;
    virtual void visit(Or_expr *) = 0;
    virtual void visit(AndThen_expr *) = 0;
    virtual void visit(OrElse_expr *) = 0;
    virtual void visit(Not_expr *) = 0;
    virtual void visit(Xor_expr *) = 0;
    virtual void visit(Conditional_expr *) = 0;
    virtual void visit(Integer_expr *) = 0;
    virtual void visit(LessThan_expr *) = 0;
    virtual void visit(MoreThan_expr *) = 0;
    virtual void visit(EqualTo_expr *) = 0;
    virtual void visit(NotEqualTo_expr *) = 0;
    virtual void visit(LessThanOrEqualTo_expr *) = 0;
    virtual void visit(MoreThanOrEqualTo_expr *) = 0;
    virtual void visit(Addition_expr *) = 0;
    virtual void visit(Subtraction_expr *) = 0;
    virtual void visit(Multiplication_expr *) = 0;
    virtual void visit(Division_expr *) = 0;
    virtual void visit(Modulus_expr *) = 0;
    virtual void visit(Negation_expr *) = 0;
};

//Boolean expression
class Bool_expr : public expr
{

    bool value;

  public:
    type *expr_type;
    Bool_expr(bool);
    virtual int weight();
    virtual int height();
    void accept(Visitor &);
    bool get_value();
};

//Not (!e) expression
class Not_expr : public expr
{
    expr *e;

  public:
    type *expr_type;
    Not_expr(expr *);
    Not_expr() = default;
    int weight();
    int height();
    void accept(Visitor &);
    expr *get_e() const;
};

//Or (|) expression
class Or_expr : public expr
{

    expr *e1;
    expr *e2;

  public:
    type *expr_type;
    Or_expr() = default;
    Or_expr(expr *, expr *);
    int weight();
    int height();
    void accept(Visitor &);
    expr *get_e1() const;
    expr *get_e2() const;
};

//OrElse (||) expression
class OrElse_expr : public expr
{

    expr *e1;
    expr *e2;

  public:
    type *expr_type;
    OrElse_expr() = default;
    OrElse_expr(expr *, expr *);
    int weight();
    int height();
    void accept(Visitor &);
    expr *get_e1() const;
    expr *get_e2() const;
};

//Xor expression
class Xor_expr : public expr
{

    expr *e1;
    expr *e2;

  public:
    type *expr_type;
    Xor_expr() = default;
    Xor_expr(expr *, expr *);
    int weight();
    int height();
    void accept(Visitor &);
    expr *get_e1() const;
    expr *get_e2() const;
};

//And expression
class And_expr : public expr
{

    expr *e1;
    expr *e2;

  public:
    type *expr_type;
    And_expr() = default;
    And_expr(expr *, expr *);
    int weight();
    int height();
    void accept(Visitor &);
    expr *get_e1() const;
    expr *get_e2() const;
};

//AndThen expression
class AndThen_expr : public expr
{

    expr *e1;
    expr *e2;

  public:
    type *expr_type;
    AndThen_expr() = default;
    AndThen_expr(expr *, expr *);
    int weight();
    int height();
    void accept(Visitor &);
    expr *get_e1() const;
    expr *get_e2() const;
};

//Conditional expression
class Conditional_expr : public expr
{

    expr *e1;
    expr *e2;
    expr *e3;

  public:
    type *expr_type;
    Conditional_expr() = default;
    Conditional_expr(expr *, expr *, expr *);
    int weight();
    int height();
    void accept(Visitor &);
    expr *get_e1() const;
    expr *get_e2() const;
    expr *get_e3() const;
};

//Integer value
class Integer_expr : public expr
{

    int val;

  public:
    type *expr_type;
    Integer_expr() = default;
    Integer_expr(int);
    int weight();
    int height();
    void accept(Visitor &);
    int get_val();
};

//Less Than (<) expression
class LessThan_expr : public expr
{

    expr *e1;
    expr *e2;

  public:
    type *expr_type;
    LessThan_expr() = default;
    LessThan_expr(expr *, expr *);
    int weight();
    int height();
    void accept(Visitor &);
    expr *get_e1() const;
    expr *get_e2() const;
};

//More Than (>) expression
class MoreThan_expr : public expr
{

    expr *e1;
    expr *e2;

  public:
    type *expr_type;
    MoreThan_expr() = default;
    MoreThan_expr(expr *, expr *);
    int weight();
    int height();
    void accept(Visitor &);
    expr *get_e1() const;
    expr *get_e2() const;
};

//Equality (==) expression
class EqualTo_expr : public expr
{

    expr *e1;
    expr *e2;

  public:
    type *expr_type;
    EqualTo_expr() = default;
    EqualTo_expr(expr *, expr *);
    int weight();
    int height();
    void accept(Visitor &);
    expr *get_e1() const;
    expr *get_e2() const;
};

//Not equal to (!=) expression
class NotEqualTo_expr : public expr
{
    expr *e1;
    expr *e2;

  public:
    type *expr_type;
    NotEqualTo_expr() = default;
    NotEqualTo_expr(expr *, expr *);
    int weight();
    int height();
    void accept(Visitor &);
    expr *get_e1() const;
    expr *get_e2() const;
};

//Less Than or equal to (<=) expression
class LessThanOrEqualTo_expr : public expr
{

    expr *e1;
    expr *e2;

  public:
    type *expr_type;
    LessThanOrEqualTo_expr() = default;
    LessThanOrEqualTo_expr(expr *, expr *);
    int weight();
    int height();
    void accept(Visitor &);
    expr *get_e1() const;
    expr *get_e2() const;
};

//More Than or equal to (>=) expression
class MoreThanOrEqualTo_expr : public expr
{

    expr *e1;
    expr *e2;

  public:
    type *expr_type;
    MoreThanOrEqualTo_expr() = default;
    MoreThanOrEqualTo_expr(expr *, expr *);
    int weight();
    int height();
    void accept(Visitor &);
    expr *get_e1() const;
    expr *get_e2() const;
};

class Addition_expr : public expr
{
    expr *e1;
    expr *e2;

  public:
    type *expr_type;
    Addition_expr() = default;
    Addition_expr(expr *, expr *);
    int weight();
    int height();
    void accept(Visitor &);
    expr *get_e1() const;
    expr *get_e2() const;
};

class Subtraction_expr : public expr
{
    expr *e1;
    expr *e2;

  public:
    type *expr_type;
    Subtraction_expr() = default;
    Subtraction_expr(expr *, expr *);
    int weight();
    int height();
    void accept(Visitor &);
    expr *get_e1() const;
    expr *get_e2() const;
};

class Division_expr : public expr
{
    expr *e1;
    expr *e2;

  public:
    type *expr_type;
    Division_expr() = default;
    Division_expr(expr *, expr *);
    int weight();
    int height();
    void accept(Visitor &);
    expr *get_e1() const;
    expr *get_e2() const;
};

class Modulus_expr : public expr
{
    expr *e1;
    expr *e2;

  public:
    type *expr_type;
    Modulus_expr() = default;
    Modulus_expr(expr *, expr *);
    int weight();
    int height();
    void accept(Visitor &);
    expr *get_e1() const;
    expr *get_e2() const;
};

class Negation_expr : public expr
{
    expr *e;

  public:
    type *expr_type;
    Negation_expr() = default;
    Negation_expr(expr *);
    int weight();
    int height();
    void accept(Visitor &);
    expr *get_e() const;
};

class Multiplication_expr : public expr
{
    expr *e1;
    expr *e2;

  public:
    type *expr_type;
    Multiplication_expr() = default;
    Multiplication_expr(expr *, expr *);
    int weight();
    int height();
    void accept(Visitor &);
    expr *get_e1() const;
    expr *get_e2() const;
};

#endif