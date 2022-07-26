#include "SymbolTable.h"

SymbolTable::SymbolTable()
{
    // Initialize built-in symbols
    this->table["SP"] = 0x0000;
    this->table["LCL"] = 0x0001;
    this->table["ARG"] = 0x0002;
    this->table["THIS"] = 0x0003;
    this->table["THAT"] = 0x0004;
    this->table["R0"] = 0x0000;
    this->table["R1"] = 0x0001;
    this->table["R2"] = 0x0002;
    this->table["R3"] = 0x0003;
    this->table["R4"] = 0x0004;
    this->table["R5"] = 0x0005;
    this->table["R6"] = 0x0006;
    this->table["R7"] = 0x0007;
    this->table["R8"] = 0x0008;
    this->table["R9"] = 0x0009;
    this->table["R10"] = 0x000A;
    this->table["R11"] = 0x000B;
    this->table["R12"] = 0x000C;
    this->table["R13"] = 0x000D;
    this->table["R14"] = 0x000E;
    this->table["R15"] = 0x000F;
    this->table["SCREEN"] = 0x4000;
    this->table["KBD"] = 0x6000;
}

void SymbolTable::addEntry(std::string symbol, int address)
{
    this->table[symbol] = address;
}

bool SymbolTable::contains(std::string symbol)
{
    return this->table.contains(symbol);
}

int SymbolTable::getAddress(std::string symbol)
{
    return this->table[symbol];
}
