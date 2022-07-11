#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <string>
#include <algorithm>

enum COMMAND_TYPE{A_COMMAND, C_COMMAND, L_COMMAND, INVALID_COMMAND};

/**
 * @brief Break each assembly command into its underlying components
 * Encapsulates access to the input code. Reads an assembly language command,
 * parses it, and provides convenient access to the command's components (fields
 * and symbols). In addition, removes all white space and comments.
 */
class Parser
{
public:
    /**
     * @brief Opens the input file/stream and gets ready to parse it.
     * 
     * @param filename - Name of file to open (prog.asm)
     */
    Parser(std::string filename);
    ~Parser();
    
    /**
     * @brief Are there more commands in the input?
     * 
     * @return true 
     * @return false 
     */
    bool hasMoreCommands();

    /**
     * @brief Reads the next command from the input and makes it the current
     * command. Should be called only if hasMoreCommands() is true.
     * Initially there is no current command.
     */
    void advance();

    /**
     * @brief Returns the type of current command
     * 
     * @return COMMAND_TYPE
     * - A_COMMAND for @Xxx where Xxx is either a symbol or a decimal number
     * - C_COMMAND for dest=comp;jump
     * - L_COMMAND (actually pseudo-command) for (Xxx) where Xxx is a symbol.
     */
    COMMAND_TYPE commandType();

    /**
     * @brief Should be called only when commandType() is A_COMMAND or
     * L_COMMAND.
     * 
     * @return std::string - The symbol or decimal Xxx of the current command
     * @Xxx or (Xxxx).
     */
    std::string symbol();

    /**
     * @brief Should be called only when commandType() is C_COMMAND.
     * 
     * @return std::string - The dest mnemonic in the current C-command
     * (8 possibilities).
     */
    std::string dest();

    /**
     * @brief Should be called only when commandType() is C_COMMAND.
     * 
     * @return std::string - The comp mnemonic in the current C-command
     * (28 possibilities).
     */
    std::string comp();

    /**
     * @brief Should only be called when commandType() is C_COMMAND.
     * 
     * @return std::string - The jump mnemonic in the current C-command
     * (8 possibilities).
     */
    std::string jump();

private:
    std::ifstream input_file;
    std::string current_command;
    bool has_more_commands;
};

#endif