//Nathan Stackpole

#include "type_check.hpp"

type *check(Context &cxt, expr *e)
{
    struct V : expr::Visitor
    {
        Context &cxt;
        type *r;
        V(Context &c) : cxt(c) {}
        void visit(expr *e) { visit(e); }
        void visit(Bool_expr *e)
        {
            //Not happy with having to do this and. Going to try and fix it before next commit.
            if (e->expr_type && e->expr_type == &cxt.boolean)
                r = e->expr_type;

            else
            {
                r = &cxt.boolean;
                e->expr_type = r;
            }
        }
        void visit(Integer_expr *e)
        {
            if (e->expr_type && e->expr_type == &cxt.integer)
                r = e->expr_type;

            else
            {
                r = &cxt.integer;
                e->expr_type = r;
            }
        }
        void visit(And_expr *e)
        {
            assert(check(cxt, e->get_e1()) == &cxt.boolean);
            assert(check(cxt, e->get_e2()) == &cxt.boolean);

            if (e->expr_type && e->expr_type == &cxt.boolean)
                r = e->expr_type;

            else
            {
                r = &cxt.boolean;
                e->expr_type = r;
            }
        }
        void visit(AndThen_expr *e)
        {
            assert(check(cxt, e->get_e1()) == &cxt.boolean);
            assert(check(cxt, e->get_e2()) == &cxt.boolean);

            if (e->expr_type && e->expr_type == &cxt.boolean)
                r = e->expr_type;

            else
            {
                r = &cxt.boolean;
                e->expr_type = r;
            }
        }
        void visit(Or_expr *e)
        {
            assert(check(cxt, e->get_e1()) == &cxt.boolean);
            assert(check(cxt, e->get_e2()) == &cxt.boolean);

            if (e->expr_type && e->expr_type == &cxt.boolean)
                r = e->expr_type;

            else
            {
                r = &cxt.boolean;
                e->expr_type = r;
            }
        }
        void visit(OrElse_expr *e)
        {
            assert(check(cxt, e->get_e1()) == &cxt.boolean);
            assert(check(cxt, e->get_e2()) == &cxt.boolean);

            if (e->expr_type && e->expr_type == &cxt.boolean)
                r = e->expr_type;

            else
            {
                r = &cxt.boolean;
                e->expr_type = r;
            }
        }
        void visit(Not_expr *e)
        {
            assert(check(cxt, e->get_e()) == &cxt.boolean);

            if (e->expr_type && e->expr_type == &cxt.boolean)
                r = e->expr_type;

            else
            {
                r = &cxt.boolean;
                e->expr_type = r;
            }
        }
        void visit(Xor_expr *e)
        {
            assert(check(cxt, e->get_e1()) == &cxt.boolean);
            assert(check(cxt, e->get_e2()) == &cxt.boolean);

            if (e->expr_type && e->expr_type == &cxt.boolean)
                r = e->expr_type;

            r = &cxt.boolean;
            e->expr_type = r;
        }
        void visit(Conditional_expr *e)
        {
            assert(check(cxt, e->get_e1()) == &cxt.boolean);
            assert(check(cxt, e->get_e2()) == &cxt.boolean);
            assert(check(cxt, e->get_e3()) == &cxt.boolean);

            if (e->expr_type && e->expr_type == &cxt.boolean)
                r = e->expr_type;

            else
            {
                r = &cxt.boolean;
                e->expr_type = r;
            }
        }
        void visit(LessThan_expr *e)
        {
            assert(check(cxt, e->get_e1()) == &cxt.integer);
            assert(check(cxt, e->get_e2()) == &cxt.integer);

            if (e->expr_type && e->expr_type == &cxt.boolean)
                r = e->expr_type;

            else
            {
                r = &cxt.boolean;
                e->expr_type = r;
            }
        }
        void visit(MoreThan_expr *e)
        {
            assert(check(cxt, e->get_e1()) == &cxt.integer);
            assert(check(cxt, e->get_e2()) == &cxt.integer);

            if (e->expr_type && e->expr_type == &cxt.boolean)
                r = e->expr_type;

            else
            {
                r = &cxt.boolean;
                e->expr_type = r;
            }
        }
        void visit(EqualTo_expr *e)
        {
            assert(check(cxt, e->get_e1()) == check(cxt, e->get_e2()));
            if (e->expr_type && e->expr_type == &cxt.boolean)
                r = e->expr_type;

            else
            {
                r = &cxt.boolean;
                e->expr_type = r;
            }
        }
        void visit(NotEqualTo_expr *e)
        {
            assert(check(cxt, e->get_e1()) == check(cxt, e->get_e2()));

            if (e->expr_type && e->expr_type == &cxt.boolean)
                r = e->expr_type;

            else
            {
                r = &cxt.boolean;
                e->expr_type = r;
            }
        }
        void visit(LessThanOrEqualTo_expr *e)
        {
            assert(check(cxt, e->get_e1()) == &cxt.integer);
            assert(check(cxt, e->get_e2()) == &cxt.integer);

            if (e->expr_type && e->expr_type == &cxt.boolean)
                r = e->expr_type;

            else
            {
                r = &cxt.boolean;
                e->expr_type = r;
            }
        }
        void visit(MoreThanOrEqualTo_expr *e)
        {
            assert(check(cxt, e->get_e1()) == &cxt.integer);
            assert(check(cxt, e->get_e2()) == &cxt.integer);

            if (e->expr_type && e->expr_type == &cxt.boolean)
                r = e->expr_type;

            else
            {
                r = &cxt.boolean;
                e->expr_type = r;
            }
        }
        void visit(Addition_expr *e)
        {
            assert(check(cxt, e->get_e1()) == &cxt.integer);
            assert(check(cxt, e->get_e2()) == &cxt.integer);

            if (e->expr_type && e->expr_type == &cxt.integer)
                r = e->expr_type;

            else
            {
                r = &cxt.integer;
                e->expr_type = r;
            }
        }
        void visit(Subtraction_expr *e)
        {
            assert(check(cxt, e->get_e1()) == &cxt.integer);
            assert(check(cxt, e->get_e2()) == &cxt.integer);

            if (e->expr_type && e->expr_type == &cxt.integer)
                r = e->expr_type;

            else
            {
                r = &cxt.integer;
                e->expr_type = r;
            }
        }
        void visit(Multiplication_expr *e)
        {
            assert(check(cxt, e->get_e1()) == &cxt.integer);
            assert(check(cxt, e->get_e2()) == &cxt.integer);

            if (e->expr_type && e->expr_type == &cxt.integer)
                r = e->expr_type;

            else
            {
                r = &cxt.integer;
                e->expr_type = r;
            }
        }
        void visit(Division_expr *e)
        {
            assert(check(cxt, e->get_e1()) == &cxt.integer);
            assert(check(cxt, e->get_e2()) == &cxt.integer);

            if (e->expr_type && e->expr_type == &cxt.integer)
                r = e->expr_type;

            else
            {
                r = &cxt.integer;
                e->expr_type = r;
            }
        }
        void visit(Modulus_expr *e)
        {
            assert(check(cxt, e->get_e1()) == &cxt.integer);
            assert(check(cxt, e->get_e2()) == &cxt.integer);

            if (e->expr_type && e->expr_type == &cxt.integer)
                r = e->expr_type;

            else
            {
                r = &cxt.integer;
                e->expr_type = r;
            }
        }
        void visit(Negation_expr *e)
        {
            assert(check(cxt, e->get_e()) == &cxt.integer);

            if (e->expr_type && e->expr_type == &cxt.integer)
                r = e->expr_type;

            else
            {
                r = &cxt.integer;
                e->expr_type = r;
            }
        }
    };
    V vis(cxt);
    e->accept(vis);
    return vis.r;
}