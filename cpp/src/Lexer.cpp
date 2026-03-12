#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <Lexer.hpp>
#include <Token.hpp>

using std::string;
using std::stringstream;
using std::vector;

Lexer::Lexer(string input) {
  this->input = input;
  this->tokens = {};
}

void Lexer::get_tokens() {
  stringstream ss(this->input);
  string line;
  string word;
  char delim = ' ';

  std::cout << "Starting to get tokens :) " << ss.str() << std::endl;

  // Lines in input file
  while (getline(ss, line)) {
    stringstream ss_line(line);

    bool comment = false;

    // Words (tokens separated by whitespace) in line
    while (getline(ss_line, word, delim)) {
      // Skip comments
      if (word == ";") {
        comment = true;
      }

      if (comment) {
        continue;
      }

      std::cout << word << std::endl;
      this->tokens.push_back(Token::tokenize(word));
    }

    comment = false;
  }

  for (Token token : tokens) {
    std::cout << token.value << std::endl;
  }
}

void Lexer::parse_tokens(string token) {}
