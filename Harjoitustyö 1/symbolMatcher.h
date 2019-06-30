#pragma once

class SymbolMatcher
{
    public:
       SymbolMatcher();
       void runLoop();

   private:
       int showMenu();

       bool readFile();
       bool readInput();
       bool processRow(bool doEcho, int rowCounter, std::string rowStr);
       bool openSymbol(int row, int col, SymbolType type);
       bool closeSymbol(int row, int col, SymbolType type);
       bool isEscaped(int col, std::string::iterator iter);

       void processRows(bool doEcho);
       void printError(int row, int col, SymbolType symType, ErrorType errType);

       std::vector<Symbol> symbols_;
       std::vector<std::string> rows_;
};
