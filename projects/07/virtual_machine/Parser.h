#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <string>
#include <COMMAND_TYPE.h>

class Parser
{
public:
    Parser(std::ifstream input_file);

    /**
     * @brief Are there more lines in the input?
     * 
     * @return true - Next line is present
     * @return false - Next line is not present
     */
    bool hasMoreLines();

    /**
     * @brief Reads the next command from the input and makes it the current
     * command.
     * This routine should be called only if hasMoreLines is true.
     * Initially there is no current command.
     */
    void advance();

    /**
     * @brief Determines the command type of the current input line.
     * 
     * @return COMMAND_TYPE - Current command type.
     */
    COMMAND_TYPE commandType();

    /**
     * @brief Extracts the first argument from the current command.
     * Should not be called if the current command is C_RETURN.
     * 
     * @return std::string - add/sub/neg/eq/gt/lt/and/or/not
     */
    std::string arg1();

    /**
     * @brief Extracts the second argument from the current command.
     * Should only be called if the current command is C_PUSH, C_POP,
     * C_FUNCTION, or C_CALL.
     * 
     * @return int
     */
    int arg2();
};


#endif