//Nathan Stackpole

#include "calculator.hpp"

int main(int argc, char *argv[])
{

    std::map<int, std::string> token_names;
    token_names[0] = "False token";
    token_names[1] = "True token";
    token_names[2] = "Left Parenth token";
    token_names[3] = "Right Parenth token";
    token_names[4] = "Plus token";
    token_names[5] = "Minus token";
    token_names[6] = "Star token";
    token_names[7] = "Slash token";
    token_names[8] = "Percent token";
    token_names[9] = "Less Than token";
    token_names[10] = "Less Than Or Equal token";
    token_names[11] = "More Than token";
    token_names[12] = "More Than Or Equal token";
    token_names[13] = "Integer token";
    token_names[14] = "Pipe token";
    token_names[15] = "Ampersand token";
    token_names[16] = "Or token";
    token_names[17] = "And token";

    char line[256];
    while (std::cin.getline(line, 256))
    {
        std::cout << line << "\n";
        std::vector<token *> line_tokens = lex_line(line, token_names);
        calculate(line_tokens);
        std::cout << "\n";
    }
}

void calculate(std::vector<token *> line_tokens)
{
    
}

std::vector<token *> lex_line(char *line, std::map<int, std::string> &token_names)
{
    std::vector<token *> tokens;
    lexer line_lexer = lexer(line);
    token *current_token = line_lexer.next();
    while (current_token != nullptr)
    {
        tokens.push_back(current_token);
        current_token = line_lexer.next();
    }

    for (int i = 0; i < tokens.size(); ++i)
    {
        std::cout << tokens[i]->name << " -> " << token_names[tokens[i]->name] << " -> " << tokens[i]->value << "\n";
    }

    return tokens;
}