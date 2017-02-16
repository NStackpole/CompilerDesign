//Nathan Stackpole, 2017

#include "lexer.hpp"

token::token(int n) : name(n){}

void lexer::consume(){ ++first; }

bool lexer::EOF() const { return first == last; }

char lexer::look_ahead() const
{
    if(EOF())
        return 0;
    else
        return *first;
}

token* lexer::next()
{
    while(!EOF())
    {
        switch(look_ahead())
        {

        }
    }
    return nullptr;
}