//Nathan Stackpole

#include <iostream>

#include "AST.hpp"
#include "eval.hpp"
#include "type.hpp"

int main()
{
    Context cxt;

    //Test Bool_expr constructor, eval
    Bool_expr bool_test = Bool_expr(true);
    std::cout << "bool_test:" << eval(&bool_test) << "\n";

    //Tests Not_expr constructor eval
    Not_expr not_test = Not_expr(&bool_test);
    std::cout << "not_test:" << eval(&not_test) << "\n";

    //Test And_expr constructor and eval
    And_expr and_test = And_expr(&bool_test, &not_test);
    std::cout << "and_test:" << eval(&and_test) << "\n";

    //Test Or_expr constructor and eval
    Or_expr or_test = Or_expr(&bool_test, &not_test);
    std::cout << "or_test:" << eval(&or_test) << "\n";

    //Test Conditional_expr constructor and eval
    Conditional_expr conditional_test = Conditional_expr(&bool_test, &and_test, &or_test);
    std::cout << "conditional_test:" << eval(&conditional_test) << "\n";

    //EqualsTo, More than, less than, and Integer constructor and eval tests
    Integer_expr int_test_1 = Integer_expr(10);
    Integer_expr int_test_2 = Integer_expr(11);
    Integer_expr int_test_3 = Integer_expr(10);
    std::cout << "Integer 1 test:" << eval(&int_test_1) << "\n";
    std::cout << "Integer 2 test:" << eval(&int_test_2) << "\n";
    std::cout << "Integer 3 test:" << eval(&int_test_3) << "\n";

    EqualTo_expr equal_test_1 = EqualTo_expr(&int_test_1, &int_test_2);
    EqualTo_expr equal_test_2 = EqualTo_expr(&int_test_1, &int_test_3);

    std::cout << "Equal test 1 (10,11):" << eval(&equal_test_1) << "\n";
    std::cout << "Equal test 2 (10,10):" << eval(&equal_test_2) << "\n";

    LessThan_expr lessthan_test1 = LessThan_expr(&int_test_1, &int_test_2);
    LessThan_expr lessthan_test2 = LessThan_expr(&int_test_2, &int_test_1);
    MoreThan_expr morethan_test1 = MoreThan_expr(&int_test_1, &int_test_2);
    MoreThan_expr morethan_test2 = MoreThan_expr(&int_test_2, &int_test_1);

    std::cout << "lessthan_test1(10,11): " << eval(&lessthan_test1) << "\n";
    std::cout << "lessthan_test1(11,10): " << eval(&lessthan_test2) << "\n";
    std::cout << "morethan_test1(10,11): " << eval(&morethan_test1) << "\n";
    std::cout << "morethan_test2(11,10): " << eval(&morethan_test2) << "\n";

    //Type checking tests
    //Replace an integer variable or boolean variable below with a boolean variable or integer variable respectively to make the program abort
    And_expr and_type_check_test = And_expr(&not_test, &and_test);

    Not_expr not_type_check_test = Not_expr(&not_test);

    Or_expr or_type_check_test = Or_expr(&not_test, &and_test);

    Conditional_expr conditional_check_test = Conditional_expr(&not_test, &or_test, &and_test);

    LessThan_expr lessthan_check_test = LessThan_expr(&int_test_1, &int_test_2);

    MoreThan_expr morethan_check_test = MoreThan_expr(&int_test_1, &int_test_2);

    EqualTo_expr equals_type_check_test = EqualTo_expr(&not_test, &not_test);

    return 1;
}