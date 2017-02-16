//Nathan Stackpole, 2017

struct token
{
    token(int n);

    int name;
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
    more_than_eq_tok
};

class lexer
{
    const char* first;
    const char* last;

    bool EOF() const;
    char look_ahead() const;
    void consume();
    token* next();

};