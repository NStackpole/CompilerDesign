//Nathan Stackpole, 2017

#include "llvm_gen.hpp"

std::string generate(expr *e)
{
    struct V : expr::Visitor
    {
        //r is the string value that will hold the value of the expr llvm code, gets returned
        std::string r;

        //Generate llvm based on the expr given
        void visit(Bool_expr *e) { }
        void visit(And_expr *e) {  }
        void visit(Or_expr *e) {  }
        void visit(AndThen_expr *e) {  }
        void visit(OrElse_expr *e) { }
        void visit(Not_expr *e) {  }
        void visit(Xor_expr *e) {  }
        void visit(Conditional_expr *e){  }
        void visit(Integer_expr *e) {  }
        void visit(LessThan_expr *e) {  }
        void visit(MoreThan_expr *e) { }
        void visit(EqualTo_expr *e) { }
        void visit(NotEqualTo_expr *e) {  }
        void visit(LessThanOrEqualTo_expr *e) {  }
        void visit(MoreThanOrEqualTo_expr *e) {  }
        void visit(Addition_expr *e){  }
        void visit(Subtraction_expr *e){}
        void visit(Multiplication_expr *e){ }
        void visit(Division_expr *e){ }
        void visit(Modulus_expr *e){ }
        void visit(Negation_expr *e) {  }
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