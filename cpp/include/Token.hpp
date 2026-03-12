#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

enum TokenType {
  KEYWORD,
  OPERATOR,
  REGISTER,
  LABEL,
  ADDR_MODE,
  NUMBER,
  COMMA,
  COMMENT,
  ERROR
};

class Token {
public:
  string value;
  TokenType type;

  Token(string, TokenType);


  static inline vector<string> operators = {
    "load",
    "store",
    "add",
    "sub",
    "mul",
    "div"
  }; 

  static Token tokenize(string);
};
