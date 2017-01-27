//Nathan Stackpole
#include <algorithm>

struct expr
{
    virtual ~expr() = default;
    virtual int weight() = 0;
    virtual bool eval() = 0;
    virtual int height() = 0;
    int height(expr*);
    int weight(expr*);
};

struct type
{
    virtual ~type() = default;
};

struct bool_type : type
{};

struct integer_type : type
{};

struct Bool_expr : expr
{
    Bool_expr(bool);
    bool value;
    virtual int weight();
    virtual int height();
    bool eval ();
};

struct Not_expr : expr
{
    expr* e;
    Not_expr(expr&);
    Not_expr() = default;
    int weight();
    int height();
    bool eval();
};

struct Or_expr : expr
{
    expr* e1;
    expr* e2;
    Or_expr() = default;
    Or_expr(expr&, expr&);
    int weight();
    int height();
    bool eval();
};

struct And_expr : expr
{
    expr* e1;
    expr* e2;
    And_expr() = default;
    And_expr(expr&, expr&);
    int weight();
    int height();
    bool eval();
};

struct Conditional_expr : expr
{
    Conditional_expr() = default;
    Conditional_expr(expr&, expr&, expr&);
    expr* e1;
    expr* e2;
    expr* e3;
    int weight();
    int height();
    bool eval();

};

struct Integer_expr : expr
{
    int val;
    Integer_expr() = default;
    Integer_expr(int);
};
