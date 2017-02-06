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
            assert(check(cxt, e->get_e1()) == &cxt.boolean);
            assert(check(cxt, e->get_e2()) == &cxt.boolean);

            r = &cxt.boolean;
        }
        void visit(Or_expr *e)
        {
            assert(check(cxt, e->get_e1()) == &cxt.boolean);
            assert(check(cxt, e->get_e2()) == &cxt.boolean);
            r = &cxt.boolean;
        }
        void visit(Not_expr *e)
        {
            assert(check(cxt, e->get_e()) == &cxt.boolean);
            r = &cxt.boolean;
        }
        void visit(Xor_expr *e)
        {
            assert(check(cxt, e->get_e1()) == &cxt.boolean);
            assert(check(cxt, e->get_e2()) == &cxt.boolean);
            r = &cxt.boolean;
        }
        void visit(Conditional_expr *e)
        {
            assert(check(cxt, e->get_e1()) == &cxt.boolean);
            assert(check(cxt, e->get_e2()) == &cxt.boolean);
            r = &cxt.boolean;
        }
        void visit(LessThan_expr *e)
        {
            assert(check(cxt, e->get_e1()) == &cxt.integer);
            assert(check(cxt, e->get_e2()) == &cxt.integer);
            r = &cxt.boolean;
        }
        void visit(MoreThan_expr *e)
        {
            assert(check(cxt, e->get_e1()) == &cxt.integer);
            assert(check(cxt, e->get_e2()) == &cxt.integer);
            r = &cxt.boolean;
        }
        void visit(EqualTo_expr *e)
        {
            assert(check(cxt, e->get_e1()) == check(cxt, e->get_e2()));
            r = &cxt.boolean;
        }
        void visit(NotEqualTo_expr *e)
        {
            assert(check(cxt, e->get_e1()) == check(cxt, e->get_e2()));
            r = &cxt.boolean;
        }
        void visit(LessThanOrEqualTo_expr *e)
        {
            assert(check(cxt, e->get_e1()) == &cxt.integer);
            assert(check(cxt, e->get_e2()) == &cxt.integer);
            r = &cxt.boolean;
        }
        void visit(MoreThanOrEqualTo_expr *e)
        {
            assert(check(cxt, e->get_e1()) == &cxt.integer);
            assert(check(cxt, e->get_e2()) == &cxt.integer);
            r = &cxt.boolean;
        }
    };
    V vis(cxt);
    e->accept(vis);
    return vis.r;
}