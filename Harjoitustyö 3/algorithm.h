#pragma once

int sequentialSearch(Statistic &stat, std::vector<int> &list, int target);
int binarySearch(Statistic &stat, std::vector<int> &list, int target, int start, int end);

void insertionSort(Statistic &stat, std::vector<int> &list);
void selectionSort(Statistic &stat, std::vector<int> &list);

std::vector<int> mergeSort(Statistic &stat, std::vector<int> list);
std::vector<int> mergeSortCombine(Statistic &stat, std::vector<int> left, std::vector<int> right);

void quickSort(Statistic &stat, std::vector<int> &list, int lo, int hi);
int quickSortPart(Statistic &stat, std::vector<int> &list, int lo, int hi);
