//Nathan Stackpole, 2017

#include "decl.hpp"
#include "scope.hpp"
#include "statement.hpp"
#include "../lexer/lexer.hpp"
#include "../AST/AST.hpp"
#include "../lexer/symbol.hpp"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>

#ifndef PARSE_HPP
#define PARSE_HPP

class parser
{
  int index;
  symbol_table *symbols;
  std::unordered_map<int, std::string> token_names;
  std::vector<token *> line;
  std::stack<scope *> scope_stack;
  expr *statement_seq();
  token *match(token_kind);
  token *match_if(token_kind);
  token *require(token_kind);
  token *consume();
  int look_ahead();
  bool end_of_file() const;

public:
  parser(std::vector<token *> &, symbol_table *, std::stack<scope *>);
  expr *expression();
  expr *additive_expression();
  expr *multiplicative_expression();
  expr *unary_expression();
  expr *primary_expression();
  expr *id_expression();
  expr *parse();
  expr *ordering_expression();
  expr *equality_expression();
  expr *logical_and_expression();
  expr *logical_or_expression();
  expr *conditional_expression();

  expr *stmt();
  decl_statement *declaration_statement();
  expr_statement *expression_statement();

  decl *declaration();
  decl *variable_declaration();

  type *type_specifier();

  symbol *identifier();
};

#endif