#include "token.hpp"

token::token(int n, std::string s) : name(n), value(s) {}
token::token(int n, symbol *S) : name(n), value(*S) {}
token::token(int n) : name(n) {}
token::token() {}

integer_token::integer_token(std::string n)
{
    value = n;
    name = int_tok;
}

boolean_token::boolean_token(int n)
{
    name = n;
    if (n == 0)
        value = "false";
    else if (n == 1)
        value = "true";
}

id_token::id_token(symbol *S) : token(id_tok, S) {}