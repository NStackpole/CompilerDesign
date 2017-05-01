//Nathan Stackpole, 2017

#include "lexer.hpp"

lexer::lexer(char *line, keyword_table *kw, symbol_table *syms) : first(line), last(&line[std::strlen(line)]), keywords(kw), symbols(syms)
{
}

keyword_table::keyword_table()
{
    insert({"false", false_key});
    insert({"true", true_key});
    insert({"var", var_key});
    insert({"int", int_key});
    insert({"bool", bool_key});
}

bool lexer::end_of_file() const { return first == last; }

void lexer::consume()
{
    if (end_of_file())
        return;
    buffer += *first;
    first++;
}

void lexer::ignore()
{
    if (end_of_file())
        return;
    first++;
}

char lexer::look_ahead() const
{
    if (end_of_file())
        return 0;
    else
        return *first;
}

bool lexer::match_letter(char c)
{
    return (std::isalpha(c) || c == '_');
}

bool lexer::match_letter_digit(char c)
{
    return (std::isdigit(c) || std::isalpha(c) || c == '_');
}

token *lexer::next()
{
    buffer.clear();
    while (!end_of_file())
    {
        switch (look_ahead())
        {
        case ' ':
            ignore();
            break;
        case '#':
            first = last;
            break;
        case '<':
            consume();
            if (look_ahead() == '=')
            {
                consume();
                return new token(less_than_eq_tok, buffer);
            }
            return new token(less_than_tok, buffer);
            break;
        case '>':
            consume();
            if (look_ahead() == '=')
            {
                consume();
                return new token(more_than_eq_tok, buffer);
            }
            else
                return new token(more_than_tok, buffer);
            break;
        case ')':
            consume();
            return new token(R_parenth_tok, buffer);
            break;
        case '(':
            consume();
            return new token(L_parenth_tok, buffer);
            break;
        case '+':
            consume();
            return new token(plus_tok, buffer);
            break;
        case '-':
            consume();
            return new token(minus_tok, buffer);
            break;
        case '!':
            consume();
            if (look_ahead() == '=')
            {
                consume();
                return new token(not_eq_tok, buffer);
            }
            return new token(bang_tok, buffer);
            break;
        case '=':
            consume();
            if (look_ahead() == '=')
            {
                consume();
                return new token(eq_tok, buffer);
            }
            
            else
            {
                return new token(assign_tok, buffer);
            }
            break;
        case '?':
            consume();
            return new token(conditional_tok, buffer);
            break;
        case ':':
            consume();
            return new token(otherwise_tok, buffer);
            break;
        case ';':
            consume();
            return new token(semi_col_tok, buffer);
            break;
        case '/':
            consume();
            return new token(slash_tok, buffer);
            break;
        case '%':
            consume();
            return new token(percent_tok, buffer);
            break;
        case '*':
            consume();
            return new token(star_tok, buffer);
            break;
        case '&':
            consume();
            if (look_ahead() == '&')
            {
                consume();
                return new token(and_tok, buffer);
            }
            return new token(amp_tok, buffer);
            break;
        case '|':
            consume();
            if (look_ahead() == '|')
            {
                consume();
                return new token(or_tok, buffer);
            }
            return new token(pipe_tok, buffer);
            break;
        case '0' ... '9':
            consume();

            while (!end_of_file() && std::isdigit(look_ahead()))
                consume();

            return new integer_token(buffer);
            break;
        default:
            if (match_letter(look_ahead()))
                return word();
            else 
                return nullptr;
        }
    }
    return nullptr;
}

token *lexer::word()
{
    consume();
    while (!end_of_file() && match_letter_digit(look_ahead()))
        consume();

    auto key = keywords->find(buffer);

    if (key != keywords->end())
    {
        token *new_tok = new token(key->second);
        return new_tok;
    }

    symbol *new_symbol = symbols->insert(buffer);
    token *new_tok = new id_token(new_symbol);
    return new_tok;
}