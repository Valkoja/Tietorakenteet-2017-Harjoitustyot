#include "main.h"

int Utilities::askLength(std::vector<int> &list)
{
    int inputInt;
    std::string inputString;
    std::stringstream inputStream;

    while (true)
    {
        try
        {
            std::cout << std::endl;
            std::cout << "Syota aineiston koko: ";
            std::getline(std::cin, inputString);

            inputStream.clear();
            inputStream.str(inputString);

            if (!(inputStream >> inputInt))
            {
                std::cout << "Virheellinen syote, ole hyva ja anna positiivinen kokonaisluku" << std::endl;
            }
            else if (inputInt < 1)
            {
                std::cout << "Virheellinen syote, aineiston koon pitaa olla vahintaan 1" << std::endl;
            }
            else if (inputInt >= (int) (INT_MAX / 2))
            {
                std::cout << "Virheellinen syote, luvun pitaa olla pienempi kuin " << (int) (INT_MAX / 2) << std::endl;
            }
            else
            {
                list.resize(inputInt);
                break;
            }
        }
        catch (const std::bad_alloc& e)
        {
            std::cout << "Muistivirhe, todennakoisesti liian suuri lista (" << e.what() << ")" << std::endl;
        }
    }

    return inputInt;
}

int Utilities::askTarget(int randMax)
{
    int inputInt;
    std::string inputString;
    std::stringstream inputStream;

    while (true)
    {
        std::cout << "Syota haettava luku tai arvo syottamalla [R]: ";
        std::getline(std::cin, inputString);

        if (inputString.compare("R") == 0 || inputString.compare("r") == 0)
        {
            inputInt = randValue(randMax);

            std::cout << "Haettavaksi luvuksi arvottiin: " << inputInt << std::endl;
            break;
        }
        else
        {
            inputStream.clear();
            inputStream.str(inputString);

            if (!(inputStream >> inputInt))
            {
                std::cout << "Virheellinen syote, ole hyva ja anna kokonaisluku valilta " << INT_MIN << " ja " << INT_MAX << std::endl << std::endl;
            }
            else
            {
                break;
            }
        }
    }

    return inputInt;
}

int Utilities::askPrints(int max)
{
    int inputInt;
    std::string inputString;
    std::stringstream inputStream;

    while (true)
    {
        std::cout << std::endl;
        std::cout << "Syota tulostettavien lukujen maara: ";
        std::getline(std::cin, inputString);

        inputStream.clear();
        inputStream.str(inputString);

        if (!(inputStream >> inputInt))
        {
            std::cout << "Virheellinen syote, ole hyva ja anna positiivinen kokonaisluku" << std::endl;
        }
        else if (inputInt < 0)
        {
            std::cout << "Virheellinen syote, maara ei voi olla negatiivinen" << std::endl;
        }
        else
        {
            break;
        }
    }

    if (inputInt > max)
    {
        inputInt = max;
    }

    return inputInt;
}

int Utilities::randValue(int randMax)
{
    std::uniform_int_distribution<int> distribution(0, randMax);
    return distribution(generator);
}

int Utilities::accumulate(std::vector<int> &list, int start, int end)
{
    int result = 0;

    for (int i = start; i < end; i++)
    {
        result += list.at(i);
    }

    return result;
}

int Utilities::widerStr(std::string str1, std::string str2)
{
    int wider = str1.length() > str2.length() ? str1.length() : str2.length();

    return wider;
}

std::string Utilities::toString(int number)
{
    std::stringstream strStream;
    strStream << number;
    return strStream.str();
}

void Utilities::populateWithOdds(std::vector<int> &list, int size)
{
    int value = 1;

    for (int i = 0; i < size; i++)
    {
        list[i] = value;
        value += 2;
    }
}

void Utilities::populateWithRand(std::vector<int> &list, int size)
{
    std::uniform_int_distribution<int> distribution(0, (size > INT_MAX / 10 ? size : size * 10));

    for (int i = 0; i < size; i++)
    {
        list[i] = distribution(generator);
    }
}

void Utilities::printList(std::vector<int> &list, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << list.at(i);

        if (i < size - 1)
        {
            std::cout << ", ";
        }
        else
        {
            std::cout << std::endl;
        }
    }
}
