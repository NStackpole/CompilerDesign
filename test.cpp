//Nathan Stackpole

#include "Compile.hpp"
#include <iostream>

int main()
{
    //Test Bool_expr constructor, eval
    Bool_expr bool_test = Bool_expr(true);
    std::cout<<"bool_test:"<<bool_test.eval()<<"\n";

    //Tests Not_expr constructor eval
    Not_expr not_test = Not_expr(bool_test);
    std::cout<<"not_test:"<<not_test.eval()<<"\n";

    //Test And_expr constructor and eval
    And_expr and_test = And_expr(bool_test, not_test);
    std::cout<<"and_test:"<<and_test.eval()<<"\n";

    //Test Or_expr constructor and eval
    Or_expr or_test = Or_expr(bool_test, not_test);
    std::cout<<"or_test:"<<or_test.eval()<<"\n";

    //Test Conditional_expr constructor and eval
    Conditional_expr conditional_test = Conditional_expr(bool_test, and_test, or_test);
    std::cout<<"conditional_test:"<<conditional_test.eval()<<"\n";

    //EqualsTo and Integer constructor and eval tests
    Integer_expr int_test_1 = Integer_expr(10);
    Integer_expr int_test_2 = Integer_expr(11);
    Integer_expr int_test_3 = Integer_expr(10);
    std::cout<<"Integer 1 test:"<<int_test_1.eval()<<"\n";
    std::cout<<"Integer 2 test:"<<int_test_2.eval()<<"\n";
    std::cout<<"Integer 3 test:"<<int_test_3.eval()<<"\n";
    EqualTo_expr equal_test_1 = EqualTo_expr(int_test_1, int_test_2);
    EqualTo_expr equal_test_2 = EqualTo_expr(int_test_1, int_test_3);
    std::cout<<"Equal test 1 (10,11):"<<equal_test_1.eval()<<"\n";
    std::cout<<"Equal test 2 (10,10):"<<equal_test_2.eval()<<"\n";


    

    return 1;
}