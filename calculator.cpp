//Nathan Stackpole

#include "calculator.hpp"

int main(int argc, char *argv[])
{
    char line[256];
    while(std::cin.getline(line,256))
    {
        std::cout<<line<<"\n";
        std::vector<token *> line_tokens = lex_line(line);

    }

}

void calculate(std::vector<token *> line_tokens)
{
}

std::vector<token *> lex_line(char* line)
{
    std::vector<token *> tokens;
    lexer line_lexer = lexer(line);
    token* current_token = line_lexer.next(); 
    while(current_token != nullptr)
    {
        tokens.push_back(current_token);
        current_token = line_lexer.next();
    }

    for(int i = 0; i<tokens.size(); ++i)
    {
        std::cout<<tokens[i]->name<<"\n";
    }

    return tokens;
}