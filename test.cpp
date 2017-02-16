//Nathan Stackpole, 2017

#include <iostream>

#include "eval.hpp"
#include <limits>

int main()
{
    //Test Bool_expr constructor, eval
    Bool_expr bool_test = Bool_expr(true);
    std::cout << "Bool constructor test (true) :" << eval(&bool_test) << "\n\n";

    //Tests Not_expr constructor eval
    Not_expr not_test = Not_expr(&bool_test);
    std::cout << "Not (!) constructor test (true) :" << eval(&not_test) << "\n\n";

    //Test And_expr and AndThen_exprconstructor and eval
    And_expr and_test = And_expr(&bool_test, &not_test);
    std::cout << "And test (true, !true):" << eval(&and_test) << "\n";
    AndThen_expr and_then_test = AndThen_expr(&bool_test, &not_test);
    std::cout << "AndThen test (true, !true):" << eval(&and_then_test) << "\n\n";

    //Test Or_expr and OrElse_expr constructor and eval
    Or_expr or_test = Or_expr(&bool_test, &not_test);
    std::cout << "Or test (true, !true) :" << eval(&or_test) << "\n\n";
    OrElse_expr or_else_test = OrElse_expr(&bool_test, &not_test);
    std::cout << "OrElse test (true, !true) :" << eval(&or_else_test) << "\n\n";

    //Test Conditional_expr constructor and eval
    Conditional_expr conditional_test = Conditional_expr(&not_test, &and_test, &or_test);
    std::cout << "Conditional Test (true, false, true):" << eval(&conditional_test) << "\n\n";

    //EqualsTo, More than, less than, and Integer constructor and eval tests
    Integer_expr int_test_1 = Integer_expr(10);
    Integer_expr int_test_2 = Integer_expr(11);
    Integer_expr int_test_3 = Integer_expr(10);
    std::cout << "Integer constructor test 1 (10):" << eval(&int_test_1) << "\n";
    std::cout << "Integer constrcutor test 2 (11):" << eval(&int_test_2) << "\n";
    std::cout << "Integer constructor test 3 (10):" << eval(&int_test_3) << "\n\n";

    EqualTo_expr equal_test_1 = EqualTo_expr(&int_test_1, &int_test_2);
    EqualTo_expr equal_test_2 = EqualTo_expr(&int_test_1, &int_test_3);
    NotEqualTo_expr not_equal_test_1 = NotEqualTo_expr(&int_test_1, &int_test_2);
    NotEqualTo_expr not_equal_test_2 = NotEqualTo_expr(&int_test_1, &int_test_3);

    std::cout << "Equal test 1 (10,11):" << eval(&equal_test_1) << "\n";
    std::cout << "Equal test 2 (10,10):" << eval(&equal_test_2) << "\n";
    std::cout << "Not Equal test 1 (10,11):" << eval(&not_equal_test_1) << "\n";
    std::cout << "Not Equal test 2 (10,10):" << eval(&not_equal_test_2) << "\n\n";

    LessThan_expr lessthan_test1 = LessThan_expr(&int_test_1, &int_test_2);
    LessThan_expr lessthan_test2 = LessThan_expr(&int_test_2, &int_test_1);
    MoreThan_expr morethan_test1 = MoreThan_expr(&int_test_1, &int_test_2);
    MoreThan_expr morethan_test2 = MoreThan_expr(&int_test_2, &int_test_1);

    LessThanOrEqualTo_expr lessthan_equal_test1 = LessThanOrEqualTo_expr(&int_test_1, &int_test_2);
    LessThanOrEqualTo_expr lessthan_equal_test2 = LessThanOrEqualTo_expr(&int_test_2, &int_test_1);
    LessThanOrEqualTo_expr lessthan_equal_test3 = LessThanOrEqualTo_expr(&int_test_3, &int_test_1);
    MoreThanOrEqualTo_expr morethan_equal_test1 = MoreThanOrEqualTo_expr(&int_test_1, &int_test_2);
    MoreThanOrEqualTo_expr morethan_equal_test2 = MoreThanOrEqualTo_expr(&int_test_2, &int_test_1);
    MoreThanOrEqualTo_expr morethan_equal_test3 = MoreThanOrEqualTo_expr(&int_test_3, &int_test_1);

    std::cout << "Less than test (10,11): " << eval(&lessthan_test1) << "\n";
    std::cout << "Less than test (11,10): " << eval(&lessthan_test2) << "\n";
    std::cout << "More than test (10,11): " << eval(&morethan_test1) << "\n";
    std::cout << "More than test (11,10): " << eval(&morethan_test2) << "\n";

    std::cout << "Less than or equals test (10,11): " << eval(&lessthan_equal_test1) << "\n";
    std::cout << "Less than or equals test (11,10): " << eval(&lessthan_equal_test2) << "\n";
    std::cout << "Less than or equals test (10,10): " << eval(&lessthan_equal_test3) << "\n";
    std::cout << "More than or equals test (10,11): " << eval(&morethan_equal_test1) << "\n";
    std::cout << "More than or equals test (11,10): " << eval(&morethan_equal_test2) << "\n";
    std::cout << "More than or equals test (10,10): " << eval(&morethan_equal_test3) << "\n\n";

    //Arithmetic tests
    Negation_expr negate_test = Negation_expr(&int_test_1);
    std::cout << "Negation test (10): " << eval(&negate_test) << "\n\n";

    Addition_expr addition_test = Addition_expr(&int_test_1, &int_test_2);
    std::cout << "Addition test (10,11): " << eval(&addition_test) << "\n\n";

    Subtraction_expr subtraction_test = Subtraction_expr(&int_test_1, &int_test_2);
    std::cout << "Subtraction test (10,11): " << eval(&subtraction_test) << "\n\n";

    Multiplication_expr multiplication_test = Multiplication_expr(&int_test_1, &int_test_2);
    std::cout << "Multiplication test (10,11): " << eval(&multiplication_test) << "\n\n";

    Integer_expr int_test_4 = Integer_expr(20);
    Division_expr division_test = Division_expr(&int_test_4, &int_test_1);
    std::cout << "Division test (20,10): " << eval(&division_test) << "\n\n";

    Modulus_expr modulus_test = Modulus_expr(&int_test_4, &int_test_1);
    std::cout << "Modulus test (20,10): " << eval(&modulus_test) << "\n\n";

    //Type checking tests
    //Replace an integer variable or boolean variable below with a boolean variable or integer variable respectively to make the program abort
    //If all types are right then the program should run to completeion, if not an assertion should be abort the program.
    And_expr and_type_check_test = And_expr(&not_test, &and_test);
    AndThen_expr and_then_check_test = AndThen_expr(&not_test, &and_test);

    Not_expr not_type_check_test = Not_expr(&not_test);

    Or_expr or_type_check_test = Or_expr(&not_test, &and_test);
    OrElse_expr or_else_type_check_test = OrElse_expr(&not_test, &and_test);

    Conditional_expr conditional_check_test = Conditional_expr(&not_test, &or_test, &and_test);

    LessThan_expr lessthan_check_test = LessThan_expr(&int_test_1, &int_test_2);
    LessThanOrEqualTo_expr lessthan_equal_check_test = LessThanOrEqualTo_expr(&int_test_1, &int_test_2);

    MoreThan_expr morethan_check_test = MoreThan_expr(&int_test_1, &int_test_2);
    MoreThanOrEqualTo_expr morethan_equal_check_test = MoreThanOrEqualTo_expr(&int_test_1, &int_test_2);

    EqualTo_expr equals_type_check_test = EqualTo_expr(&not_test, &not_test);
    NotEqualTo_expr not_equals_type_check_test = NotEqualTo_expr(&not_test, &not_test);

    Negation_expr negate_check_test = Negation_expr(&int_test_1);

    Addition_expr addition_check_test = Addition_expr(&int_test_1, &int_test_2);

    Subtraction_expr subtraction_check_test = Subtraction_expr(&int_test_1, &int_test_2);

    Multiplication_expr multiplication_check_test = Multiplication_expr(&int_test_1, &int_test_2);

    Division_expr division_check_test = Division_expr(&int_test_4, &int_test_1);

    Modulus_expr modulus_check_test = Modulus_expr(&int_test_4, &int_test_1);

    return 1;
}