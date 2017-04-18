//Nathan Stackpole, 2017

#include "lexer.hpp"
#include "AST.hpp"
#include "decl.hpp"
#include "statement.hpp"
#include "symbol.hpp"

#include <iostream>
#include <vector>
#include <unordered_map>

#ifndef PARSE_HPP
#define PARSE_HPP

struct stmt;
struct decl;


class parser
{
  std::unordered_map<int, std::string> token_names;
  std::vector<token *> line;
  int index;
  token* match(token_kind);
  token* match_if(token_kind);
  token* consume();
  int look_ahead();
  bool end_of_file() const;
  
public:
  parser(std::vector<token *>);
  expr* expression();
  expr* additive_expression();
  expr* multiplicative_expression();
  expr* unary_expression();
  expr* primary_expression();
  expr* id_expression();
  expr* parse();
  expr* ordering_expression();
  expr* equality_expression();
  expr* logical_and_expression();
  expr* logical_or_expression();
  expr* conditional_expression();

  symbol* identifier();
};

#endif