//Nathan Stackpole, 2017

#include "codegen.hpp"

int main(int argc, char *argv[])
{

    keyword_table *keywords = new keyword_table();
    symbol_table *symbols = new symbol_table();
    std::deque<scope *> scopes;
    scopes.push_back(new scope());
    std::vector<expr *> syntax_trees;

    char line[256];
    while (std::cin.getline(line, 256))
    {
        std::vector<token *> line_tokens = lex(line, keywords, symbols);
        syntax_trees.push_back(parse(line_tokens, symbols, scopes));
    }

    for( expr *e : syntax_trees)
    {
        //Code generation goes here
    }

}

std::vector<token *> lex(char *line, keyword_table *keywords, symbol_table *symbols)
{
    std::vector<token *> tokens;
    lexer line_lexer = lexer(line, keywords, symbols);
    token *current_token = line_lexer.next();

    while (current_token != nullptr)
    {
        tokens.push_back(current_token);
        current_token = line_lexer.next();
    }

    return tokens;
}

expr *parse(std::vector<token *> tokens, symbol_table *symbols, std::deque<scope *> &stack)
{
    parser p(tokens, symbols, stack);
    expr *current_expression = p.parse();
    return current_expression;
}