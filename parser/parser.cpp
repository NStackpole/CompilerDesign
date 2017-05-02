//Nathan Stackpole, 2017

#include "parser.hpp"
#include "../AST/eval.hpp"

parser::parser(std::vector<token *> &tokens, symbol_table *S, std::deque<scope *> &scopes) : line(tokens), symbols(S), scope_stack(scopes), index(0) {}

bool parser::end_of_file() const
{
    return index == line.size();
}

int parser::look_ahead()
{
    if (end_of_file())
        return -1;
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
        throw "expected '" + token_names.at(k) + "\'\n";
    }
}

token *parser::match_if(token_kind k)
{
    if (look_ahead() == k)
        return consume();
    else
        return nullptr;
}

token *parser::require(token_kind k)
{
    assert(look_ahead() == k);
    return consume();
}

expr *parser::parse()
{

    //An unordered_map used for printing out token names.

    token_names[false_tok] = "false";
    token_names[true_tok] = "true";
    token_names[L_parenth_tok] = "(";
    token_names[R_parenth_tok] = ")";
    token_names[plus_tok] = "+";
    token_names[minus_tok] = "-";
    token_names[star_tok] = "*";
    token_names[slash_tok] = "/";
    token_names[percent_tok] = "%";
    token_names[less_than_tok] = "<";
    token_names[less_than_eq_tok] = "<=";
    token_names[more_than_tok] = ">";
    token_names[more_than_eq_tok] = ">=";
    token_names[int_tok] = "Integer";
    token_names[pipe_tok] = "|";
    token_names[amp_tok] = "&";
    token_names[or_tok] = "||";
    token_names[and_tok] = "&&";
    token_names[bang_tok] = "!";
    token_names[not_eq_tok] = "!=";
    token_names[eq_tok] = "==";
    token_names[conditional_tok] = "?";
    token_names[otherwise_tok] = ":";
    token_names[true_key] = "True keyword";
    token_names[false_key] = "False keyword";
    token_names[bool_key] = "bool keyword";
    token_names[int_key] = "int keyword";
    token_names[var_key] = "var keyword";
    token_names[assign_tok] = "=";
    token_names[id_tok] = "Identifier token";
    token_names[if_key] = "if keyword";
    token_names[else_key] = "else keyword";
    token_names[L_bracket_tok] = "{";
    token_names[R_bracket_tok] = "}";
    token_names[assert_key] = "assert";

    try
    {
        return statement_seq();
    }
    catch (std::string error)
    {
        std::cerr << "\nException Caught In Parsing: \n";
        std::cerr << error << "\n";
        return nullptr;
    }
}

expr *parser::statement_seq()
{
    return stmt();
}

expr *parser::stmt()
{
    switch (look_ahead())
    {
    //If the var keyword was lexed then start a new declaration statement
    case var_key:
        return declaration_statement()->entity->init;
    case if_key:
        return conditional_statement();
    case L_bracket_tok:
        return start_block_statement();
        break;
    case R_bracket_tok:
        return end_block_statement();
    case assert_key:
        return assertion_statement();

    //If just an id_tok is found we want to check for an assignment statement
    case id_tok:
        //Don't want to comnsume the id_tok in case there isnt an assign_tok ahead
        //so we manually check if there is an assign_tok in the right spot and if so
        // call assignment_expression()
        if (line.size() > 1)
            if (line[index + 1]->name == assign_tok)
                return assignment_expression();
    default:
        return expression_statement()->expression;
    }
}

decl_statement *parser::declaration_statement()
{
    decl *d = declaration();
    return new decl_statement(d);
}

expr_statement *parser::expression_statement()
{
    expr *e = expression();
    return new expr_statement(e);
}

expr *parser::conditional_statement()
{
    consume();
    require(L_parenth_tok);
    expr *e1 = expression();
    require(R_parenth_tok);
    expr *e2 = stmt();
    require(else_key);
    expr *e3 = stmt();
    
    return new Conditional_expr(e1, e2,e3) ;
}

expr *parser::start_block_statement()
{
    require(L_bracket_tok);
    scope_stack.push_back(new scope());
    return nullptr;
}

expr *parser::end_block_statement()
{
    require(R_bracket_tok);
    scope_stack.pop_back();
    return nullptr;
}

expr *parser::assertion_statement()
{
    consume();
    require(L_parenth_tok);
    expr* e = expression();
    assert(eval(e));
    require(R_parenth_tok);
    return nullptr;
}

expr *parser::assignment_expression()
{
    symbol *id = identifier();
    id = symbols->find(*id);
    match(assign_tok);

    // If the variable is already in scope, overwrite the decl mapped to the symbol
    
    for(int i = scope_stack.size() - 1; i >=0; --i)
    {
        if (scope_stack[i]->find(*id) != nullptr)
        {
            decl *var = new decl();
            expr *e = expression();
            var->init = e;
            scope_stack[i]->modify(*id, var);
            return e;
        }
    }
    throw std::string(*id + " not declared");
}



decl *parser::declaration()
{
    switch (look_ahead())
    {
    case var_key:
        return variable_declaration();
    default:
        break;
    }
    throw std::string("Expected declaration\n");
}

decl *parser::variable_declaration()
{
    require(var_key);
    type *t = type_specifier();
    symbol *n = identifier();
    symbols->insert(*n);
    decl *var = new decl();
    match(assign_tok);
    expr *e = expression();
    require(semi_col_tok);
    var->init = e;
    scope_stack.back()->insert(*n, var);
    return var;
}

type *parser::type_specifier()
{
    switch (look_ahead())
    {
    case bool_key:
        consume();
        return new bool_type();
    case int_key:
        consume();
        return new integer_type();
    }

    throw std::string("Expected type specifier\n");
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
    case id_tok:
        return id_expression();
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
    case true_key:
        consume();
        return new Bool_expr(true);
    case false_key:
        consume();
        return new Bool_expr(false);
    default:
        break;
    }
    throw std::string("primary expression excpeted\n");
}

expr *parser::id_expression()
{
    symbol *id = identifier();
    id = symbols->find(*id);
    //Check the scope stack for the variable.
    for (int i = scope_stack.size() - 1; i >=0; --i)
    {
        decl *d = scope_stack[i]->find(*id);
        if (d != nullptr)
            return d->init;
    }
    throw std::string(*id + " not declared\n");
}

symbol *parser::identifier()
{
    token *id = match(id_tok);
    symbol *sym = &id->value;
    return sym;
}