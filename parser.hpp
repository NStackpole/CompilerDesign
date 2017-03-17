//Nathan Stackpole, 2017

#include "lexer.hpp"

#ifndef PARSE_HPP
#define PARSE_HPP

class parser
{
    char *first;
    char *last;
    std::string buffer;

  public:
    bool match(token_kind k);
    void consume();
    char look_ahead() const;
    bool end_of_file() const;
};

#endif