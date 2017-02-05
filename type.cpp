//Nathan Stackpole

#include "type.hpp"

type *check(Context &cxt, expr *e)
{
    struct V : expr::Visitor
    {
        Context &cxt;
        type *r;
        V(Context &c) : cxt(c) {}
        void visit(expr *e) { visit(e); }
        void visit(Bool_expr *e) { r = &cxt.boolean; }
        void visit(Integer_expr *e) { r = &cxt.integer; }
        void visit(And_expr *e)
        {
            r = &cxt.boolean;
        }
        void visit(Or_expr *e) { r = &cxt.boolean; }
        void visit(Not_expr *e) { r = &cxt.boolean; }
        void visit(Xor_expr *e) { r = &cxt.boolean; }
        void visit(Conditional_expr *e) { r = &cxt.boolean; }
        void visit(LessThan_expr *e) { r = &cxt.boolean; }
        void visit(MoreThan_expr *e) { r = &cxt.boolean; }
        void visit(EqualTo_expr *e) { r = &cxt.boolean; }
    };
    V vis(cxt);
    e->accept(vis);
    return vis.r;
}