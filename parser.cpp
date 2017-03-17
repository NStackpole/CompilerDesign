//Nathan Stackpole, 2017

#include "parser.hpp"

bool parser::end_of_file() const
{
    return first == last;
}

char parser::look_ahead() const
{
    if (end_of_file())
        return 0;
    else
        return *first;
}

void parser::consume()
{
    if (end_of_file())
        return;
    buffer += *first;
    ++first;
}

bool parser::match(token_kind k)
{
    if (look_ahead() == k)
        consume();
    else
        throw("Syntax Error\n");
}