#include "main.h"

int main()
{
    int selection;
    std::string inputString;
    std::stringstream ss;

    std::cout << "Lentokenttasimulaatio - Valkoja Iiro" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "Choose variation to run:" << std::endl;
    std::cout << "[1] - One runway" << std::endl;
    std::cout << "[2] - Two runways, either landing or takeoff" << std::endl;
    std::cout << "[3] - Two runways, landing and takoff / landing when necessary" << std::endl;
    std::cout << "[4] - Three runways, landing, takeoff and whichever is needed" << std::endl;
    std::cout << "[5] - One runway, fuel usage" << std::endl;
    std::cout << "[0] - Quit" << std::endl;

    while (true)
    {
        std::getline(std::cin, inputString);

        ss.clear();
        ss.str(inputString);

        // Syöte ei ole kokonaisluku tai se on halutun alueen ulkopuolella
        if (!(ss >> selection) || selection < 0 || selection > 5)
        {
            std::cout << std::endl;
            std::cout << "Invalid selection, please pick between numbers 0 and 5" << std::endl;
        }
        else
        {
            break;
        }
    }

    if (selection == 1)
    {
        std::cout << "This program simulates an airport with only one runway." << std::endl;
        std::cout << "One plane can land or depart in each unit of time." << std::endl;

        Variation_1 var1;
        var1.requestParams();
        var1.runSimulation();
    }
    else if (selection == 2)
    {
        std::cout << "This program simulates an airport with two runways." << std::endl;
        std::cout << "One plane can land and one plane can depart in each unit of time." << std::endl;

        Variation_2 var2;
        var2.requestParams();
        var2.runSimulation();
    }
    else if (selection == 3)
    {
        std::cout << "This program simulates an airport with two runways." << std::endl;
        std::cout << "One plane can land and one plane can either land or depart in each unit of time." << std::endl;

        Variation_3 var3;
        var3.requestParams();
        var3.runSimulation();
    }
    else if (selection == 4)
    {
        std::cout << "This program simulates an airport with only three runways." << std::endl;
        std::cout << "One plane can land, one depart and one do either in each unit of time." << std::endl;

        Variation_4 var4;
        var4.requestParams();
        var4.runSimulation();
    }
    else if (selection == 5)
    {
        std::cout << "This program simulates an airport with only one runway." << std::endl;
        std::cout << "One plane can land or depart in each unit of time, fuel usage is tracked." << std::endl;

        Variation_5 var5;
        var5.requestParams();
        var5.runSimulation();
    }

    return 0;
}
