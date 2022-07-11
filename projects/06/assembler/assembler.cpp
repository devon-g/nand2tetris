#include "parser.h"
#include "code.h"

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

    // Define variables for command components
    // Symbols
    std::string symbol;

    // Bits
    uint16_t symbol_bits;
    uint16_t dest_bits;
    uint16_t comp_bits;
    uint16_t jump_bits;
    std::bitset<16> command_bits;

    // Parse and convert every command to machine language
    while (p.hasMoreCommands())
    {
        p.advance();
        // Determine action based on command type
        switch (p.commandType())
        {
            case COMMAND_TYPE::A_COMMAND:
                // Get symbol mnemonic and check if it is a number
                symbol = p.symbol();                
                if (symbol.find_first_not_of("1234567890") == std::string::npos)
                    symbol_bits = static_cast<uint16_t>(std::stoi(symbol));
                // Build command bitset for A_COMMAND
                command_bits = symbol_bits;
                command_bits[15] = 0;
                // TODO: Later we will handle symbols
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
            case COMMAND_TYPE::L_COMMAND: break;
            default: break;
        }
    }

    output_file.close();

    return 0;
}