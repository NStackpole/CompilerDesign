//Nathan Stackpole

#ifndef AST_HPP
#define AST_HPP

#include <algorithm>
#include <cassert>

struct bool_type;
struct integer_type;

class Bool_expr;
class Not_expr;
class And_expr;
class Or_expr;
class Xor_expr;
class Conditional_expr;
class Integer_expr;
class LessThan_expr;
class MoreThan_expr;
class EqualTo_expr;

//Base expression class
struct expr
{
    struct Visitor;
    virtual ~expr() = default;
    virtual int height() = 0;
    virtual int weight() = 0;
    virtual void accept(Visitor&) = 0;
    int height(expr*);
    int weight(expr*);
};

//Base type class
struct type
{
    struct Visitor;
    virtual ~type() = default;
    virtual void accept(Visitor&) { }
};


struct expr::Visitor
{
    virtual void visit(Bool_expr*) = 0;
    virtual void visit(And_expr*) = 0;
    virtual void visit(Or_expr*) = 0;
    virtual void visit(Not_expr*) = 0;
    virtual void visit(Xor_expr*) = 0;
    virtual void visit(Conditional_expr*) = 0;
    virtual void visit(Integer_expr*) = 0;
    virtual void visit(LessThan_expr*) = 0;
    virtual void visit(MoreThan_expr*) = 0;
    virtual void visit(EqualTo_expr*) = 0;
};

struct type::Visitor
{
    
};

struct bool_type : type
{};

struct integer_type : type
{};

struct Context
{
    bool_type boolean;
    integer_type integer;
};

//Boolean expression
class Bool_expr : public expr
{
    
    bool value;
    
    public:

    Bool_expr(bool);
    virtual int weight();
    virtual int height();
    void accept(Visitor&);
    bool get_value();
};

//Not expression
class Not_expr : public expr
{
    expr* e;

    public:   
   
    Not_expr(expr*);
    Not_expr() = default;
    int weight();
    int height();
    int eval();
    void accept(Visitor&);
    expr* get_e();
};

//Or expression
class Or_expr : public expr
{
    
    expr* e1;
    expr* e2;

    public:
    
    Or_expr() = default;
    Or_expr(expr*, expr*);
    int weight();
    int height();
    int eval();
    void accept(Visitor&);
    expr* get_e1();
    expr* get_e2();
};

//Xor expression
class Xor_expr : public expr
{

    expr* e1;
    expr* e2;

    public:
    
    Xor_expr() = default;
    Xor_expr(expr*, expr*);
    int weight();
    int height();
    int eval();
    void accept(Visitor&);
    expr* get_e1();
    expr* get_e2();
};

//And expression
class And_expr : public expr
{
    
    expr* e1;
    expr* e2;

    public:
    
    And_expr() = default;
    And_expr(expr*, expr*);
    int weight();
    int height();
    int eval();
    void accept(Visitor&);
    expr* get_e1();
    expr* get_e2();
};

//Conditional expression
class Conditional_expr : public expr
{
    
    expr* e1;
    expr* e2;
    expr* e3;

    public:

    Conditional_expr() = default;
    Conditional_expr(expr*, expr*, expr*);
    int weight();
    int height();
    int eval();
    void accept(Visitor&);
    expr* get_e1();
    expr* get_e2();
    expr* get_e3();

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
    void accept(Visitor&);
    int get_val();
};

class LessThan_expr : public expr
{
    
    expr* e1;
    expr* e2;

    public:
    
    LessThan_expr() = default;
    LessThan_expr(expr*, expr*);
    int weight();
    int height();
    int eval();
    void accept(Visitor&);
    expr* get_e1();
    expr* get_e2();
};

class MoreThan_expr : public expr
{
    
    expr* e1;
    expr* e2;

    public:

    MoreThan_expr() = default;
    MoreThan_expr(expr*, expr*);
    int weight();
    int height();
    int eval();
    void accept(Visitor&);
    expr* get_e1();
    expr* get_e2();
};

class EqualTo_expr : public expr
{
    
    expr* e1;
    expr* e2;

    public:

    EqualTo_expr() = default;
    EqualTo_expr(expr*, expr*);
    int weight();
    int height();
    int eval();
    void accept(Visitor&);
    expr* get_e1();
    expr* get_e2();
};

#endif