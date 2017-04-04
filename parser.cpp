//Nathan Stackpole, 2017

#include "parser.hpp"

parser::parser(std::vector<token *> tokens) : line(tokens), index(0) {}

bool parser::end_of_file() const
{
    return index == line.size();
}

int parser::look_ahead()
{
    if (end_of_file())
        return 0;
    else
        return line[index]->name;
}

token *parser::consume()
{
    if (end_of_file())
        return nullptr;
    ++index;
    return line[index - 1];
}

token *parser::match(token_kind k)
{
    if (look_ahead() == k)
        return consume();
    else
    {
        std::stringstream ss;
        ss << "expected '" << token_names.at(k) << '\'';
        throw(ss.str().c_str());
    }
}

token *parser::match_if(token_kind k)
{
    if (look_ahead() == k)
        return consume();
    else
        return nullptr;
}

expr *parser::parse()
{

    //A map used for printing out token names.

    token_names[0] = "False token";
    token_names[1] = "True token";
    token_names[2] = "Left Parenth token";
    token_names[3] = "Right Parenth token";
    token_names[4] = "Plus token";
    token_names[5] = "Minus token";
    token_names[6] = "Star token";
    token_names[7] = "Slash token";
    token_names[8] = "Percent token";
    token_names[9] = "Less Than token";
    token_names[10] = "Less Than Or Equal token";
    token_names[11] = "More Than token";
    token_names[12] = "More Than Or Equal token";
    token_names[13] = "Integer token";
    token_names[14] = "Pipe token";
    token_names[15] = "Ampersand token";
    token_names[16] = "Or token";
    token_names[17] = "And token";
    token_names[18] = "Bang token";
    token_names[19] = "Not Equals token";
    token_names[20] = "Equals token";
    token_names[21] = "Conditional token";
    token_names[22] = "Otherwise token";

    try
    {
        return expression();
    }
    catch (const char *error)
    {
        std::cerr << error << "\n";
        return nullptr;
    }
}

expr *parser::expression()
{
    return conditional_expression();
}

expr *parser::conditional_expression()
{
    expr *e1 = logical_or_expression();
    while (true)
    {
        if (match_if(conditional_tok))
        {
            expr *e2 = logical_or_expression();
            if (match_if(otherwise_tok))
            {
                expr *e3 = logical_or_expression();
                e1 = new Conditional_expr(e1, e2, e3);
            }
        }
        else
            break;
    }
    return e1;
}

expr *parser::logical_or_expression()
{
    expr *e1 = logical_and_expression();
    while (true)
    {
        if (match_if(or_tok))
        {
            expr *e2 = logical_and_expression();
            e1 = new OrElse_expr(e1, e2);
        }
        else
            break;
    }
    return e1;
}

expr *parser::logical_and_expression()
{
    expr *e1 = equality_expression();
    while (true)
    {
        if (match_if(and_tok))
        {
            expr *e2 = equality_expression();
            e1 = new AndThen_expr(e1, e2);
        }
        else
            break;
    }
    return e1;
}

expr *parser::equality_expression()
{
    expr *e1 = ordering_expression();
    while (true)
    {
        if (match_if(eq_tok))
        {
            expr *e2 = ordering_expression();
            e1 = new EqualTo_expr(e1, e2);
        }

        else if (match_if(not_eq_tok))
        {
            expr *e2 = ordering_expression();
            e1 = new NotEqualTo_expr(e1, e2);
        }
        else
            break;
    }
    return e1;
}

expr *parser::ordering_expression()
{
    expr *e1 = additive_expression();
    while (true)
    {
        if (match_if(less_than_tok))
        {
            expr *e2 = additive_expression();
            e1 = new LessThan_expr(e1, e2);
        }

        else if (match_if(more_than_tok))
        {
            expr *e2 = additive_expression();
            e1 = new MoreThan_expr(e1, e2);
        }

        else if (match_if(more_than_eq_tok))
        {
            expr *e2 = additive_expression();
            e1 = new MoreThanOrEqualTo_expr(e1, e2);
        }

        else if (match_if(less_than_eq_tok))
        {
            expr *e2 = additive_expression();
            e1 = new LessThanOrEqualTo_expr(e1, e2);
        }

        else
            break;
    }
    return e1;
}

expr *parser::additive_expression()
{
    expr *e1 = multiplicative_expression();
    while (true)
    {
        if (match_if(plus_tok))
        {
            expr *e2 = multiplicative_expression();
            e1 = new Addition_expr(e1, e2);
        }
        else if (match_if(minus_tok))
        {
            expr *e2 = multiplicative_expression();
            e1 = new Subtraction_expr(e1, e2);
        }
        else
            break;
    }
    return e1;
}

expr *parser::multiplicative_expression()
{
    expr *e1 = unary_expression();
    while (true)
    {
        if (match_if(star_tok))
        {
            expr *e2 = unary_expression();
            e1 = new Multiplication_expr(e1, e2);
        }

        else if (match_if(slash_tok))
        {
            expr *e2 = unary_expression();
            e1 = new Division_expr(e1, e2);
        }

        else if (match_if(percent_tok))
        {
            expr *e2 = unary_expression();
            e1 = new Modulus_expr(e1, e2);
        }
        else
            break;
    }
    return e1;
}

expr *parser::unary_expression()
{
    if (match_if(minus_tok))
    {
        expr *e = unary_expression();
        e = new Negation_expr(e);
        return e;
    }
    else if (match_if(bang_tok))
    {
        expr *e = unary_expression();
        e = new Not_expr(e);
        return e;
    }
    else
        return primary_expression();
}

expr *parser::primary_expression()
{
    switch (look_ahead())
    {
    case int_tok:
        return new Integer_expr(std::stoi(consume()->value));
    case L_parenth_tok:
    {
        consume();
        expr *e = expression();
        match(R_parenth_tok);
        return e;
    }
    case true_tok:
        consume();
        return new Bool_expr(true);
    case false_tok:
        consume();
        return new Bool_expr(false);
    default:
        break;
    }
    throw("primary expression excpeted\n");
}