#pragma once

enum ErrorType
{
    Opening,
    Closing
};

enum SymbolType
{
    Round,       // (
    Square,      // [
    Curly,       // {
    Angle,       // <
    Comment,     // /*
    SingleQuote, // '
    DoubleQuote  // "
};

struct Symbol
{
    int row;
    int col;
    SymbolType type;
};

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "symbolMatcher.h"
