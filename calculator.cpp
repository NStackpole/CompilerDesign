//Nathan Stackpole, 2017

#include "calculator.hpp"

int main(int argc, char *argv[])
{

    //An unordered_map used for printing out token names.
    std::unordered_map<int, std::string> token_names;
    token_names[false_tok] = "False token";
    token_names[true_tok] = "True token";
    token_names[L_parenth_tok] = "Left Parenth token";
    token_names[R_parenth_tok] = "Right Parenth token";
    token_names[plus_tok] = "Plus token";
    token_names[minus_tok] = "Minus token";
    token_names[star_tok] = "Star token";
    token_names[slash_tok] = "Slash token";
    token_names[percent_tok] = "Percent token";
    token_names[less_than_tok] = "Less Than token";
    token_names[less_than_eq_tok] = "Less Than Or Equal token";
    token_names[more_than_tok] = "More Than token";
    token_names[more_than_eq_tok] = "More Than Or Equal token";
    token_names[int_tok] = "Integer token";
    token_names[pipe_tok] = "Pipe token";
    token_names[amp_tok] = "Ampersand token";
    token_names[or_tok] = "Or token";
    token_names[and_tok] = "And token";
    token_names[bang_tok] = "Bang token";
    token_names[not_eq_tok] = "Not Equals token";
    token_names[eq_tok] = "Equals token";
    token_names[conditional_tok] = "Conditional token";
    token_names[otherwise_tok] = "Otherwise token";
    token_names[true_key] = "True keyword";
    token_names[false_key] = "False keyword";
    token_names[bool_key] = "bool keyword";
    token_names[int_key] = "int keyword";
    token_names[var_key] = "var keyword";
    token_names[assign_tok] = "Assignment token";
    token_names[id_tok] = "Identifier token";
    token_names[if_key] = "if keyword";
    token_names[else_key] = "else keyword";
    token_names[L_bracket_tok] = "Left bracket token";
    token_names[R_bracket_tok] = "Right bracket token";

    keyword_table *keywords = new keyword_table();
    symbol_table *symbols = new symbol_table();
    std::deque<scope *> scopes;
    scopes.push_back(new scope());

    //Read in a line at a time, create tokens from it, turn those tokens into expressions that are then evaluated.
    char line[256];
    while (std::cin.getline(line, 256))
    {
        std::cout << line << "\n";
        std::vector<token *> line_tokens = lex_line(line, token_names, keywords, symbols);

        if (line_tokens.size() >= 1)
            calculate(line_tokens, symbols, scopes);

        std::cout << "\n";
    }
}

//Finds the variables in a line and expression type. Will probably be replaced when the parser is complete.
//Only works for one expression per line and does not work with conditional expressions.
//If an expression cannot be evaluated it is simply skipped.
void calculate(std::vector<token *> &line_tokens, symbol_table *symbols, std::deque<scope *> &scopes)
{
    parser p(line_tokens, symbols, scopes);
    expr *current_expression = p.parse();
    if (current_expression != nullptr)
        std::cout << "Evaluation: " << eval(current_expression) << "\n";
    else
        std::cout << "Expression could not be evaluated.\n";
}

//Creates a lexer object with the line that was passed in and creates tokens. The name and attribute of each token are then printed out.
std::vector<token *> lex_line(char *line, std::unordered_map<int, std::string> &token_names, keyword_table *keywords, symbol_table *symbols)
{
    std::vector<token *> tokens;
    lexer line_lexer = lexer(line, keywords, symbols);
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