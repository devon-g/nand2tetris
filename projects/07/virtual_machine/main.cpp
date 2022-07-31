#include "CodeWriter.h"
#include "Parser.h"
#include <cstdio>

int main(int argc, char **argv) {
  std::string input_file = argv[1];
  // Extract path of input file and change file extension from .vm to .asm
  std::string output_file =
      input_file.substr(0, input_file.find_last_of('.')).append("_.asm");

  printf("Input: %s\nOutput %s\n", input_file.c_str(), output_file.c_str());
  //  Parser p("a");
  //  CodeWriter cw("b");

  return 0;
}
