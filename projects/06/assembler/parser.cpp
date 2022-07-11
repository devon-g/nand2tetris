#include "parser.h"

Parser::Parser(std::string filename)
{
    this->input_file.open(filename);
    this->has_more_commands = !this->input_file.eof();
}

Parser::~Parser()
{
    this->input_file.close();
}

bool Parser::hasMoreCommands()
{
    return this->has_more_commands;
}

std::string Parser::getCurrentCommand()
{
    return this->current_command;
}

void Parser::advance()
{
    // Get next line from file
    std::string current_line;

    // Ignore lines that are empty or are comments
    do
    {
        this->has_more_commands = !std::getline(this->input_file, current_line).eof();
        current_line.erase(remove_if(current_line.begin(), current_line.end(), isspace), current_line.end());
    }
    while (this->has_more_commands && (isspace(current_line.front()) || current_line.front() == '/'));

    // Strip inline comments
    size_t comment_pos = current_line.find('/');
    if (comment_pos != std::string::npos)
        current_line = current_line.substr(0, comment_pos);

    this->current_command = current_line;
}

void Parser::reset()
{
    this->input_file.clear();
    this->input_file.seekg(0);
    this->current_command = "";
    this->has_more_commands = !this->input_file.eof();
}

COMMAND_TYPE Parser::commandType()
{
    COMMAND_TYPE command_type;

    char first = '\0';
    
    if (!this->current_command.empty())
        first = this->current_command.front();

    if (first == '@')
        command_type = COMMAND_TYPE::A_COMMAND;
    else if (first == '(')
        command_type = COMMAND_TYPE::L_COMMAND;
    else if (first == '\0')
        command_type = COMMAND_TYPE::INVALID_COMMAND;
    else
        command_type = COMMAND_TYPE::C_COMMAND;

    return command_type;
}

std::string Parser::symbol()
{
    // A_COMMAND: @Xxx
    // Extract contents of A_COMMAND excluding the starting @
    std::string symbol = this->current_command.substr(1, this->current_command.size() - 1);
    return symbol;
}

std::string Parser::dest()
{
    // C_COMMAND: dest=comp;jump
    // Find index of = in C_COMMAND if present
    size_t equal_pos = this->current_command.find('=');
    // Extract dest from beginning of C_COMMAND to =
    std::string dest = "";
    // If = symbol present then 
    if (equal_pos != std::string::npos)
        dest = this->current_command.substr(0, equal_pos);

    // Either return a destination or an empty string
    return dest;
}

std::string Parser::comp()
{
    // C_COMMAND: dest=comp;jump
    // = index: 4
    // ; index: 9
    // C_COMMAND size: 14

    // Find index of = in C_COMMAND if present
    size_t equal_pos = this->current_command.find('=');
    // Find index of ; in C_COMMAND if present
    size_t semicolon_pos = this->current_command.find(';');

    // Extract comp from C_COMMAND
    std::string comp = "";
    // If = present and ; not present
    if (equal_pos != std::string::npos && semicolon_pos == std::string::npos)
        comp = this->current_command.substr(equal_pos + 1, this->current_command.size() - 1 - equal_pos);
    // If = present and ; present
    if (equal_pos != std::string::npos && semicolon_pos != std::string::npos)
        comp = this->current_command.substr(equal_pos + 1, semicolon_pos - 1 - equal_pos);
    // If = not present and ; present
    if (equal_pos == std::string::npos && semicolon_pos != std::string::npos)
        comp = this->current_command.substr(0, semicolon_pos);
    // Either return a computation or an empty string
    return comp;
}

std::string Parser::jump()
{
    // C_COMMAND: dest=comp;jump
    // Find index of ; in C_COMMAND if present
    size_t semicolon_pos = this->current_command.find(';');

    // Extract jump from C_COMMAND
    std::string jump = "";
    // If ; present
    if (semicolon_pos != std::string::npos)
        jump = this->current_command.substr(semicolon_pos + 1, this->current_command.size() - 1 - semicolon_pos);

    // Either return a jump or an empty string
    return jump;
}