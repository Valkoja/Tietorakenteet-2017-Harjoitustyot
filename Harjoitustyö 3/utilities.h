#pragma once

class Utilities
{
    public:
        static std::default_random_engine generator;

        int askLength(std::vector<int> &list);
        int askTarget(int randMax);
        int askPrints(int printsMax);
        int randValue(int randMax);

        int accumulate(std::vector<int> &list, int start, int end);
        int widerStr(std::string str1, std::string str2);
        std::string toString(int number);

        void populateWithOdds(std::vector<int> &list, int size);
        void populateWithRand(std::vector<int> &list, int size);
        void printList(std::vector<int> &list, int size);
};
