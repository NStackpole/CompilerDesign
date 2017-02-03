//Nathan Stackpole

#include "AST.hpp"
#include <iostream>
#include "eval.hpp"
int main()
{
    
    //Test Bool_expr constructor, eval
    Bool_expr bool_test = Bool_expr(true);
    std::cout<<"bool_test:"<<eval(&bool_test)<<"\n";

    //Tests Not_expr constructor eval
    Not_expr not_test = Not_expr(&bool_test);
    std::cout<<"not_test:"<<eval(&not_test)<<"\n";

    //Test And_expr constructor and eval
    And_expr and_test = And_expr(&bool_test, &not_test);
    std::cout<<"and_test:"<<eval(&and_test)<<"\n";

    //Test Or_expr constructor and eval
    Or_expr or_test = Or_expr(&bool_test, &not_test);
    std::cout<<"or_test:"<<eval(&or_test)<<"\n";

    //Test Conditional_expr constructor and eval
    Conditional_expr conditional_test = Conditional_expr(&bool_test, &and_test, &or_test);
    std::cout<<"conditional_test:"<<eval(&conditional_test)<<"\n";

    //EqualsTo and Integer constructor and eval tests
    Integer_expr int_test_1 = Integer_expr(10);
    Integer_expr int_test_2 = Integer_expr(11);
    Integer_expr int_test_3 = Integer_expr(10);
    std::cout<<"Integer 1 test:"<<eval(&int_test_1)<<"\n";
    std::cout<<"Integer 2 test:"<<eval(&int_test_2)<<"\n";
    std::cout<<"Integer 3 test:"<<eval(&int_test_3)<<"\n";
    EqualTo_expr equal_test_1 = EqualTo_expr(&int_test_1, &int_test_2);
    EqualTo_expr equal_test_2 = EqualTo_expr(&int_test_1, &int_test_3);
    std::cout<<"Equal test 1 (10,11):"<<eval(&equal_test_1)<<"\n";
    std::cout<<"Equal test 2 (10,10):"<<eval(&equal_test_2)<<"\n";
 

    return 1;
}