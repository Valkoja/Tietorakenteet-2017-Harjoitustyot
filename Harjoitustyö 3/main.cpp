#include "main.h"

// Alustetaan staattinen random engine utilities luokkaan
std::default_random_engine Utilities::generator = std::default_random_engine((int) std::time(nullptr));

int main()
{
    std::cout << "Testipeti etsinta- ja lajittelualgoritmeille - Valkoja Iiro" << std::endl;

    int selection = -1;
    std::string inputString;
    std::stringstream inputStream;

    while (selection != 0)
    {
        std::cout << std::endl;
        std::cout << "Valitse ajettava toiminto:" << std::endl;
        std::cout << "--------------------------" << std::endl;
        std::cout << "[1] - Perakkaisetsinta" << std::endl;
        std::cout << "[2] - Binaarietsinta ja suorituskykyvertailu" << std::endl;
        std::cout << "[3] - Lisayslajittelu" << std::endl;
        std::cout << "[4] - Lomituslajittelu" << std::endl;
        std::cout << "[5] - Lisaalgoritmit ja suorituskykyvertailu" << std::endl;
        std::cout << "[0] - Lopeta" << std::endl;

        while (true)
        {
            std::cout << std::endl;
            std::cout << "Valinta: ";
            std::getline(std::cin, inputString);

            inputStream.clear();
            inputStream.str(inputString);

            if (!(inputStream >> selection) || selection < 0 || selection > 5)
            {
                std::cout << "Virheellinen valinta, ole hyva ja valitse numeroista 0-5" << std::endl;
            }
            else
            {
                break;
            }
        }

        switch (selection)
        {
            case 1:
                feature_1();
                break;
            case 2:
                feature_2();
                break;
            case 3:
                feature_3();
                break;
            case 4:
                feature_4();
                break;
            case 5:
                feature_5();
                break;
        }
    }

    return 0;
}
