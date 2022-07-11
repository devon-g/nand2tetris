#include "code.h"

Code::Code()
{
    // Destinations
    destinations[""] = 0b000;
    destinations["M"] = 0b001;
    destinations["D"] = 0b010;
    destinations["MD"] = 0b011;
    destinations["A"] = 0b100;
    destinations["AM"] = 0b101;
    destinations["AD"] = 0b110;
    destinations["AMD"] = 0b111;

    // Computations
    computations["0"] = 0b0101010;
    computations["1"] = 0b0111111;
    computations["-1"] = 0b0111010;
    computations["D"] = 0b0001100;
    computations["A"] = 0b0110000;
    computations["M"] = 0b1110000;
    computations["!D"] = 0b0001101;
    computations["!A"] = 0b0110001;
    computations["!M"] = 0b1110001;
    computations["-D"] = 0b0001111;
    computations["-A"] = 0b0110011;
    computations["-M"] = 0b1110011;
    computations["D+1"] = 0b0011111;
    computations["A+1"] = 0b0110111;
    computations["M+1"] = 0b1110111;
    computations["D-1"] = 0b0001110;
    computations["A-1"] = 0b0110010;
    computations["M-1"] = 0b1110010;
    computations["D+A"] = 0b0000010;
    computations["D+M"] = 0b1000010;
    computations["D-A"] = 0b0010011;
    computations["D-M"] = 0b1010011;
    computations["A-D"] = 0b0000111;
    computations["M-D"] = 0b1000111;
    computations["D&A"] = 0b0000000;
    computations["D&M"] = 0b1000000;
    computations["D|A"] = 0b0010101;
    computations["D|M"] = 0b1010101;

    // Jumps
    jumps[""] = 0b000;
    jumps["JGT"] = 0b001;
    jumps["JEQ"] = 0b010;
    jumps["JGE"] = 0b011;
    jumps["JLT"] = 0b100;
    jumps["JNE"] = 0b101;
    jumps["JLE"] = 0b110;
    jumps["JMP"] = 0b111;
}

std::bitset<3> Code::dest(std::string dest_mnemonic)
{
    return this->destinations[dest_mnemonic];
}

std::bitset<7> Code::comp(std::string comp_mnemonic)
{
    return this->computations[comp_mnemonic];
}

std::bitset<3> Code::jump(std::string jump_mnemonic)
{
    return this->jumps[jump_mnemonic];
}