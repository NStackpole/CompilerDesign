//Nathan Stackpole

#include "type_check.hpp"

type *check(Context &cxt, expr *e)
{
    struct V : expr::Visitor
    {
        Context &cxt;
        type *r;
        V(Context &c) : cxt(c) {}

        //Visit functions for all the different types of expressions
        //Assert that the members of the function (if it has any) are of the right type, and then if so sets r to the proper type for that expr,
        // which will then get returned
        void visit(expr *e) { visit(e); }

        void visit(Bool_expr *e)
        {
            if (e->expr_type)
                r = e->expr_type;

            else
            {
                r = &cxt.boolean;
                e->expr_type = r;
            }
        }

        void visit(Integer_expr *e)
        {
            if (e->expr_type)
                r = e->expr_type;

            else
            {
                r = &cxt.integer;
                e->expr_type = r;
            }
        }

        void visit(And_expr *e)
        {
            //Check that the members of the expr are of the right type
            assert(check(cxt, e->get_e1()) == &cxt.boolean);
            assert(check(cxt, e->get_e2()) == &cxt.boolean);

            if (e->expr_type)
                r = e->expr_type;

            else
            {
                r = &cxt.boolean;
                e->expr_type = r;
            }
        }

        void visit(AndThen_expr *e)
        {
            //Check that the members of the expr are of the right type
            assert(check(cxt, e->get_e1()) == &cxt.boolean);
            assert(check(cxt, e->get_e2()) == &cxt.boolean);

            if (e->expr_type)
                r = e->expr_type;

            else
            {
                r = &cxt.boolean;
                e->expr_type = r;
            }
        }

        void visit(Or_expr *e)
        {
            //Check that the members of the expr are of the right type
            assert(check(cxt, e->get_e1()) == &cxt.boolean);
            assert(check(cxt, e->get_e2()) == &cxt.boolean);

            if (e->expr_type)
                r = e->expr_type;

            else
            {
                r = &cxt.boolean;
                e->expr_type = r;
            }
        }

        void visit(OrElse_expr *e)
        {
            //Check that the members of the expr are of the right type
            assert(check(cxt, e->get_e1()) == &cxt.boolean);
            assert(check(cxt, e->get_e2()) == &cxt.boolean);

            if (e->expr_type)
                r = e->expr_type;

            else
            {
                r = &cxt.boolean;
                e->expr_type = r;
            }
        }

        void visit(Not_expr *e)
        {
            //Check that the member of the expr are of the right type
            assert(check(cxt, e->get_e()) == &cxt.boolean);

            if (e->expr_type)
                r = e->expr_type;

            else
            {
                r = &cxt.boolean;
                e->expr_type = r;
            }
        }

        void visit(Xor_expr *e)
        {
            //Check that the members of the expr are of the right type
            assert(check(cxt, e->get_e1()) == &cxt.boolean);
            assert(check(cxt, e->get_e2()) == &cxt.boolean);

            if (e->expr_type)
                r = e->expr_type;

            r = &cxt.boolean;
            e->expr_type = r;
        }

        void visit(Conditional_expr *e)
        {
            //Check that the members of the expr are of the right type
            assert(check(cxt, e->get_e1()) == &cxt.boolean);
            assert(check(cxt, e->get_e2()) == &cxt.boolean);
            assert(check(cxt, e->get_e3()) == &cxt.boolean);

            if (e->expr_type)
                r = e->expr_type;

            else
            {
                r = &cxt.boolean;
                e->expr_type = r;
            }
        }

        void visit(LessThan_expr *e)
        {
            //Check that the members of the expr are of the right type
            assert(check(cxt, e->get_e1()) == &cxt.integer);
            assert(check(cxt, e->get_e2()) == &cxt.integer);

            if (e->expr_type)
                r = e->expr_type;

            else
            {
                r = &cxt.boolean;
                e->expr_type = r;
            }
        }

        void visit(MoreThan_expr *e)
        {
            //Check that the members of the expr are of the right type
            assert(check(cxt, e->get_e1()) == &cxt.integer);
            assert(check(cxt, e->get_e2()) == &cxt.integer);

            if (e->expr_type)
                r = e->expr_type;

            else
            {
                r = &cxt.boolean;
                e->expr_type = r;
            }
        }

        void visit(EqualTo_expr *e)
        {
            //Check that the members of the expr are of the same type
            assert(check(cxt, e->get_e1()) == check(cxt, e->get_e2()));

            if (e->expr_type)
                r = e->expr_type;

            else
            {
                r = &cxt.boolean;
                e->expr_type = r;
            }
        }

        void visit(NotEqualTo_expr *e)
        {
            //Check that the members of the expr are of the same type
            assert(check(cxt, e->get_e1()) == check(cxt, e->get_e2()));

            if (e->expr_type)
                r = e->expr_type;

            else
            {
                r = &cxt.boolean;
                e->expr_type = r;
            }
        }

        void visit(LessThanOrEqualTo_expr *e)
        {
            //Check that the members of the expr are of the right type
            assert(check(cxt, e->get_e1()) == &cxt.integer);
            assert(check(cxt, e->get_e2()) == &cxt.integer);

            if (e->expr_type)
                r = e->expr_type;

            else
            {
                r = &cxt.boolean;
                e->expr_type = r;
            }
        }

        void visit(MoreThanOrEqualTo_expr *e)
        {
            //Check that the members of the expr are of the right type
            assert(check(cxt, e->get_e1()) == &cxt.integer);
            assert(check(cxt, e->get_e2()) == &cxt.integer);

            if (e->expr_type)
                r = e->expr_type;

            else
            {
                r = &cxt.integer;
                e->expr_type = r;
            }
        }

        void visit(Addition_expr *e)
        {
            //Check that the members of the expr are of the right type
            assert(check(cxt, e->get_e1()) == &cxt.integer);
            assert(check(cxt, e->get_e2()) == &cxt.integer);

            if (e->expr_type)
                r = e->expr_type;

            else
            {
                r = &cxt.integer;
                e->expr_type = r;
            }
        }

        void visit(Subtraction_expr *e)
        {
            //Check that the members of the expr are of the right type
            assert(check(cxt, e->get_e1()) == &cxt.integer);
            assert(check(cxt, e->get_e2()) == &cxt.integer);

            if (e->expr_type)
                r = e->expr_type;

            else
            {
                r = &cxt.integer;
                e->expr_type = r;
            }
        }

        void visit(Multiplication_expr *e)
        {
            //Check that the members of the expr are of the right type
            assert(check(cxt, e->get_e1()) == &cxt.integer);
            assert(check(cxt, e->get_e2()) == &cxt.integer);

            if (e->expr_type)
                r = e->expr_type;

            else
            {
                r = &cxt.integer;
                e->expr_type = r;
            }
        }

        void visit(Division_expr *e)
        {
            //Check that the members of the expr are of the right type
            assert(check(cxt, e->get_e1()) == &cxt.integer);
            assert(check(cxt, e->get_e2()) == &cxt.integer);

            if (e->expr_type)
                r = e->expr_type;

            else
            {
                r = &cxt.integer;
                e->expr_type = r;
            }
        }

        void visit(Modulus_expr *e)
        {
            //Check that the members of the expr are of the right type
            assert(check(cxt, e->get_e1()) == &cxt.integer);
            assert(check(cxt, e->get_e2()) == &cxt.integer);

            if (e->expr_type)
                r = e->expr_type;

            else
            {
                r = &cxt.integer;
                e->expr_type = r;
            }
        }

        void visit(Negation_expr *e)
        {
            //Check that the member of the expr are of the right type
            assert(check(cxt, e->get_e()) == &cxt.integer);

            if (e->expr_type)
                r = e->expr_type;

            else
            {
                r = &cxt.integer;
                e->expr_type = r;
            }
        }
    };

    //create a visitor object, passing in the context
    V vis(cxt);

    //Calls the accept function which calls the visit function for the expr
    e->accept(vis);

    //Return the proper type for the expr
    return vis.r;
}