# Compiler Design Repository
This repository holds work done for my Compiler Design class. Currently that includes a compiler being made for a language designed in the class. Currently the "compiler" is really just a C++ library representation of the abstract syntax tree for the language.

This language currently:
* Can evaluate the following expressions : Not, And, Or, Xor, Conditional, <, >, ==, !=, <=, >=, and then (&&), or else (||), division, modulus, negation, multiplication, subtraction, addition.
* Has a very basic type system: integer and boolean.
* Checks the types of expressions to make sure the expression is well formed. If it is not the program will abort.

TODO:
* Test type checking on all expressions
