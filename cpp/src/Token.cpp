#include <algorithm>
#include <string>

#include <Token.hpp>

using std::string;

Token::Token(string value, TokenType type) {
  this->value = value;
  this->type = type;
}

Token Token::tokenize(string token) {
  if (std::find(operators.begin(), operators.end(), token) != operators.end()) {
    return Token(token, OPERATOR);
  } else {
    return Token(token, ERROR);
  }
}

std::ostream& operator << ( std::ostream& outs, const Token & token )
{
  return outs << token.value;
}
