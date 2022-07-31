#ifndef CODEWRITER_H
#define CODEWRITER_H

#include "COMMAND_TYPE.h"
#include <fstream>
#include <string>

class CodeWriter {
public:
  /**
   * @brief Opens an output file / stream and gets ready to write into it.
   *
   * @param output_file
   */
  CodeWriter(std::string output_file);

  /**
   * @brief Writes to the output file the assembly code that implements the
   * given arithmetic-logical command.
   *
   * @param command
   */
  void writeArithmetic(std::string command);

  /**
   * @brief Writes to the output file the assembly code that implements the
   * given push or pop command.
   *
   * @param command - C_PUSH or C_POP command type
   * @param segment
   * @param index
   */
  void writePushPop(COMMAND_TYPE command, std::string segment, int index);

  /**
   * @brief Closes the output file / stream.
   *
   */
  void close();
};

#endif
