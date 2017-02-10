//Nathan Stackpole

#include "eval.hpp"

//Evaluation function: one function that contains a Visitor class that has a visit function that is overriden to evaluate any defined expression
int eval(expr *e)
{
    struct V : expr::Visitor
    {
        int r;
        void visit(Bool_expr *e) { r = e->get_value(); }
        void visit(And_expr *e) { r = eval(e->get_e1()) & eval(e->get_e2()); }
        void visit(Or_expr *e) { r = eval(e->get_e1()) | eval(e->get_e2()); }
        void visit(AndThen_expr *e) { r = eval(e->get_e1()) && eval(e->get_e2()); }
        void visit(OrElse_expr *e) { r = eval(e->get_e1()) || eval(e->get_e2()); }
        void visit(Not_expr *e) { r = !eval(e->get_e()); }
        void visit(Xor_expr *e) { r = (eval(e->get_e1()) != eval(e->get_e2())); }
        void visit(Conditional_expr *e)
        {
            if (eval(e->get_e1()))
                r = eval(e->get_e2());
            else
                r = eval(e->get_e3());
        }
        void visit(Integer_expr *e) { r = e->get_val(); }
        void visit(LessThan_expr *e) { r = eval(e->get_e1()) < eval(e->get_e2()); }
        void visit(MoreThan_expr *e) { r = eval(e->get_e1()) > eval(e->get_e2()); }
        void visit(EqualTo_expr *e) { r = eval(e->get_e1()) == eval(e->get_e2()); }
        void visit(NotEqualTo_expr *e) { r = eval(e->get_e1()) != eval(e->get_e2()); }
        void visit(LessThanOrEqualTo_expr *e) { r = eval(e->get_e1()) <= eval(e->get_e2()); }
        void visit(MoreThanOrEqualTo_expr *e) { r = eval(e->get_e1()) >= eval(e->get_e2()); }
        void visit(Addition_expr *e)
        {
            if (std::numeric_limits<int>::max() - eval(e->get_e1()) < eval(e->get_e2()))
                throw "Integer Overflow Detected in addition. Exiting program.\n";
            r = eval(e->get_e1()) + eval(e->get_e2());
        }
        void visit(Subtraction_expr *e)
        {
            if (std::numeric_limits<int>::max() - eval(e->get_e1()) < eval(e->get_e2()))
                throw "Integer Overflow Detected in subtraction. Exiting Program.\n";
            r = eval(e->get_e1()) - eval(e->get_e2());
        }
        void visit(Multiplication_expr *e)
        {
            if (std::numeric_limits<int>::max() - eval(e->get_e1()) < eval(e->get_e2()))
                throw "Integer Overflow Detected in multiplication. Exiting Program.\n";
            r = eval(e->get_e1()) * eval(e->get_e2());
        }
        void visit(Division_expr *e)
        {
            if (eval(e->get_e2()) == 0)
                throw "Division by zero detected. Exiting Program.\n";
            if (eval(e->get_e2()) == std::numeric_limits<int>::min())
                throw "Division by minimum integer value detected. Exiting Program.\n";
            r = eval(e->get_e1()) / eval(e->get_e2());
        }
        void visit(Modulus_expr *e)
        {
            if (eval(e->get_e2()) == 0)
                throw "Modular divison by zero detected. Exiting Program.\n";
            if (eval(e->get_e2()) == std::numeric_limits<int>::min())
                throw "Modular divison by minimum integer value detected. Exiting Program.\n";
            r = eval(e->get_e1()) % eval(e->get_e2());
        }
        void visit(Negation_expr *e) { r = 0 - eval(e->get_e()); }
    };
    V vis;
    try
    {
        e->accept(vis);
    }
    catch (const char *message)
    {
        std::cerr << "Exception Caught: \n";
        std::cerr << message << "\n";
        abort();
    }

    return vis.r;
}