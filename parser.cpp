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

token* parser::consume()
{
    if (end_of_file())
        return nullptr;
    ++index;
    return line[index-1];
}

token* parser::match(token_kind k)
{
    if (look_ahead() == k)
        return consume();
    else
        throw("Syntax Error\n");
}

token* parser::match_if(token_kind k)
{
    if (look_ahead() == k)
        return consume();
    else
        return nullptr;
}

token* parser::require(token_kind k)
{
    assert(look_ahead() == k);
    return consume();
}

expr* parser::parse()
{
    return expression();
}

expr* parser::expression()
{
    return additive_expression();
}

expr* parser::additive_expression()
{
    expr* e1 = multiplicative_expression();
    while(true)
    {
        if(match_if(plus_tok))
        {
            expr* e2 = multiplicative_expression();
            e1 = new Addition_expr(e1,e2);
        }
        else if(match_if(minus_tok))
        {
            expr* e2 = multiplicative_expression();
            e1 = new Subtraction_expr(e1,e2);
        }
        else 
            break;
    }
    return e1;
}

expr* parser::multiplicative_expression()
{
    expr* e1 = unary_expression();
    while (true)
    {
        if (match_if(star_tok))
        {
            expr* e2 = unary_expression();
            e1 = new Multiplication_expr(e1,e2);
        }

        else if (match_if(slash_tok))
        {
            expr* e2 = unary_expression();
            e1 = new Division_expr(e1,e2);
        }

        else if (match_if(percent_tok))
        {
            expr* e2 = unary_expression();
            e1 = new Modulus_expr(e1,e2);
        }
        else
            break;
    }
    return e1;
}

expr* parser::unary_expression()
{
    if (match_if(minus_tok))
    {
        expr* e = unary_expression();
        e = new Negation_expr(e);
        return e;
    }
    else if (match_if(bang_tok))
    {
        expr* e = unary_expression();
        e = new Not_expr(e);
        return e;
    }
    else
        return primary_expression();
}

expr* parser::primary_expression()
{
    switch (look_ahead())
    {
        case int_tok:
            return new Integer_expr(std::stoi(consume()->value));
        case L_parenth_tok:
        {
            consume();
            expr* e = expression();
            match(R_parenth_tok);
            return e;
        }
        case true_tok:
            return new Bool_expr(true);
        case false_tok:
            return new Bool_expr(false);
        default:
            break;
    }
}