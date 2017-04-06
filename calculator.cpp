//Nathan Stackpole, 2017

#include "calculator.hpp"

int main(int argc, char *argv[])
{

    //An unordered_map used for printing out token names.
    std::unordered_map<int, std::string> token_names;
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
    token_names[18] = "Bang token";
    token_names[19] = "Not Equals token";
    token_names[20] = "Equals token";
    token_names[21] = "Conditional token";
    token_names[22] = "Otherwise token";

    //Read in a line at a time, create tokens from it, turn those tokens into expressions that are then evaluated.
    char line[256];
    while (std::cin.getline(line, 256))
    {
        std::cout << line << "\n";
        std::vector<token *> line_tokens = lex_line(line, token_names);

        if (line_tokens.size() > 1)
            calculate(line_tokens);

        std::cout << "\n";
    }
}

//Finds the variables in a line and expression type. Will probably be replaced when the parser is complete.
//Only works for one expression per line and does not work with conditional expressions.
//If an expression cannot be evaluated it is simply skipped.
void calculate(std::vector<token *> line_tokens)
{
    parser p(line_tokens);
    expr* current_expression = p.parse();
    if(current_expression != nullptr)
        std::cout << "Evaluation: " << eval(current_expression) << "\n";
    else
        std::cout << "Expression could not be evaluated.\n";
}

//Creates a lexer object with the line that was passed in and creates tokens. The name and attribute of each token are then printed out.
std::vector<token *> lex_line(char *line, std::unordered_map<int, std::string> &token_names)
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