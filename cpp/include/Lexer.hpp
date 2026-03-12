#pragma once
#include <string>
#include <vector>
#include <Token.hpp>

using std::string;
using std::vector;

class Lexer {
public:
  std::string input;
  vector<Token> tokens;

  Lexer(string);
  void get_tokens();
  void parse_tokens(string);
};

