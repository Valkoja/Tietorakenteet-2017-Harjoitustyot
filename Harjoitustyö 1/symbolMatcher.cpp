#include "main.h"

SymbolMatcher::SymbolMatcher()
{
    // Constructor
}

void SymbolMatcher::runLoop()
{
    bool loop = true;
    int input = 0;

    while (loop)
    {
        input = showMenu();

        switch (input)
        {
            case 1:
                if (readInput())
                {
                    processRows(false);
                }
                break;

            case 2:
                if (readFile())
                {
                    processRows(false);
                }
                break;

            case 3:
                if (readFile())
                {
                    processRows(true);
                }
                break;

            default:
                loop = false;
                break;
        }
    }
}

int SymbolMatcher::showMenu()
{
    int temp = 0;
    int output = 0;
    std::string input;
    std::stringstream ss;

    while (output == 0)
    {
        std::cout << std::endl;
        std::cout << "[1] Syota tarkistettava rivi" << std::endl;
        std::cout << "[2] Lue tiedostosta" << std::endl;
        std::cout << "[3] Lue tiedostosta ja tulosta naytolle" << std::endl;
        std::cout << "[4] Sulje ohjelma" << std::endl;
        std::getline(std::cin, input);

        ss.clear();
        ss.str(input);

        // Syöte ei ole kokonaisluku tai se on halutun alueen ulkopuolella
        if (!(ss >> temp) || temp < 1 || temp > 4)
        {
            std::cout << std::endl;
            std::cout << "Virheellinen valinta, ole hyva ja valitse numero 1-4" << std::endl;
            std::cout << "----------------------------------------------------" << std::endl;
        }
        else
        {
            output = temp;
        }
    }

    return output;
}

bool SymbolMatcher::readInput()
{
    std::string line;

    std::cout << std::endl;
    std::cout << "Syota tarkistettava rivi" << std::endl;
    std::getline (std::cin, line);

    rows_.push_back(line);

    return true;
}

bool SymbolMatcher::readFile()
{
    bool result = true;
    std::string line;
    std::string filename;

    std::cout << std::endl;
    std::cout << "Anna avattavan tiedoston nimi / polku" << std::endl;
    std::getline (std::cin, filename);

    std::ifstream fileHandle(filename, std::ifstream::in);

    if (fileHandle.good())
    {
        while (std::getline(fileHandle, line))
        {
            rows_.push_back(line);
        }

        if (rows_.size() < 1)
        {
            result = false;
            std::cout << std::endl;
            std::cout << "Tiedostosta ei saatu luettua yhtaan rivia" << std::endl;
        }
    }
    else
    {
        result = false;
        std::cout << std::endl;
        std::cout << "Tiedoston avaaminen / lukeminen ei onnistunut" << std::endl;
    }

    fileHandle.close();

    return result;
}

