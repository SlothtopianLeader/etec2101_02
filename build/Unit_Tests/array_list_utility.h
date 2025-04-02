#pragma once
#pragma once
#include <string>
#include <stdexcept>
#include <ostream>
#include <iostream>
#include <random>
#include <unit_tests_array_list.h>
/*
    List of References:
    https://www.geeksforgeeks.org/cpp-program-for-quicksort/
    https://www.programiz.com/dsa/quick-sort
    https://www.geeksforgeeks.org/bubble-sort-algorithm/
    https://en.cppreference.com/w/cpp/header/random
    https://www.geeksforgeeks.org/shuffle-a-given-array-using-fisher-yates-shuffle-algorithm/
*/

enum class SortOrder
{
    ASCENDING,
    DESCENDING
};

template <typename T>
void printArray(T& L, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << L[i] << " ";
    }
    std::cout << std::endl;
}

template <class T>
int partition(ssuds::ArrayList<T>& L, int low, int high, SortOrder st)
{
    int pivot = L[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if ((st == SortOrder::ASCENDING && L[j] <= pivot) || (st == SortOrder::DESCENDING && L[j] >= pivot))
        {
            i++;
            std::swap(L[i], L[j]);
        }
    }

    std::swap(L[i + 1], L[high]);
    return (i + 1);
}

template <typename T>
void quickSort(ssuds::ArrayList<T>& L, int low, int high, SortOrder st)
{
    if (low < high)
    {
        int pi = partition(L, low, high, st);
        quickSort(L, low, pi - 1, st);          // left of pivot
        quickSort(L, pi + 1, high, st);         // right of pivot
    }
}

template <typename T>
void quickSort(ssuds::ArrayList<T>& L, SortOrder st)
{
    quickSort(L, 0, L.size() - 1, st);
}


template <typename T>
bool out_of_order(const T& v1, const T& v2, SortOrder st)
{
    if (st == SortOrder::ASCENDING)
        return v1 > v2;
    else
        return v1 < v2;
}

template <typename T>
int binarySearch(ssuds::ArrayList<T>& L, int low, int high, int x, SortOrder st)
{
    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (L[mid] == x)
            return mid;
        if (st == SortOrder::ASCENDING)
        {
            if (L[mid] < x)
                low = mid + 1;
            else
                high = mid - 1;
        }
        else
        {
            if (L[mid] > x)
                low = mid + 1;
            else
                high = mid - 1;
        }
    }
    return -1;
}

template <typename T>
int binarySearch(ssuds::ArrayList<T>& L, int x, SortOrder st)
{
    return binarySearch(L, 0, L.size() - 1, x, st);
}

template <typename T>
void bubbleSort(ssuds::ArrayList<T>& L, SortOrder st)
{
    for (int i = 0; i < L.size() - 1; i++)
    {
        for (int j = 0; j < L.size() - 1 - i; j++)
        {
            if ((st == SortOrder::ASCENDING && L[j] > L[j + 1]) || (st == SortOrder::DESCENDING && L[j] < L[j + 1]))
            {
                std::swap(L[j], L[j + 1]);
            }
        }
    }
}

template <typename T>
void shuffle(ssuds::ArrayList<T>& L)
{
    std::random_device rd;
    std::mt19937 random(rd());

    for (int i = L.size() - 1; i > 0; i--)
    {
        std::uniform_int_distribution<> dist(0, i);
        int j = dist(random);

        std::swap(L[i], L[j]);
    }
}
