//Nathan Stackpole, 2017

#include <cctype>
#include <string>

struct token
{
    int name;
    token(int);
    token();
};

struct integer_token : public token
{
    int value;
    integer_token(int);
};

enum token_kind
{
    eof_tok,
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
    or_tok
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
    token* next();
};