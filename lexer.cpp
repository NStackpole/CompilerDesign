//Nathan Stackpole, 2017

#include "lexer.hpp"

token::token(int n) : name(n) {}
token::token(){}


integer_token::integer_token(int n) : value(n) 
{
    name = int_tok; 
}

bool lexer::end_of_file() const { return first == last; }

void lexer::consume() 
{
    if(end_of_file())
        return;
    buffer += *first++;
    first++;
}

void lexer::ignore()
{
    if(end_of_file())
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
            case '<':
                consume();
                if (look_ahead() == '=')
                {
                    consume();
                    return new token(less_than_eq_tok);
                }
                return new token(less_than_tok);
            case '>':
                consume();
                if (look_ahead() == '=')
                {
                    consume();
                    return new token(more_than_eq_tok);
                }
                else
                    return new token(more_than_tok);
            case ')':
                return new token(L_parenth_tok);
            case '(':
                return new token(R_parenth_tok);
            case '+':
                return new token(plus_tok);
            case '-':
                return new token(minus_tok);
            case '/':
                return new token(slash_tok);
            case '*':
                return new token(star_tok);
            case '&':
                return new token(amp_tok);
            case '|':
                if(look_ahead() == '|')
                {
                    consume();
                    return new token(or_tok);
                }
                return new token(pipe_tok);
            case '0'...'9':
                consume();

                while(!end_of_file() && std::isdigit(look_ahead()))
                    consume();

                int n = std::stoi(buffer);
                return new integer_token(n); 

                
        }
    }
    return nullptr;
}