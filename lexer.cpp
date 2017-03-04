//Nathan Stackpole, 2017

#include "lexer.hpp"

lexer::lexer(char* line) : first(line), last(&line[std::strlen(line)])
{
}

token::token(int n, std::string s) : name(n), value(s) {}
token::token() {}

integer_token::integer_token(std::string n) 
{
    value = n;
    name = int_tok;
}

boolean_token::boolean_token(int n)
{
    name = n;
    if(n == 0)
        value = "false";
    else if (n==1)
        value = "true";
};

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

token *lexer::next()
{
    buffer.clear();
    while (!end_of_file())
    {
        switch (look_ahead())
        {
        case ' ':
            //consume();
            first++;
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
        case '>':
            consume();
            if (look_ahead() == '=')
            {
                consume();
                return new token(more_than_eq_tok, buffer);
            }
            else
                return new token(more_than_tok, buffer);
        case ')':
            consume();
            return new token(R_parenth_tok, buffer);
        case '(':
            consume();
            return new token(L_parenth_tok, buffer);
        case '+':
            consume();
            return new token(plus_tok, buffer);
        case '-':
            consume();
            return new token(minus_tok, buffer);
        case '/':
            consume();
            return new token(slash_tok, buffer);
        case '*':
            consume();
            return new token(star_tok, buffer);
        case '&':
            if (look_ahead() == '&')
            {
                consume();
                return new token(and_tok, buffer);
            }
            return new token(amp_tok, buffer);
        case '|':
            if (look_ahead() == '|')
            {
                consume();
                return new token(or_tok, buffer);
            }
            return new token(pipe_tok, buffer);
        case '0' ... '9':
            consume();

            while (!end_of_file() && std::isdigit(look_ahead()))
                consume();

            return new integer_token(buffer);
        }
    }
    return nullptr;
}