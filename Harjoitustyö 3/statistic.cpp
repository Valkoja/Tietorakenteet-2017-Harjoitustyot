#include "main.h"

Statistic::Statistic()
{
    comparisons = 0;
    assignments = 0;
}

void Statistic::timerStart()
{
    startTime = std::chrono::high_resolution_clock::now();
}

void Statistic::timerStop()
{
    stopTime = std::chrono::high_resolution_clock::now();
}

void Statistic::addComparisons(int addition)
{
    comparisons += addition;
}

void Statistic::addAssignments(int addition)
{
    assignments += addition;
}

int Statistic::getComparisons()
{
    return comparisons;
}

int Statistic::getAssignments()
{
    return assignments;
}

int Statistic::getOperations()
{
    return comparisons + assignments;
}

int Statistic::getTimeElapsed()
{
    return (int) std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime).count();
}

bool Statistic::isEqual(int first, int second)
{
    comparisons++;
    return (first == second);
}

bool Statistic::isGreater(int first, int second)
{
    comparisons++;
    return (first > second);
}

void Statistic::swap(int &first, int &second)
{
    assignments += 3;

    int temp = first;
    first = second;
    second = temp;
}

void Statistic::reset()
{
    comparisons = 0;
    assignments = 0;
}
