#include <iostream> 
#include <fstream>
#include <string>
#include <sstream>

#include <Lexer.hpp>

int main() {
  std::cout << "Hello world!" << std::endl;
  std::ifstream source_file ("../../docs/example-file-simple.k91");

  std::string line;
  std::stringstream input;

  // Open file and read the contents
  if (source_file.is_open()) {
    while (getline(source_file, line)) {
      input << line << "\n";
    }
  }

  source_file.close();

  Lexer lex = Lexer(input.str());

  lex.get_tokens();
  return 0;
}
