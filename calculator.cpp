//Nathan Stackpole

#include "calculator.hpp"

int main(int argc, char *argv[])
{

    std::map<int, std::string> token_names;
    token_names[0] = "False";
    token_names[1] = "True";
    token_names[2] = "Left Parenth";
    token_names[3] = "Right Parenth";
    token_names[4] = "Plus";
    token_names[5] = "Minus";
    token_names[6] = "Star";
    token_names[7] = "Slash";
    token_names[8] = "Percent";
    token_names[9] = "Less Than";
    token_names[10] = "Less Than Or Equal";
    token_names[11] = "More Than";
    token_names[12] = "More Than Or Equal";
    token_names[13] = "Integer";
    token_names[14] = "Pipe";
    token_names[15] = "Ampersand";
    token_names[16] = "Or";
    token_names[17] = "And";

    char line[256];
    while (std::cin.getline(line, 256))
    {
        std::cout << line << "\n";
        std::vector<token *> line_tokens = lex_line(line, token_names);
        calculate(line_tokens);
    }
}

void calculate(std::vector<token *> line_tokens)
{
    //Placeholder calc function
    std::vector<int> integers;
    std::vector<bool> bools;

    for (int i = 0; i < line_tokens.size(); ++i)
    {
        if (line_tokens[i]->name == 0)
            bools.push_back(false);
        else if (line_tokens[i]->name == 1)
            bools.push_back(true);

        else if (line_tokens[i]->name == 13)
        {
            integers.push_back(std::stoi(line_tokens[i]->value));
        }

        else if (line_tokens[i]->name == 4)
        {
            integers.push_back(std::stoi((line_tokens[i + 1])->value));
            std::cout << "eval= " << integers[0] + integers[1] << "\n";
        }
    }
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