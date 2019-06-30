#pragma once

class Statistic
{
    public:
        Statistic();

        void reset();
        void addComparisons(int addition);
        void addAssignments(int addition);
        void timerStart();
        void timerStop();

        void swap(int &first, int &second);
        bool isEqual(int first, int second);
        bool isGreater(int first, int second);

        int getComparisons();
        int getAssignments();
        int getOperations();
        int getTimeElapsed();

    private:
        int comparisons;
        int assignments;
        std::chrono::high_resolution_clock::time_point startTime;
        std::chrono::high_resolution_clock::time_point stopTime;
};
