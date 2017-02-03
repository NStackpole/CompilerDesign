//Nathan Stackpole

#include "eval.hpp"

int eval(expr* e)
{
    struct V : expr::Visitor
    {
        int r;
        void visit(Bool_expr* e) { r = e->get_value(); }
        void visit(And_expr* e) { r = eval(e->get_e1()) & eval(e->get_e2()); }
        void visit(Or_expr* e) { r = eval(e->get_e1()) | eval(e->get_e2()); }
        void visit(Not_expr* e) { r = !eval(e->get_e()); }
        void visit(Xor_expr* e) { r = (eval(e->get_e1()) != eval(e->get_e2())); }
        void visit(Conditional_expr* e) 
        {
            if(eval(e->get_e1()))
                r = eval(e->get_e2());
            else
                r = eval(e->get_e3()); 
        }
        void visit(Integer_expr* e) { r = e->get_val(); }
        void visit(LessThan_expr* e) { r = eval(e->get_e1()) < eval(e->get_e2());} 
        void visit(MoreThan_expr* e) {r = eval(e->get_e1()) > eval(e->get_e2());}
        void visit(EqualTo_expr* e) {r = eval(e->get_e1()) == eval(e->get_e2());}
    };
    V vis;
    e->accept(vis);
    return vis.r;
}