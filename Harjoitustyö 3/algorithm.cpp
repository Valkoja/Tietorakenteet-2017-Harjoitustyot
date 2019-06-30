#include "main.h"

int sequentialSearch(Statistic &stat, std::vector<int> &list, int target)
{
    for (unsigned i = 0; i < list.size(); i++)
    {
        if (stat.isEqual(list.at(i), target))
        {
            return i;
        }
    }

    return -1;
}

int binarySearch(Statistic &stat, std::vector<int> &list, int target, int start, int end)
{
    if (stat.isEqual(end - start, 1))
    {
        if (stat.isEqual(target, list.at(start)))
            return start;

        if (stat.isEqual(target, list.at(end)))
            return end;

        return -1;
    }

    int middle = start + (int) std::floor((end - start) / 2);

    if (stat.isEqual(target, list.at(middle)))
    {
        return middle;
    }

    if (stat.isGreater(target, list.at(middle)))
    {
        return binarySearch(stat, list, target, middle, end);
    }
    else
    {
        return binarySearch(stat, list, target, start, middle);
    }
}

void insertionSort(Statistic &stat, std::vector<int> &list)
{
    for (unsigned i = 0; i < list.size(); i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (stat.isGreater(list.at(j - 1), list.at(j)))
            {
                stat.swap(list[j-1], list[j]);
            }
        }
    }
}

void selectionSort(Statistic &stat, std::vector<int> &list)
{
    int min;

    for (unsigned i = 0; i < list.size(); i++)
    {
        min = i;

        for (unsigned j = i + 1; j < list.size(); j++)
        {
            if (stat.isGreater(list.at(min), list.at(j)))
            {
                min = j;
            }
        }

        if (!stat.isEqual(min, i))
        {
            stat.swap(list[i], list[min]);
        }
    }
}

std::vector<int> mergeSort(Statistic &stat, std::vector<int> list)
{
    if (list.size() == 1)
    {
        return list;
    }

    int middle = (int) std::floor(list.size() / 2);
    std::vector<int> left(list.begin(), list.begin() + middle);
    std::vector<int> right(list.begin() + middle, list.end());

    left = mergeSort(stat, left);
    right = mergeSort(stat, right);

    return mergeSortCombine(stat, left, right);
}

std::vector<int> mergeSortCombine(Statistic &stat, std::vector<int> left, std::vector<int> right)
{
    std::vector<int> result;

    while (!left.empty() && !right.empty())
    {
        if (stat.isGreater(right.front(), left.front()))
        {
            stat.addAssignments(1);
            result.push_back(left.front());
            left.erase(left.begin());
        }
        else
        {
            stat.addAssignments(1);
            result.push_back(right.front());
            right.erase(right.begin());
        }
    }

    while (!left.empty())
    {
        stat.addAssignments(1);
        result.push_back(left.front());
        left.erase(left.begin());
    }

    while (!right.empty())
    {
        stat.addAssignments(1);
        result.push_back(right.front());
        right.erase(right.begin());
    }

    return result;
}

void quickSort(Statistic &stat, std::vector<int> &list, int lo, int hi)
{
    if (stat.isGreater(hi, lo))
    {
        int part = quickSortPart(stat, list, lo, hi);

        quickSort(stat, list, lo, part - 1);
        quickSort(stat, list, part + 1, hi);
    }
}

int quickSortPart(Statistic &stat, std::vector<int> &list, int lo, int hi)
{
    int i = lo - 1;
    int pivot = list.at(hi);

    for (int j = lo; j < hi; j++)
    {
        if (stat.isGreater(pivot, list.at(j)))
        {
            i += 1;
            stat.swap(list[i], list[j]);
        }
    }

    if (stat.isGreater(list.at(i + 1), list.at(hi)))
    {
        stat.swap(list[hi], list[i + 1]);
    }

    return i + 1;
}
