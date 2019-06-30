#include "main.h"

void feature_2()
{
    int selection = -1;
    std::string inputString;
    std::stringstream inputStream;

    while (selection != 0)
    {
        std::cout << std::endl;
        std::cout << "Valitse ajettava toiminto:" << std::endl;
        std::cout << "--------------------------" << std::endl;
        std::cout << "[1] - Binaarietsinta" << std::endl;
        std::cout << "[2] - Suorituskykyvertailu" << std::endl;
        std::cout << "[0] - Palaa paavalikkoon" << std::endl;

        while (true)
        {
            std::cout << std::endl << "Valinta: ";
            std::getline(std::cin, inputString);

            inputStream.clear();
            inputStream.str(inputString);

            if (!(inputStream >> selection) || selection < 0 || selection > 2)
            {
                std::cout << "Virheellinen valinta, ole hyva ja valitse numeroista 0-2" << std::endl;
            }
            else
            {
                break;
            }
        }

        switch (selection)
        {
            case 1:
                feature_2_Find();
                break;
            case 2:
                feature_2_Compare();
                break;
        }
    }
}

void feature_2_Find()
{
    int listIndex  = 0;
    int listLength = 0;
    int listTarget = 0;

    Utilities util;
    Statistic stat;
    std::vector<int> listVector;

    // Listan pituus, haettava avain, aineiston luonti
    listLength = util.askLength(listVector);
    listTarget = util.askTarget(listLength);
    util.populateWithOdds(listVector, listLength);

    // Käydään luvut läpi
    stat.timerStart();
    listIndex = binarySearch(stat, listVector, listTarget, 0, listLength - 1);
    stat.timerStop();

    // Lopputuloseksen tulostus
    if (listIndex != -1)
    {
        std::cout << std::endl;
        std::cout << "Luku loytyi listan paikalta " << util.toString(listIndex) << std::endl;
    }
    else
    {
        std::cout << std::endl;
        std::cout << "Lukua ei loytynyt" << std::endl;
    }

    std::cout << "Vertailuja:  " << util.toString(stat.getComparisons()) << std::endl;
    std::cout << "Aikaa kului: " << util.toString(stat.getTimeElapsed()) << " us" << std::endl;

    std::cout << std::endl;
    std::cout << "Paina enter palataksesi valikkoon";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void feature_2_Compare()
{
    int repeats    = 0;
    int listIndex  = 0;
    int listLength = 0;
    int listTarget = 0;
    int avgSeqFind = 0;
    int avgSeqComp = 0;
    int avgSeqTime = 0;
    int avgBinFind = 0;
    int avgBinComp = 0;
    int avgBinTime = 0;

    Utilities util;
    Statistic stat;
    std::string inputString;
    std::stringstream inputStream;
    std::vector<int> listVector;

    // Listan pituus, luodaan aineisto
    listLength = util.askLength(listVector);
    util.populateWithOdds(listVector, listLength);

    // Toistojen määrä
    while (true)
    {
        std::cout << "Syota toistojen maara: ";
        std::getline(std::cin, inputString);

        inputStream.clear();
        inputStream.str(inputString);

        if (!(inputStream >> repeats))
        {
            std::cout << "Virheellinen syote, ole hyva ja anna positiivinen kokonaisluku" << std::endl << std::endl;
        }
        else if (repeats < 1)
        {
            std::cout << "Virheellinen syote, toistoja pitaa suorittaa vahintaan 1" << std::endl << std::endl;
        }
        else
        {
            break;
        }
    }

    // Tulostusvektori = toistot + keskiarvot
    std::vector<std::vector<std::string>> output(repeats + 1);

    for (int i = 0; i < repeats; i++)
    {
        // Otsikkorivi
        output[i].push_back("Toisto " + util.toString(i + 1) + " / " + util.toString(repeats) + " - Haettu lukua: " + util.toString(listTarget));

        // Arvotaan haettava luku
        listTarget = util.randValue(listLength);

        // Perakkaisetsinta
        stat.reset();
        stat.timerStart();
        listIndex = sequentialSearch(stat, listVector, listTarget);
        stat.timerStop();

        output[i].push_back("Perakkaisetsinta:  ");
        output[i].push_back(listIndex != -1 ? "Loytyi, paikka: " + util.toString(listIndex) + "  " : "Lukua ei loytynyt  ");
        output[i].push_back("Vertailuja: " + util.toString(stat.getComparisons()) + "  ");
        output[i].push_back("Aikaa kului: " + util.toString(stat.getTimeElapsed()) + " us");

        avgSeqFind += (listIndex != -1 ? 1 : 0);
        avgSeqComp += stat.getComparisons();
        avgSeqTime += stat.getTimeElapsed();

        // Binaarietsinta
        stat.reset();
        stat.timerStart();
        listIndex = binarySearch(stat, listVector, listTarget, 0, listLength - 1);
        stat.timerStop();

        output[i].push_back("Binaarietsinta:    ");
        output[i].push_back(listIndex != -1 ? "Loytyi, paikka: " + util.toString(listIndex) + "  " : "Lukua ei loytynyt  ");
        output[i].push_back("Vertailuja: " + util.toString(stat.getComparisons()) + "  ");
        output[i].push_back("Aikaa kului: " + util.toString(stat.getTimeElapsed()) + " us");

        avgBinFind += (listIndex != -1 ? 1 : 0);
        avgBinComp += stat.getComparisons();
        avgBinTime += stat.getTimeElapsed();
    }

    // Keskiarvot tulostusvektoriin
    output[repeats].push_back("Keskiarvot " + util.toString(repeats) + " toiston jalkeen");
    output[repeats].push_back("Perakkaisetsinta:  ");
    output[repeats].push_back("Loytyi " + util.toString(avgSeqFind) + " / " + util.toString(repeats) + "  ");
    output[repeats].push_back("Vertailuja: " + util.toString((int) std::floor(avgSeqComp / repeats)) + "  ");
    output[repeats].push_back("Aikaa kului: " + util.toString((int) std::floor(avgSeqTime / repeats)) + " us");
    output[repeats].push_back("Binaarietsinta:    ");
    output[repeats].push_back("Loytyi " + util.toString(avgBinFind) + " / " + util.toString(repeats) + "  ");
    output[repeats].push_back("Vertailuja: " + util.toString((int) std::floor(avgBinComp / repeats)) + "  ");
    output[repeats].push_back("Aikaa kului: " + util.toString((int) std::floor(avgBinTime / repeats)) + " us");

    // Tulostus
    feature_2_Print(output);

    std::cout << std::endl;
    std::cout << "Paina enter palataksesi valikkoon";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void feature_2_Print(std::vector<std::vector<std::string>> output)
{
    unsigned colWidth1 = 0;
    unsigned colWidth2 = 0;
    unsigned colWidth3 = 0;
    unsigned colWidth4 = 0;

    // Sarakkeiden leveydet
    for (unsigned i = 0; i < output.size(); i++)
    {
        if (output[i].at(1).length() > colWidth1) colWidth1 = output[i].at(1).length();
        if (output[i].at(5).length() > colWidth1) colWidth1 = output[i].at(5).length();

        if (output[i].at(2).length() > colWidth2) colWidth2 = output[i].at(2).length();
        if (output[i].at(6).length() > colWidth2) colWidth2 = output[i].at(6).length();

        if (output[i].at(3).length() > colWidth3) colWidth3 = output[i].at(3).length();
        if (output[i].at(7).length() > colWidth3) colWidth3 = output[i].at(7).length();

        if (output[i].at(4).length() > colWidth4) colWidth4 = output[i].at(4).length();
        if (output[i].at(8).length() > colWidth4) colWidth4 = output[i].at(8).length();
    }

    // Tulostus
    for (unsigned i = 0; i < output.size(); i++)
    {
        std::cout << std::endl;
        std::cout << output[i].at(0) << std::endl;
        std::cout << std::string((colWidth1 + colWidth2 + colWidth3 + colWidth4), '-') << std::endl;
        std::cout << std::left << std::setw(colWidth1) << output[i].at(1);
        std::cout << std::left << std::setw(colWidth2) << output[i].at(2);
        std::cout << std::left << std::setw(colWidth3) << output[i].at(3);
        std::cout << std::left << std::setw(colWidth4) << output[i].at(4) << std::endl;
        std::cout << std::left << std::setw(colWidth1) << output[i].at(5);
        std::cout << std::left << std::setw(colWidth2) << output[i].at(6);
        std::cout << std::left << std::setw(colWidth3) << output[i].at(7);
        std::cout << std::left << std::setw(colWidth4) << output[i].at(8) << std::endl;
    }
}
