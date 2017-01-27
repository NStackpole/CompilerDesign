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
    Not_expr(expr*);
    int weight();
    int height();
    bool eval();
};

struct Or_expr : expr
{
    expr* e1;
    expr* e2;
    int weight();
    int height();
    bool eval();
};

struct And_expr : expr
{
    expr* e1;
    expr* e2;
    int weight();
    int height();
    bool eval();
};

struct Conditional_expr : expr
{
    expr* e1;
    expr* e2;
    expr* e3;

};

