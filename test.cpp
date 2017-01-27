//Nathan Stackpole

#include "Compile.hpp"
#include <iostream>

int main()
{
    std::cout<<"Hello\n";

    Bool_expr bool_test = Bool_expr(false);
    std::cout<<bool_test.eval()<<"\n";
    bool_test.value = true;
    std::cout<<bool_test.eval()<<"\n";

    Not_expr not_test = Not_expr(bool_test);
    std::cout<<not_test.eval()<<"\n";

    And_expr and_test = And_expr(bool_test, not_test);
    std::cout<<and_test.eval()<<"\n";

    Or_expr or_test = Or_expr(bool_test, not_test);
    std::cout<<or_test.eval()<<"\n";

    return 1;
}