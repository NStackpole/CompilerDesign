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
        std::cout << "\n";
    }
}

void calculate(std::vector<token *> line_tokens)
{
    //Placeholder calc function
    std::vector<expr *> expressions;

    for (int i = 0; i < line_tokens.size(); ++i)
    {
        if (line_tokens[i]->name == 0)
            expressions.push_back(new Bool_expr(false));
        else if (line_tokens[i]->name == 1)
            expressions.push_back(new Bool_expr(true));
        /*else if (line_tokens[i]->name == 4)
            expressions.push_back(new Addition_expr());*/
        else if (line_tokens[i]->name == 13)
        {
            std::cout << "";
            expressions.push_back(new Integer_expr(std::stoi(line_tokens[i]->value)));
            if (i > 1)
            {
                std::cout<<"i>1\n";
                if (line_tokens[i - 1]->name == 4 && line_tokens[i - 2]->name == 13)
                {
                    std::cout<<"Making addition expr\n" << expressions.size() << "\n\n";
                    Addition_expr current_add_expr = Addition_expr(expressions[0], expressions[1]);
                    std::cout << "Evaluation: " << eval(&current_add_expr) << "\n\n";
                }
            }
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