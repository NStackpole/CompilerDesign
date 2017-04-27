//Nathan Stackpole, 2017

#include "symbol.hpp"
#include "token.hpp"
#include <string>
#include <cstring>

#ifndef LEX_HPP
#define LEX_HPP

class lexer
{
    const char *first;
    const char *last;
    std::string buffer;
    const keyword_table *keywords;
    symbol_table *symbols;

    bool end_of_file() const;
    char look_ahead() const;
    void consume();
    void ignore();
    token *word();
    bool match_letter(char);
    bool match_letter_digit(char);

  public:
    lexer(char *, keyword_table *, symbol_table *);
    token *next();
};

#endif