void SymbolMatcher::processRows(bool doEcho)
{
    bool result = true;
    int rowCounter = -1;
    std::string input;
    std::vector<std::string>::iterator iter;

    if (doEcho)
    {
        std::cout << std::endl;
    }

    // Käydään rivit läpi
    for(iter = rows_.begin(); iter != rows_.end(); ++iter)
    {
        rowCounter++;
        result = processRow(doEcho, rowCounter, *iter);

        if (!result)
        {
            break;
        }
    }

    // Ei virheitä rivien läpikäynnissä, tarkistetaan jäikö jotain auki
    if (result)
    {
        if (!symbols_.empty())
        {
            printError(symbols_.back().row, symbols_.back().col, symbols_.back().type, Opening);
        }
        else
        {
            std::cout << std::endl;
            std::cout << "Ei virheita: sulut, kommentit ja lainausmerkit tasapainossa" << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << "Paina enter palataksesi valikkoon" << std::endl;
    std::getline (std::cin, input);

    // Siivotaan vektorit
    rows_.clear();
    symbols_.clear();
}

bool SymbolMatcher::processRow(bool doEcho, int rowCounter, std::string rowStr)
{
    bool result = true;
    int colCounter = -1;
    std::size_t found;
    std::string::iterator iter;
    std::string::iterator prev;

    if (doEcho)
    {
        std::cout << rowStr << std::endl;
    }

    for (iter = rowStr.begin(); iter != rowStr.end(); ++iter)
    {
        // Koska suuri osa tarkistuksista käyttää continue ohittaakseen muut merkin
        // tarkastelut, kasvatetaan sarakelaskuria ja tarkistetaan tila kierroksen alussa
        colCounter++;

        if (!result)
        {
            break;
        }

        // Tarkastuksen ohittavat tilat
        if (!symbols_.empty())
        {
            // Ollaan /* */ kommentin sisällä
            if (symbols_.back().type == Comment)
            {
                if (*iter == '/' && colCounter > 1)
                {
                    prev = std::prev(iter, 1);

                    if (*prev == '*')
                    {
                        result = closeSymbol(rowCounter, colCounter, Comment);
                    }
                }

                continue;
            }

            // Ollaan ' ' merkkien sisällä
            if (symbols_.back().type == SingleQuote)
            {
                if (*iter == '\'')
                {
                    if (!isEscaped(colCounter, iter))
                    {
                        result = closeSymbol(rowCounter, colCounter, SingleQuote);
                    }
                }

                continue;
            }

            // Ollaan " " merkkien sisällä
            if (symbols_.back().type == DoubleQuote)
            {
                if (*iter == '"')
                {
                    if (!isEscaped(colCounter, iter))
                    {
                        result = closeSymbol(rowCounter, colCounter, DoubleQuote);
                    }
                }

                continue;
            }
        }

        // Käsittely merkille /
        if (*iter == '/' && colCounter > 1)
        {
            prev = std::prev(iter, 1);

            // Rivikommentti, ohitetaan lopun rivin tarkastelu
            if (*prev == '/')
            {
                break;
            }

            // Ylimääräinen */ merkki, kommenttien sulkeminen hoidettu aiemmin
            if (*prev == '*')
            {
                result = false;
                printError(rowCounter, colCounter, Comment, Closing);
                break;
            }

            continue;
        }

        // Käsittely merkille *
        if (*iter == '*' && colCounter > 1)
        {
            prev = std::prev(iter, 1);

            if (*prev == '/')
            {
                openSymbol(rowCounter, colCounter, Comment);
            }

            continue;
        }

        // Käsittelyt lopuille tarkisteltaville merkeille
        switch (*iter)
        {
            case '\'':
                openSymbol(rowCounter, colCounter, SingleQuote);
                break;

            case '"':
                openSymbol(rowCounter, colCounter, DoubleQuote);
                break;

            case '(':
                openSymbol(rowCounter, colCounter, Round);
                break;

            case '[':
                openSymbol(rowCounter, colCounter, Square);
                break;

            case '{':
                openSymbol(rowCounter, colCounter, Curly);
                break;

            case '<':
                // Sulut kattavat if / while rakenteet, cout toivottavasti muut tapaukset
                if (symbols_.back().type != Round && rowStr.find("cout") == std::string::npos)
                {
                    openSymbol(rowCounter, colCounter, Angle);
                }
                break;

            case ')':
                result = closeSymbol(rowCounter, colCounter, Round);
                break;

            case ']':
                result = closeSymbol(rowCounter, colCounter, Square);
                break;

            case '}':
                result = closeSymbol(rowCounter, colCounter, Curly);
                break;

            case '>':
                if (symbols_.back().type != Round && rowStr.find("cin") == std::string::npos)
                {
                    result = closeSymbol(rowCounter, colCounter, Angle);
                }
                break;
        }
    }

    return result;
}

bool SymbolMatcher::isEscaped(int col, std::string::iterator iter)
{
    bool isEscaped = false;
    int slashCounter = 0;
    std::string::iterator prev = iter;

    // Lasketaan montako kenoviivaa tarkasteltavan merkin edessä on
    while (col > 0)
    {
         prev = std::prev(prev, 1);

         if (*prev == (char)92)
         {
             slashCounter++;
         }
         else
         {
             break;
         }
    }

    // Jos kenoviivoja on pariton määrä, on merkki ohitettu (escaped)
    if (slashCounter % 2 != 0)
    {
        isEscaped = true;
    }

    return isEscaped;
}

bool SymbolMatcher::openSymbol(int row, int col, SymbolType type)
{
    Symbol newSymbol;

    newSymbol.row = row;
    newSymbol.col = col;
    newSymbol.type = type;

    symbols_.push_back(newSymbol);
}

bool SymbolMatcher::closeSymbol(int row, int col, SymbolType type)
{
    bool result = true;

    if (symbols_.empty())
    {
        // Ei auki olevia
        result = false;
        printError(row, col, type, Closing);

    }
    else if (symbols_.back().type != type)
    {
        // Väärän tyyppinen
        result = false;
        printError(row, col, type, Closing);
    }
    else
    {
        symbols_.pop_back();
    }

    return result;
}

void SymbolMatcher::printError(int row, int col, SymbolType symType, ErrorType errType)
{
    std::string error = "";

    switch (symType)
    {
        case Round:
        case Square:
        case Curly:
        case Angle:
            error += "Ylimaarainen " + std::string(errType == Opening ? "alku" : "loppu") + "sulku";
            break;

        case Comment:
            error += "Ylimaarainen " + std::string(errType == Opening ? "alku" : "loppu") + "kommentti";
            break;

        case SingleQuote:
            error += "Ylimaarainen merkin " + std::string(errType == Opening ? "aloitusd" : "lopetus");
            break;

        case DoubleQuote:
            error += "Ylimaarainen merkkijonon " + std::string(errType == Opening ? "aloitus" : "lopetus");
            break;
    }

    std::cout << std::endl;
    std::cout << "VIRHE:      " << error << std:: endl;
    std::cout << "RIVINUMERO: " << (row + 1) << std:: endl;
    std::cout << "RIVI:       " << rows_.at(row) << std:: endl;
    std::cout << std::string(12, ' ') << std::string(col, ' ') << "^" << std::endl;
}
