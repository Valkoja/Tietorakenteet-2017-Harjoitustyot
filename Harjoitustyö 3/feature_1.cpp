#include "main.h"

void feature_1()
{
    int listIndex = -1;
    int listLength = 0;
    int listTarget = 0;

    Utilities util;
    Statistic stat;
    std::vector<int> listVector;

    // Listan pituus ja haettava avain
    listLength = util.askLength(listVector);
    listTarget = util.askTarget(listLength);

    // Luodaan aineisto, käydään luvut läpi
    util.populateWithOdds(listVector, listLength);
    listIndex = sequentialSearch(stat, listVector, listTarget);

    // Löytyikö haettava luku
    if (listIndex != -1)
    {
        std::cout << std::endl;
        std::cout << "Luku loytyi listan paikalta " << listIndex << std::endl;
    }
    else
    {
        std::cout << std::endl;
        std::cout << "Lukua ei loytynyt" << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Paina enter palataksesi paavalikkoon";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
