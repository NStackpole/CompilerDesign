//Nathan Stackpole

#include "eval.hpp"

//Evaluation function: one function that contains a Visitor class that has a visit function that is overriden to evaluate any defined expression
int eval(expr *e)
{
    struct V : expr::Visitor
    {
        //r is the integer value that will hold the value of the expr evaluation, gets returned
        int r;

        //Evaluation functions for all the different types of expr
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
            //Checking for integer overflow
            if (std::numeric_limits<int>::max() - eval(e->get_e1()) < eval(e->get_e2()))
                throw "Integer Overflow Detected in addition. Exiting program.\n";

            r = eval(e->get_e1()) + eval(e->get_e2());
        }
        void visit(Subtraction_expr *e)
        {
            //checking for integer overflow
            if (std::numeric_limits<int>::max() - eval(e->get_e1()) < eval(e->get_e2()))
                throw "Integer Overflow Detected in subtraction. Exiting Program.\n";

            r = eval(e->get_e1()) - eval(e->get_e2());
        }
        void visit(Multiplication_expr *e)
        {
            //Checking for integer overflow
            if (std::numeric_limits<int>::max() - eval(e->get_e1()) < eval(e->get_e2()))
                throw "Integer Overflow Detected in multiplication. Exiting Program.\n";

            r = eval(e->get_e1()) * eval(e->get_e2());
        }
        void visit(Division_expr *e)
        {
            //Check for division by zero or by the minimum integer value.
            if (eval(e->get_e2()) == 0)
                throw "Division by zero detected. Exiting Program.\n";
            if (eval(e->get_e2()) == std::numeric_limits<int>::min())
                throw "Division by minimum integer value detected. Exiting Program.\n";

            r = eval(e->get_e1()) / eval(e->get_e2());
        }
        void visit(Modulus_expr *e)
        {
            //Checking for modular division by zero or by the minimum integer value.
            if (eval(e->get_e2()) == 0)
                throw "Modular division by zero detected. Exiting Program.\n";
            if (eval(e->get_e2()) == std::numeric_limits<int>::min())
                throw "Modular division by minimum integer value detected. Exiting Program.\n";

            r = eval(e->get_e1()) % eval(e->get_e2());
        }
        void visit(Negation_expr *e) { r = 0 - eval(e->get_e()); }
    };

    //Create a visitor.
    V vis;

    try
    {
        //try to use the accept function for the expr which will call the visit function for the expr.
        e->accept(vis);
    }
    catch (const char *message)
    {
        //If an exception is caught from a visit function, the error message is printed and the program is aborted.
        std::cerr << "Exception Caught: \n";
        std::cerr << message << "\n";
        abort();
    }

    return vis.r;
}