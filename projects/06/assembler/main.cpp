#include "Parser.h"
#include "Code.h"
#include "SymbolTable.h"

int main(int argc, char** argv)
{
    // Open output file
    std::ofstream output_file;
    
    std::string output_filepath = argv[1];
    // Output file in same directory as input file but replace extension with
    // .hack
    output_filepath = output_filepath.substr(0, output_filepath.find_last_of('.'));
    output_file.open(output_filepath + "_.hack");

    Parser p(argv[1]);
    Code c;
    SymbolTable s;

    // Define variables for command components
    // Symbols
    std::string symbol;
    std::string label;

    // Bits
    uint16_t symbol_bits;
    uint16_t dest_bits;
    uint16_t comp_bits;
    uint16_t jump_bits;
    std::bitset<16> command_bits;

    // First pass: extract symbols and store them in the symbol table
    int current_program_line = 0;
    while (p.hasMoreCommands())
    {
        p.advance();

        // Add symbols from L_COMMANDS to symbol table
        if (p.commandType() == COMMAND_TYPE::L_COMMAND)
        {
            // Get label: (Xxx)
            label = p.getCurrentCommand();
            // Save symbol Xxx
            symbol = label.substr(1, label.size() - 2);

            // If symbol is not already in symbol table we add it
            if (!s.contains(symbol))
                s.addEntry(symbol, current_program_line);
        }
        // Increment program line ignoring L_COMMANDs and INVALID_COMMANDS
        else if (p.commandType() != COMMAND_TYPE::INVALID_COMMAND)
            current_program_line++;
    }

    // Reset the parser for second pass.
    p.reset();

    // Second pass: parse and convert every command to machine language
    int current_symbol_address = 0x0010;
    while (p.hasMoreCommands())
    {
        p.advance();
        // Determine action based on command type
        switch (p.commandType())
        {
            case COMMAND_TYPE::A_COMMAND:
                // Get symbol mnemonic and check if it is a number
                symbol = p.symbol();                
                // If the A_COMMAND symbol is numeric, convert it directly to
                // bits
                if (symbol.find_first_not_of("1234567890") == std::string::npos)
                    symbol_bits = static_cast<uint16_t>(std::stoi(symbol));
                else // Look up symbol in symbol table and then convert to bits
                {
                    // If symbol is not present in symbol table, add it at next
                    // available memory address
                    if (!s.contains(symbol))
                    {
                        s.addEntry(symbol, current_symbol_address);
                        current_symbol_address++;
                    }
                    symbol_bits = static_cast<uint16_t>(s.getAddress(symbol));
                }
                // Build command bitset for A_COMMAND
                command_bits = symbol_bits;
                command_bits[15] = 0;
                // Add A_COMMAND to output file
                output_file << command_bits << std::endl;
                break;
            case COMMAND_TYPE::C_COMMAND:
                // Take each set of command bits and shift them to their correct
                // place in the final command bitset.
                jump_bits = static_cast<uint16_t>(c.jump(p.jump()).to_ulong());
                dest_bits = static_cast<uint16_t>(c.dest(p.dest()).to_ulong()) << 3;
                comp_bits = static_cast<uint16_t>(c.comp(p.comp()).to_ulong()) << 6;
                // Build command bitset for C_COMMAND
                command_bits = comp_bits | dest_bits | jump_bits;
                command_bits[15] = command_bits[14] = command_bits[13] = 1;
                // ADD C_COMMAND to output file
                output_file << command_bits << std::endl;
                break;
            default: break;
        }
    }

    output_file.close();

    return 0;
}
