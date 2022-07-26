#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <string>
#include <unordered_map>

class SymbolTable
{
public:
    SymbolTable();

    /**
     * @brief Adds a symbol/address pair to the table.
     * 
     * @param symbol - Symbol to add to table
     * @param address - Address symbol should refer to
     */
    void addEntry(std::string symbol, int address);

    /**
     * @brief Determines if given symbol is in the table
     * 
     * @param symbol - Symbol to check table for
     * @return true - Symbol is present
     * @return false - Symbol is not present
     */
    bool contains(std::string symbol);

    /**
     * @brief Find address associated with given symbol
     * 
     * @param symbol - Symbol to find address for
     * @return int - Address of given symbol
     */
    int getAddress(std::string symbol);

private:
    std::unordered_map<std::string, int> table;
};

#endif