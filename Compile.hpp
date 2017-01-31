//Nathan Stackpole
#include <algorithm>

//Base expression class
struct expr
{
    virtual ~expr() = default;
    virtual int weight() = 0; 
    virtual int eval() = 0; //Evaluates the expression and returns a bool
    virtual int height() = 0; 
    int height(expr*); //Finds the height of the tree of the expression
    int weight(expr*); //Finds the weight of the tree for the expression (basically counts the nodes in the tree)
};

//Base type class
struct type
{
    virtual ~type() = default;
};

struct bool_type : type
{};

struct integer_type : type
{};

//Boolean expression
class Bool_expr : public expr
{
    bool value;
    
    public:
    Bool_expr(bool);
    virtual int weight();
    virtual int height();
    int eval ();
};

//Not expression
class Not_expr : public expr
{
    expr* e;
    
    public:
    Not_expr(expr&);
    Not_expr() = default;
    int weight();
    int height();
    int eval();
};

//Or expression
class Or_expr : public expr
{
    expr* e1;
    expr* e2;

    public:
    Or_expr() = default;
    Or_expr(expr&, expr&);
    int weight();
    int height();
    int eval();
};

class Xor_expr : public expr
{
    expr* e1;
    expr* e2;

    public:
    Xor_expr() = default;
    Xor_expr(expr&, expr&);
    int weight();
    int height();
    int eval();
};

//And expression
class And_expr : public expr
{
    expr* e1;
    expr* e2;

    public:
    And_expr() = default;
    And_expr(expr&, expr&);
    int weight();
    int height();
    int eval();
};

//Conditional expression
class Conditional_expr : public expr
{
    expr* e1;
    expr* e2;
    expr* e3;

    public:
    Conditional_expr() = default;
    Conditional_expr(expr&, expr&, expr&);
    int weight();
    int height();
    int eval();

};

class Integer_expr : public expr
{
    int val;

    public:
    Integer_expr() = default;
    Integer_expr(int);
    int weight();
    int height();
    int eval();
};

class LessThan_expr : public expr
{
    expr* e1;
    expr* e2;

    public:
    LessThan_expr() = default;
    LessThan_expr(expr&, expr&);
    int weight();
    int height();
    int eval();
};

class MoreThan_expr : public expr
{
    expr* e1;
    expr* e2;

    public:
    MoreThan_expr() = default;
    MoreThan_expr(expr&, expr&);
    int weight();
    int height();
    int eval();
};

class EqualTo_expr : public expr
{
    expr* e1;
    expr* e2;

    public:
    EqualTo_expr() = default;
    EqualTo_expr(expr&, expr&);
    int weight();
    int height();
    int eval();
};
