//Nathan Stackpole, 2017

#include "calculator.hpp"

int main(int argc, char *argv[])
{

    //A map used for printing out token names.
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
    std::vector<Integer_expr *> integers;
    std::vector<Bool_expr *> booleans;
    int expression_type;

    for (int i = 0; i < line_tokens.size(); ++i)
    {
        if (line_tokens[i]->name == 13)
            integers.push_back(new Integer_expr(std::stoi(line_tokens[i]->value)));
        else if (line_tokens[i]->name == 0)
            booleans.push_back(new Bool_expr(false));
        else if (line_tokens[i]->name == 1)
            booleans.push_back(new Bool_expr(true));
        else if (line_tokens[i]->name == 21)
            return;
        else
            expression_type = line_tokens[i]->name;
    }

    if (expression_type == 18)
        assert(booleans.size() == 1);
    else
        assert(integers.size() == 2 || booleans.size() == 2);

    create_expression(expression_type, integers, booleans);
}

//Creates a lexer object with the line that was passed in and creates tokens. The name and attribute of each token are then printed out.
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

//Creates an expression with a given expression type and expression variables.
void create_expression(int expression_type, std::vector<Integer_expr *> integers, std::vector<Bool_expr *> booleans)
{
    
    switch (expression_type)
    {

    case (4):
    {
        Addition_expr current_expr = Addition_expr(integers[0], integers[1]);
        std::cout << "Evaluation: " << eval(&current_expr) << "\n\n";
        break;
    }
    case (5):
    {
        Subtraction_expr current_expr = Subtraction_expr(integers[0], integers[1]);
        std::cout << "Evaluation: " << eval(&current_expr) << "\n\n";
        break;
    }
    case (6):
    {
        Multiplication_expr current_expr = Multiplication_expr(integers[0], integers[1]);
        std::cout << "Evaluation: " << eval(&current_expr) << "\n\n";
        break;
    }
    case (7):
    {
        Division_expr current_expr = Division_expr(integers[0], integers[1]);
        std::cout << "Evaluation: " << eval(&current_expr) << "\n\n";
        break;
    }
    case (8):
    {
        Modulus_expr current_expr = Modulus_expr(integers[0], integers[1]);
        std::cout << "Evaluation: " << eval(&current_expr) << "\n\n";
        break;
    }
    case (9):
    {
        LessThan_expr current_expr = LessThan_expr(integers[0], integers[1]);
        std::cout << "Evaluation: " << eval(&current_expr) << "\n\n";
        break;
    }
    case (10):
    {
        LessThanOrEqualTo_expr current_expr = LessThanOrEqualTo_expr(integers[0], integers[1]);
        std::cout << "Evaluation: " << eval(&current_expr) << "\n\n";
        break;
    }
    case (11):
    {
        MoreThan_expr current_expr = MoreThan_expr(integers[0], integers[1]);
        std::cout << "Evaluation: " << eval(&current_expr) << "\n\n";
        break;
    }
    case (12):
    {
        MoreThanOrEqualTo_expr current_expr = MoreThanOrEqualTo_expr(integers[0], integers[1]);
        std::cout << "Evaluation: " << eval(&current_expr) << "\n\n";
        break;
    }
    case (14):
    {
        And_expr current_expr = And_expr(booleans[0], booleans[1]);
        std::cout << "Evaluation: " << eval(&current_expr) << "\n\n";
        break;
    }
    case (15):
    {
        Or_expr current_expr = Or_expr(booleans[0], booleans[1]);
        std::cout << "Evaluation: " << eval(&current_expr) << "\n\n";
        break;
    }
    case (16):
    {
        OrElse_expr current_expr = OrElse_expr(booleans[0], booleans[1]);
        std::cout << "Evaluation: " << eval(&current_expr) << "\n\n";
        break;
    }
    case (17):
    {
        AndThen_expr current_expr = AndThen_expr(booleans[0], booleans[1]);
        std::cout << "Evaluation: " << eval(&current_expr) << "\n\n";
        break;
    }
    case (18):
    {
        Not_expr current_expr = Not_expr(booleans[0]);
        std::cout << "Evaluation: " << eval(&current_expr) << "\n\n";
        break;
    }
    case (19):
    {

        expr *e1;
        expr *e2;

        if (booleans.size() == 2)
        {
            e1 = booleans[0];
            e2 = booleans[1];
        }
        else
        {
            e1 = integers[0];
            e2 = integers[1];
        }

        NotEqualTo_expr current_expr = NotEqualTo_expr(e1, e2);

        std::cout << "Evaluation: " << eval(&current_expr) << "\n\n";
        break;
    }
    case (20):
    {
        expr *e1;
        expr *e2;
        if (booleans.size() == 2)
        {
            e1 = booleans[0];
            e2 = booleans[1];
        }
        else
        {
            e1 = integers[0];
            e2 = integers[1];
        }

        EqualTo_expr current_expr = EqualTo_expr(e1, e2);

        std::cout << "Evaluation: " << eval(&current_expr) << "\n\n";
        break;
    }
    }
}