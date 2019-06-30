#include "main.h"

int main()
{
    std::cout << "Harjoitustyo 1 - Valkoja Iiro" << std::endl;
    std::cout << "Symbolien tasapainotusohjelma" << std::endl;
    std::cout << "-----------------------------" << std::endl;

    SymbolMatcher matcher;
    matcher.runLoop();

    return 0;
}
