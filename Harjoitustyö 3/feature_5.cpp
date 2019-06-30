#include "main.h"

void feature_5()
{
    int selection = -1;
    std::string inputString;
    std::stringstream inputStream;

    while (selection != 0)
    {
        std::cout << std::endl;
        std::cout << "Valitse ajettava toiminto:" << std::endl;
        std::cout << "--------------------------" << std::endl;
        std::cout << "[1] - Valintalajittelu" << std::endl;
        std::cout << "[2] - Pikalajittelu" << std::endl;
        std::cout << "[3] - Suorituskykyvertailu" << std::endl;
        std::cout << "[0] - Palaa paavalikkoon" << std::endl;

        while (true)
        {
            std::cout << std::endl;
            std::cout << "Valinta: ";
            std::getline(std::cin, inputString);

            inputStream.clear();
            inputStream.str(inputString);

            if (!(inputStream >> selection) || selection < 0 || selection > 3)
            {
                std::cout << "Virheellinen valinta, ole hyva ja valitse numeroista 0-3" << std::endl;
            }
            else
            {
                break;
            }
        }

        switch (selection)
        {
            case 1:
            case 2:
                feature_5_Sort(selection);
                break;
            case 3:
                feature_5_Compare();
                break;
        }
    }
}

void feature_5_Sort(int algorithm)
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
    if (algorithm == 1)
    {
        selectionSort(stat, listVector);
    }
    else
    {
        quickSort(stat, listVector, 0, listVector.size() - 1);
    }

    if (listPrints > 0)
    {
        std::cout << std::endl;
        std::cout << "Aineiston " << util.toString(listPrints) << " ensimmaista alkiota jarjestelyn jalkeen:" << std::endl;
        util.printList(listVector, listPrints);
    }

    // Paluu valikkoon
    std::cout << std::endl;
    std::cout << "Paina enter palataksesi valikkoon";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void feature_5_Compare()
{
    int selection  = 0;
    int listLength = 0;

    Utilities util;
    Statistic stat;
    std::string inputString;
    std::stringstream inputStream;

    std::vector<int> baseVector;
    std::vector<int> tempVector;
    std::vector<std::vector<std::string>> output(11);

    std::cout << std::endl;
    std::cout << "Valitse suorituskykyvertailu:" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "[1] - 1000 -> 10000" << std::endl;
    std::cout << "[2] - 10000 -> 100000" << std::endl;
    std::cout << "[3] - 100000 -> 1000000" << std::endl;
    std::cout << "[0] - Palaa edelliseen valikkoon" << std::endl;

    while (true)
    {
        std::cout << std::endl;
        std::cout << "Valinta: ";
        std::getline(std::cin, inputString);

        inputStream.clear();
        inputStream.str(inputString);

        if (!(inputStream >> selection) || selection < 0 || selection > 3)
        {
            std::cout << "Virheellinen valinta, ole hyva ja valitse numeroista 0-3" << std::endl;
        }
        else
        {
            switch (selection)
            {
                case 1:
                    listLength = 1000;
                    break;
                case 2:
                    listLength = 10000;
                    break;
                case 3:
                    listLength = 100000;
                    break;
            }

            // Pois inputista
            break;
        }
    }

    // Palattaessa ohitetaan suoritus
    if (selection != 0)
    {
        try
        {
            // Otsikkorivi
            output[0].push_back("Taulu: ");

            for (int i = 0; i < 4; i++)
            {
                output[0].push_back("| ");
                output[0].push_back("Vertail: ");
                output[0].push_back("Sijoitu: ");
                output[0].push_back("Operaat: ");
                output[0].push_back("Aika us: ");
            }

            // Suorituskykyvertailu
            for (int i = 1; i <= 10; i++)
            {
                output[i].push_back(util.toString(listLength * i));
                output[i].push_back("|");

                // Varmistetaan että vektorit mahtuvat muistiin, luodaan aineisto
                baseVector.resize(listLength * i);
                tempVector.resize(listLength * i);
                util.populateWithRand(baseVector, listLength * i);

                // Lomituslajittelu
                tempVector = baseVector;
                stat.reset();
                stat.timerStart();
                tempVector = mergeSort(stat, tempVector);
                stat.timerStop();

                output[i].push_back(util.toString(stat.getComparisons()) + " ");
                output[i].push_back(util.toString(stat.getAssignments()) + " ");
                output[i].push_back(util.toString(stat.getOperations()) + " ");
                output[i].push_back(util.toString(stat.getTimeElapsed()) + " ");
                output[i].push_back("|");

                // Pikalajittelu
                tempVector = baseVector;
                stat.reset();
                stat.timerStart();
                quickSort(stat, tempVector, 0, tempVector.size() - 1);
                stat.timerStop();

                output[i].push_back(util.toString(stat.getComparisons()) + " ");
                output[i].push_back(util.toString(stat.getAssignments()) + " ");
                output[i].push_back(util.toString(stat.getOperations()) + " ");
                output[i].push_back(util.toString(stat.getTimeElapsed()) + " ");
                output[i].push_back("|");

                // Valintalajittelu
                tempVector = baseVector;
                stat.reset();
                stat.timerStart();
                selectionSort(stat, tempVector);
                stat.timerStop();

                output[i].push_back(util.toString(stat.getComparisons()) + " ");
                output[i].push_back(util.toString(stat.getAssignments()) + " ");
                output[i].push_back(util.toString(stat.getOperations()) + " ");
                output[i].push_back(util.toString(stat.getTimeElapsed()) + " ");
                output[i].push_back("|");

                // Lisäyslajittelu
                tempVector = baseVector;
                stat.reset();
                stat.timerStart();
                insertionSort(stat, tempVector);
                stat.timerStop();

                output[i].push_back(util.toString(stat.getComparisons()) + " ");
                output[i].push_back(util.toString(stat.getAssignments()) + " ");
                output[i].push_back(util.toString(stat.getOperations()) + " ");
                output[i].push_back(util.toString(stat.getTimeElapsed()) + " ");
            }

            feature_5_Print(output);
        }
        catch (const std::bad_alloc& e)
        {
            std::cout << "Testi pysahtyi muistivirheeseen, todennakoisesti liian suuri lista (" << e.what() << ")" << std::endl;
        }

        // Paluu valikkoon
        std::cout << std::endl;
        std::cout << "Paina enter palataksesi valikkoon";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void feature_5_Print(std::vector<std::vector<std::string>> output)
{
    Utilities util;
    std::vector<int> colWidths(21, 0);

    // Sarakkeiden leveydet
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            if (output[i].at(j).length() > (unsigned) colWidths.at(j))
            {
                colWidths.at(j) = output[i].at(j).length();
            }
        }
    }

    // Tulostetaan otsikkorivi
    std::cout << std::endl;
    std::cout << std::left << std::setw(colWidths.at(0)) << " ";
    std::cout << std::left << std::setw(util.accumulate(colWidths, 1, 6)) << "| Lomituslajittelu";
    std::cout << std::left << std::setw(util.accumulate(colWidths, 6, 11)) << "| Pikalajittelu";
    std::cout << std::left << std::setw(util.accumulate(colWidths, 11, 16)) << "| Valintalajittelu";
    std::cout << std::left << std::setw(util.accumulate(colWidths, 16, 21)) << "| Lisayslajittelu" << std::endl;

    // Tulostetaan tulokset
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            std::cout << std::left << std::setw(colWidths.at(j)) << output[i].at(j);
        }

        std::cout << std::endl;

        // Viiva sarakeotsikoiden alla
        if (i == 0)
        {
            std::cout << std::string(util.accumulate(colWidths, 0, 21), '-') << std::endl;
        }
    }
}
