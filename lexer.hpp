//Nathan Stackpole, 2017

#ifndef LEX_HPP
#define LEX_HPP

#include <string>
#include <cstring>
#include "symbol.hpp"

struct token
{
    int name;
    std::string value;
    token(int, std::string);
    token(int, symbol*&);
    token(int);
    token();
};

struct integer_token : public token
{
    integer_token(std::string);
};

struct boolean_token : public token
{
    boolean_token(int);
};

struct id_token : public token
{
    id_token(symbol *);
};

enum token_kind
{
    false_tok,
    true_tok,
    L_parenth_tok,
    R_parenth_tok,
    plus_tok,
    minus_tok,
    star_tok,
    slash_tok,
    percent_tok,
    less_than_tok,
    less_than_eq_tok,
    more_than_tok,
    more_than_eq_tok,
    int_tok,
    pipe_tok,
    amp_tok,
    or_tok,
    and_tok,
    bang_tok,
    not_eq_tok,
    eq_tok,
    conditional_tok,
    otherwise_tok,
    id_tok
};

class lexer
{
    const char *first;
    const char *last;
    std::string buffer;

    bool end_of_file() const;
    char look_ahead() const;
    void consume();
    void ignore();
    token *word();
    bool match_letter(char);
    bool match_letter_digit(char);

  public:
    lexer(char *);
    token *next();
};

#endif