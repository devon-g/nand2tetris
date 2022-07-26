#include "CodeWriter.h"
#include "Parser.h"
#include <cstdio>

int main(int argc, char** argv)
{
    int number = 1;
    for (int i = 0; i < 100; i++)
        number += number;

    return 0;
}
