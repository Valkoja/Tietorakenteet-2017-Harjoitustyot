#include "main.h"

void feature_4()
{
    int listPrints = 0;
    int listLength = 0;

    Utilities util;
    Statistic stat;
    std::vector<int> listVector;

    // Listan pituus ja näytettävien alkioiden määrä
    listLength = util.askLength(listVector);
    listPrints = util.askPrints(listLength);

    // Luodaan aineisto
    util.populateWithRand(listVector, listLength);

    if (listPrints > 0)
    {
        std::cout << std::endl;
        std::cout << "Aineiston " << util.toString(listPrints) << " ensimmaista alkiota ennen jarjestelya:" << std::endl;
        util.printList(listVector, listPrints);
    }

    // Järjestellään
    listVector = mergeSort(stat, listVector);

    if (listPrints > 0)
    {
        std::cout << std::endl;
        std::cout << "Aineiston " << util.toString(listPrints) << " ensimmaista alkiota jarjestelyn jalkeen:" << std::endl;
        util.printList(listVector, listPrints);
    }

    // Paluu valikkoon
    std::cout << std::endl;
    std::cout << "Paina enter palataksesi paavalikkoon";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
