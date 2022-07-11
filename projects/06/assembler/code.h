#ifndef CODE_H
#define CODE_H

#include <bitset>
#include <map>

/**
 * @brief Translates Hack assembly language mnemonics into binary codes.
 */
class Code
{
public:
    Code();

    /**
     * @brief Converts destination mnemonic to binary code.
     * 
     * @param dest_mnemonic - Destination mnemonic
     * @return std::bitset<3> - Binary translation
     */
    std::bitset<3> dest(std::string dest_mnemonic);

    /**
     * @brief Converts computation mnemonic to binary code.
     * 
     * @param comp_mnemonic - Computation mnemonic
     * @return std::bitset<7> - Binary translation
     */
    std::bitset<7> comp(std::string comp_mnemonic);

    /**
     * @brief Converts jump mnemonic to binary code.
     * 
     * @param jump_mnemonic - Jump mnemonic
     * @return std::bitset<3> - Binary translation
     */
    std::bitset<3> jump(std::string jump_mnemonic);

private:
    std::map<std::string,std::bitset<3>> destinations;
    std::map<std::string,std::bitset<7>> computations;
    std::map<std::string,std::bitset<3>> jumps;
};

#endif